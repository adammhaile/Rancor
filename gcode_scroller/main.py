import subprocess
from pathlib import Path
from subprocess import Popen
import shlex
import os

fgc = '\x1b[1;166}'

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
        line = process.stdout.readline().decode('ascii').rstrip()
        i = line.find(':')
        if i >= 0 and len(line) > i+3:
            # remove last 3 because 'executed' prints ' =>' at end
            line = line[i+2:len(line)-3]
        print(f'{fgc}{line}{reset}')
        
    stdout, _ = process.communicate()
    line = stdout.decode('ascii')


if __name__ == '__main__':
    run()