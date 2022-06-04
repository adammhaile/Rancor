#!/usr/bin/env bash

if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

apt-get install -y python3-systemd
apt-get install -y build-essential
apt-get install -y libsystemd-dev
apt-get install -y systemd-journal-remote
systemctl enable --now systemd-journal-gatewayd

python3 setup.py develop

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";

ln -sf ${SCRIPT_DIR}/timelapse.service /etc/systemd/system/timelapse.service
systemctl daemon-reload
systemctl enable timelapse.service
systemctl start timelapse.service