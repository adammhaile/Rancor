if [ -n "$SSH_CLIENT" ] || [ -n "$SSH_TTY" ]; then
    exit 0
fi


SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
cd ${SCRIPT_DIR}

export TERM=fbterm

# add -v to see resulting console char dimensions
fbterm --font-size=16 --font-names="AcPlus IBM BIOS" python3 ./main.py

export TERM=xterm