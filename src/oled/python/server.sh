#!/bin/bash
pids=($(ps alxwww | egrep server.py | egrep -v grep | awk '{ print $1 }'))
if [ ${#pids[@]} -gt 0 ]; then sudo kill -9 ${pids[@]}; fi
sudo python3 server.py &> server.out &
sleep 10
curl -v -d @test.json 127.0.0.1:7777/oled/v1/display/picture
