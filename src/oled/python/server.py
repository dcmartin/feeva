###
# src/oled/python/server.py
###

import json
import subprocess
import threading
import time

import RPi.GPIO as GPIO
import OLED_Driver as OLED

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from PIL import ImageColor

## utility

def Display_Picture(File_Name):
    image = Image.open(File_Name)
    OLED.Display_Image(image)

## v1/test/ API

from flask import Flask, request
webapp = Flask('oled')

@webapp.route("/oled/v1/test/text", methods=['GET'])
def Test_Text():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype('cambriab.ttf',24)

    draw.text((0, 12), 'WaveShare', fill = "BLUE", font = font)
    draw.text((0, 36), 'Electronic', fill = "BLUE",font = font)
    draw.text((20, 72), '1.5 inch', fill = "CYAN", font = font)
    draw.text((10, 96), 'R', fill = "RED", font = font)
    draw.text((25, 96), 'G', fill = "GREEN", font = font)
    draw.text((40, 96), 'B', fill = "BLUE", font = font)
    draw.text((55, 96), ' OLED', fill = "CYAN", font = font)

    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/pattern", methods=['GET'])
def Test_Pattern():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    
    draw.line([(0,8), (127,8)],   fill = "RED",    width = 16)
    draw.line([(0,24),(127,24)],  fill = "YELLOW", width = 16)
    draw.line([(0,40),(127,40)],  fill = "GREEN",  width = 16)
    draw.line([(0,56),(127,56)],  fill = "CYAN",   width = 16)
    draw.line([(0,72),(127,72)],  fill = "BLUE",   width = 16)
    draw.line([(0,88),(127,88)],  fill = "MAGENTA",width = 16)
    draw.line([(0,104),(127,104)],fill = "BLACK",  width = 16)
    draw.line([(0,120),(127,120)],fill = "WHITE",  width = 16)
    
    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/lines", methods=['GET'])
def Test_Lines():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)

    for x in range(0, int((OLED.SSD1351_WIDTH-1)/2), 6):
        draw.line([(0, 0), (x, OLED.SSD1351_HEIGHT - 1)], fill = "RED", width = 1)
        draw.line([(0, 0), ((OLED.SSD1351_WIDTH-1) - x, OLED.SSD1351_HEIGHT - 1)], fill = "RED", width = 1)
        draw.line([(0, 0), (OLED.SSD1351_WIDTH - 1, x)], fill = "RED", width = 1)
        draw.line([(0, 0), (OLED.SSD1351_WIDTH - 1, (OLED.SSD1351_HEIGHT-1) - x)], fill = "RED", width = 1)
        OLED.Display_Image(image)
    OLED.Delay(250)
    draw.rectangle([0, 0, OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1], fill = "BLACK", outline = "BLACK")

    for x in range(0, int((OLED.SSD1351_WIDTH-1)/2), 6):
        draw.line([(OLED.SSD1351_WIDTH - 1, 0), (x, OLED.SSD1351_HEIGHT - 1)], fill = "YELLOW", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, 0), (x + int((OLED.SSD1351_WIDTH-1)/2), OLED.SSD1351_HEIGHT - 1)], fill = "YELLOW", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, 0), (0, x)], fill = "YELLOW", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, 0), (0, x + int((OLED.SSD1351_HEIGHT-1)/2))], fill = "YELLOW", width = 1)
        OLED.Display_Image(image)
    OLED.Delay(250)
    draw.rectangle([0, 0, OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1], fill = "BLACK", outline = "BLACK")

    for x in range(0, int((OLED.SSD1351_WIDTH-1)/2), 6):
        draw.line([(0, OLED.SSD1351_HEIGHT - 1), (x, 0)], fill = "BLUE", width = 1)
        draw.line([(0, OLED.SSD1351_HEIGHT - 1), (x + int((OLED.SSD1351_WIDTH-1)/2), 0)], fill = "BLUE", width = 1)
        draw.line([(0, OLED.SSD1351_HEIGHT - 1), (OLED.SSD1351_WIDTH - 1, x)], fill = "BLUE", width = 1)
        draw.line([(0, OLED.SSD1351_HEIGHT - 1), (OLED.SSD1351_WIDTH - 1, x + (OLED.SSD1351_HEIGHT-1)/2)], fill = "BLUE", width = 1)
        OLED.Display_Image(image)
    draw.rectangle([0, 0, OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1], fill = "BLACK", outline = "BLACK")
    OLED.Delay(250)
    
    for x in range(0, int((OLED.SSD1351_WIDTH-1)/2), 6):
        draw.line([(OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1), (x, 0)], fill = "GREEN", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1), (x + int((OLED.SSD1351_WIDTH-1)/2), 0)], fill = "GREEN", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1), (0, x)], fill = "GREEN", width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1), (0, x + int((OLED.SSD1351_HEIGHT-1)/2))], fill = "GREEN", width = 1)
        OLED.Display_Image(image)
    draw.rectangle([0, 0, OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1], fill = "BLACK")
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/hv-lines", methods=['GET'])
def Test_HV_Lines():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    
    for y in range(0, OLED.SSD1351_HEIGHT - 1, 5):
        draw.line([(0, y), (OLED.SSD1351_WIDTH - 1, y)], fill = "WHITE", width = 1)
    OLED.Display_Image(image)
    OLED.Delay(250)
    for x in range(0, OLED.SSD1351_WIDTH - 1, 5):
        draw.line([(x, 0), (x, OLED.SSD1351_HEIGHT - 1)], fill = "WHITE", width = 1)
    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/rects", methods=['GET'])
