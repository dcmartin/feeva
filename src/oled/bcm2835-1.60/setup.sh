#!/bin/bash
apt update -qq -y
apt install -qq -y automake
./configure
make install
