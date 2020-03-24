#!/bin/bash
apt update -qq -y
apt install -qq -y python3-pip libopenjp2-7 libtiff5
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade RPi.GPIO
python3 -m pip install --upgrade spidev
python3 -m pip install --upgrade Pillow
