# based on this project: https://github.com/JimsJump/Duet_3_6HC_Time_Lapse
# Copyright (C) {2020}  {JimsJump.com}
# Copyright (C) {2022}  {Adam Haile}
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import requests as r
from requests.exceptions import Timeout
import sys
import json

import os
import select
import signal
from systemd import journal

class Lumix:
    def __init__(self, ip):
        self.ip = ip
        self.resp = None
        self.baseurl = "http://{ip}/cam.cgi".format(ip=self.ip)
        # self.start()
        
    def __get(self, params):
        try:
            self.resp = r.get(self.baseurl, params=params, timeout=1)
            return self.__check()
        except Timeout:
            return (False, f'Error: Timeout waiting for connection to {self.ip}')
        
    def __check(self):
        if self.resp != None:
            if self.resp.status_code != 200:
                return (False, self.resp.text)
                
        return (True, None)
        
    def start(self):
        return self.__get({"mode": "camcmd", "value": "recmode"})
        
    def cap(self):
        return self.__get({"mode": "camcmd", "value": "capture"})
        
    def rec_start(self):
        return self.__get({"mode": "camcmd", "value": "video_recstart"})
        
    def rec_stop(self):
        return self.__get({"mode": "camcmd", "value": "video_recstop"})
        
        
def init_journal():
    # Create a systemd.journal.Reader instance 
    j = journal.Reader()

    # Set the reader's default log level
    j.log_level(journal.LOG_INFO)

    # Only include entries since the current box has booted.
    j.this_boot()
    j.this_machine()

    # Filter log entries to Duet3 Control Server
    j.add_match(_SYSTEMD_UNIT="duetcontrolserver.service")

    # Move to the end of the journal
    j.seek_tail()

    # Important! - Discard old journal entries
    j.get_previous()

    # Create a poll object for journal entries
    p = select.poll()
    p.register(j, j.get_events())

    # Register the journal's file descriptor with the polling object.
    journal_fd = j.fileno()
    poll_event_mask = j.get_events()
    p.register(journal_fd, poll_event_mask)
    
    return (j, p)
    
def poll(j, p, funcs):
    valid_funcs = funcs.keys()
    
    print('Polling for camera control messages...')
    # Poll for new journal entries every 250ms
    # Update and take action the Duet Control Server announces:
    # CAM_START, CAM_CAPTURE, CAM_REC_START, & CAM_REC_STOP
    # Anouncements are sent via GCODE using M118 P0 S"CAM_CAPTURE" for example
    while True :
        if p.poll(250) :
            if j.process() != journal.APPEND :
                continue
            for entry in j:
                msg = entry['MESSAGE']
                ts = str(entry['__REALTIME_TIMESTAMP'] )
                
                if msg.startswith('[info] '):
                    msg = msg.strip().replace('[info] ', '')
                    if msg in valid_funcs:
                        status, error = funcs[msg]()
                        if status:
                            print(f'{ts} | {msg} SUCCESS')
                        else:
                            print(f'{ts} | {msg} FAILED -> {error}')
    
            
def main():
    if len(sys.argv) > 1:
        cmd = sys.argv[1]
        
    ip = None
    with open('/home/dsf/lumix.json', 'r') as f:
        cfg = json.load(f)
        if isinstance(cfg, dict) and 'ip' in cfg:
            ip = cfg['ip']
            
    if not ip:
        print('Error: Could not load IP address')
        
    try:
        l = Lumix(ip)
        
        funcs = {
            'CAM_START': l.start,
            'CAM_CAPTURE': l.cap,
            'CAM_REC_START': l.rec_start,
            'CAM_REC_STOP': l.rec_stop 
        }
        
        j, p = init_journal()
        poll(j, p, funcs)
    except KeyboardInterrupt:
        print('Closing...')
    