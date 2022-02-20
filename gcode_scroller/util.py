import subprocess
from pathlib import Path
from subprocess import Popen
import shlex
import os

from . import log

def shell_split(cmd, args, cwd=None):
    if cwd is None:
        cwd = os.getcwd()
    log.info(f"Running: {cmd} {' '.join(args)}")
    process = Popen([cmd] + args,
                    shell=False,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    cwd=cwd
                    )
    output = ''
    while process.poll() is None:
        line = process.stdout.readline().decode('ascii')
        output += line
        line = line.rstrip()
        if line:
            log.info(f"$> {line}")
    stdout, _ = process.communicate()
    line = stdout.decode('ascii')
    if line != '':
        output += line
        line = line.rstrip()
        log.info(f"$> {line}")

    return process.returncode, output
        
def shell(cmd, cwd=None):
    split = shlex.split(cmd)
    cmd = split[0]
    args = []
    if len(split) > 1:
        args = split[1:]
    return shell_split(cmd, args, cwd)