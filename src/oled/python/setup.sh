#!/bin/bash
if [ "${USER:-}" != 'root' ]; then echo "Run as root; sudo ${0} ${*}" &> /dev/stderr; exit 1; fi

apt update -qq -y
apt install -qq -y python3-pip libopenjp2-7 libtiff5
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade RPi.GPIO
python3 -m pip install --upgrade spidev
python3 -m pip install --upgrade Pillow
python3 -m pip install --upgrade flask