def Test_Rects():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    
    for x in range(0, int((OLED.SSD1351_WIDTH-1)/2), 6):
        draw.rectangle([(x, x), (OLED.SSD1351_WIDTH- 1 - x, OLED.SSD1351_HEIGHT-1 - x)], fill = None, outline = "WHITE")
    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/fillrects", methods=['GET'])
def Test_FillRects(): 
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    
    for x in range(OLED.SSD1351_HEIGHT-1, int((OLED.SSD1351_HEIGHT-1)/2), -6):
        draw.rectangle([(x, x), ((OLED.SSD1351_WIDTH-1) - x, (OLED.SSD1351_HEIGHT-1) - x)], fill = "BLUE", outline = "BLUE")
        draw.rectangle([(x, x), ((OLED.SSD1351_WIDTH-1) - x, (OLED.SSD1351_HEIGHT-1) - x)], fill = None, outline = "YELLOW")
    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/circles", methods=['GET'])
def Test_Circles():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)

    draw.ellipse([(0, 0), (OLED.SSD1351_WIDTH - 1, OLED.SSD1351_HEIGHT - 1)], fill = "BLUE", outline = "BLUE")
    OLED.Display_Image(image)
    OLED.Delay(500)
    for r in range(0, int(OLED.SSD1351_WIDTH/2) + 4, 4):
        draw.ellipse([(r, r), ((OLED.SSD1351_WIDTH-1) - r, (OLED.SSD1351_HEIGHT-1) - r)], fill = None, outline = "YELLOW")
    OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/triangles", methods=['GET'])
def Test_Triangles():
    image = Image.new("RGB", (OLED.SSD1351_WIDTH, OLED.SSD1351_HEIGHT), "BLACK")
    draw = ImageDraw.Draw(image)
    
    for i in range(0, int(OLED.SSD1351_WIDTH/2), 4):
        draw.line([(i, OLED.SSD1351_HEIGHT - 1 - i), (OLED.SSD1351_WIDTH/2, i)], fill = (255 - i*4, i*4, 255 - i*4), width = 1)
        draw.line([(i, OLED.SSD1351_HEIGHT - 1 - i), (OLED.SSD1351_WIDTH - 1 - i, OLED.SSD1351_HEIGHT - 1 - i)], fill = (i*4, i*4 ,255 - i*4), width = 1)
        draw.line([(OLED.SSD1351_WIDTH - 1 - i, OLED.SSD1351_HEIGHT - 1 - i), (OLED.SSD1351_WIDTH/2, i)], fill = (i*4, 255 - i*4, i*4), width = 1)
        OLED.Display_Image(image)
    return ('{"success": true}\n' % ())

@webapp.route("/oled/v1/test/picture", methods=['GET'])
def Test_Picture():
  Display_Picture("picture1.jpg")
  Display_Picture("picture2.jpg")
  Display_Picture("picture3.jpg")
  Display_Picture("picture4.jpg")
  return ('{"success": {"file": "%s"}}\n' % (File_Name))

## POST

import numpy as np
import cv2

@webapp.route("/oled/v1/display/picture", methods=['POST'])
def displayPicture():
  r = request
  nparr = np.fromstring(r.data, np.uint8)
  img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
  OLED.Display_Image(image)
  return ('{"success": true}\n' % ())

###
### MAIN
###

REST_API_BIND_ADDRESS = '0.0.0.0'
REST_API_PORT = 7777

try:
  def main():
    OLED.Device_Init()
    webapp.run(host=REST_API_BIND_ADDRESS, port=REST_API_PORT)

  if __name__ == '__main__':
    main()

except:
  OLED.Clear_Screen()
  GPIO.cleanup()
