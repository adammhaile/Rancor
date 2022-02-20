# add -v to see resulting console char dimensions
SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
cd ${SCRIPT_DIR}
export TERM=fbterm
fbterm --font-size=16 --font-names="AcPlus IBM BIOS" python3 ./main.py
