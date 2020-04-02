#!/bin/bash
while true; do
  echo "Waiting" &> /dev/stderr
  mosquitto_sub -C 1 -h 192.168.1.50 -u username -P password -t "+/+/+/event/end/+" > out.json
  if [ -s out.json ] && [ $(jq '.image!=null' out.json) = 'true' ]; then
    echo "Displaying" &> /dev/stderr
    curl -sSL -d @out.json 127.0.0.1:7777/oled/v1/display/picture
  else
    echo "Skipping" &> /dev/stderr
  fi
done
