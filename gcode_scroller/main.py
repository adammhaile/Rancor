import subprocess
from pathlib import Path
from subprocess import Popen, check_output
import shlex
import os
import sys
import time

fgc = '\x1b[1;166}'

scroll_delay = 0.03

banner = """
d8888b.                       
88  `8D                       
88oobY'                       
88`8b                         
88 `88.                       
88   YD                       
     .d8b.                    
    d8' `8b                   
    88ooo88                   
    88~~~88                   
    88   88                   
    YP   YP                   
        d8b   db              
        888o  88              
        88V8o 88              
        88 V8o88              
        88  V888              
        VP   V8P              
             .o88b.           
            d8P  Y8           
            8P                
            8b                
            Y8b  d8           
             `Y88P'           
                 .d88b.       
                .8P  Y8.      
                88    88      
                88    88      
                `8b  d8'      
                 `Y88P'       
                       d8888b.
                       88  `8D
                       88oobY'
                       88`8b  
                       88 `88.
                       88   YD
"""
mod_time = 0.25
boot_up_scroll = [
    ('Initializing system', 0.25),
    (' .', 0.25), (' .', 0.25), (' .', 0.25), (' .', 0.25),
    ('\n\nWelcome to R.A.N.C.O.R.', 0.25),
    
    ('\n\n\tR', 0.5),('OBOTIC', 0.25),
    ('\n\tA', 0.5),('UTOMATED', 0.25),
    ('\n\tN', 0.5),('P-COMPLETE', 0.25),
    ('\n\tO', 0.5),('BJECT', 0.25),
    ('\n\tR', 0.5),('EPLICATOR\n\n', 1.0),
    
    ('**** Loading Core Modules ****\n\n', 0.5),
    ('Matter Engine:          ', mod_time), ('  [OK]\n', 0.25),
    ('Pylon Construction:     ', mod_time), ('  [OK]\n', 0.25),
    ('Flux Capacitor:         ', mod_time), ('[FAIL]\n', 0.25),
    ('Speech Synthesis:       ', mod_time), ('  [OK]\n', 0.25),
    ('Inertial Dampers:       ', mod_time), ('  [OK]\n', 0.25),
    ('Thermal Core:           ', mod_time), ('  [OK]\n', 0.25),
    ('True Leveling:          ', mod_time), ('  [OK]\n', 0.25),
    ('Filament Blockchain:    ', mod_time), ('  [OK]\n', 0.25),
    ('Turbo Encabulator:      ', mod_time), ('  [OK]\n', 0.25),
    ('thingiverse.com:        ', mod_time), ('[FAIL]\n', 0.25),
    ('Printables.com:         ', mod_time), ('  [OK]\n', 0.25),
    ('Smoothieware:           ', mod_time), ('[FAIL]\n', 0.25),
    ('Marlin:                 ', mod_time), ('[FAIL]\n', 0.25),
    ('Klipper:                ', mod_time), ('[FAIL]\n', 0.25),
    ('RepRapFirmware/Duet:    ', mod_time), ('  [OK]\n', 0.25),
    
    ('\n\n\nR.A.N.C.O.R. Online\n\n', 0.5),
    ('Starting Code Monitor ...\n\n', 0.5),
]

def scroll(line):
    s = line[0]
    end_delay = 0.0
    if len(line) > 1:
        end_delay = line[1]

    s = s.replace('\n', '\n\n') # fbterm needs double for some reason
    sys.stdout.write(fgc)
    for c in s:
        sys.stdout.write(c)
        sys.stdout.flush()
        time.sleep(scroll_delay)
    
    if end_delay > 0:
        time.sleep(end_delay)

def run():
    cmd = '/opt/dsf/bin/CodeLogger'
    args = ['-t', 'executed', '-q']
    cwd = os.getcwd()
    process = Popen([cmd] + args,
                    shell=False,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    cwd=cwd
                    )
    output = ''
    while process.poll() is None:
        try:
            line = process.stdout.readline().decode('utf-8').rstrip()
            i = line.find(':')
            if i >= 0 and len(line) > i+3:
                # remove last 3 because 'executed' prints ' =>' at end
                line = line[i+2:]
                if line.endswith(' =>'):
                    line = line[:len(line)-3]
                line = line[:30]
            print(f'{fgc}{line}')
        except KeyboardInterrupt:
            sys.exit()
        except:
            pass
        
    stdout, _ = process.communicate()
    line = stdout.decode('ascii')


if __name__ == '__main__':
    banner_lines = banner.split('\n')
    lc = len(banner_lines)
    for line in banner_lines:
        sys.stdout.write(fgc)
        line += '\n\n'
        for c in line:
            sys.stdout.write(c)
            sys.stdout.flush()
            time.sleep(0.003)
            
    for _ in range(lc*2): #push banner off screen
        print()
        time.sleep(0.03)
            
    # scroll main bootup sequence
    for line in boot_up_scroll:
        scroll(line)
            
    check_output(['/opt/dsf/bin/CodeConsole', '-c', 'M800 F\"greeting\"'])
        
    while True:
        try:
            run()
        except KeyboardInterrupt:
            sys.exit()