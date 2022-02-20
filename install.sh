# set -u
# trap "exit 1" TERM
# export TOP_PID=$$

# if [ "${EUID:-$(id -u)}" -gt 0 ];
# then
#     echo "Must run as root!"
#     exit 1
# fi

# apt-get install python3-systemd

# apt-get install systemd-devel
# # apt-get install build-essential
# apt-get install libsystemd-dev
# apt-get install libsystemd-daemon-dev
# apt-get install systemd-journal-remote
# systemctl enable --now systemd-journal-gatewayd