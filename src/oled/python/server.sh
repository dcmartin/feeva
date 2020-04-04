#!/bin/bash
if [ "${USER:-}" != 'root' ]; then echo "Run as root; sudo ${0} ${*}" &> /dev/stderr; exit 1; fi

pids=($(ps alxwww | egrep server.py | egrep -v grep | awk '{ print $1 }'))
if [ ${#pids[@]} -gt 0 ]; then kill -9 ${pids[@]}; fi
python3 server.py &
echo "Testing; curl -v -d @test.json 127.0.0.1:7777/oled/v1/display/picture" &> /dev/stderr
curl -v -d @test.json 127.0.0.1:7777/oled/v1/display/picture
