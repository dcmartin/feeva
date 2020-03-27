#
# REST API for working with NeoPixels.
#
# This is a minimal library to work with NeoPixels from within a Docker
# container. Many aspects of the awesome Adafruit "neopixel" library API
# are not exposed here (yet, maybe someday I will add, or maybe you could
# add and submit a PR). If you wish to use more features than are exposed
# here, please see the neopixel API documentation, here:
#    https://circuitpython.readthedocs.io/projects/neopixel/en/latest/api.html
#
# Written by Glen Darling, March 2020.
#

from flask import Flask
import json
import subprocess
import threading
import time

# Import the required libraries
import board
import neopixel

# REST API details
REST_API_BIND_ADDRESS = '0.0.0.0'
REST_API_PORT = 7777
webapp = Flask('neopixel')

# Raspberry Pi Broadcom GPIO pin numbers must not exceed this
BCM_GPIO_MAX = 26

# A global to indicate the number of NeoPixels that are connected
neopixel_count = 0

# The global array of neopixels
neopixels = None


# Validate the BCM GPIO number string
def valid_gpio(gpiostr):
  try:
    gpio = int(gpiostr)
    if gpio < 1 or gpio > BCM_GPIO_MAX:
      return False
    return True
  except:
    return False

# Validate the NeoPixel number string (any number greater than zero is fine!)
def valid_neopixel_max(maxstr):
  try:
    neopixel_max = int(maxstr)
    if neopixel_max < 0:
      return False
    return True
  except:
    return False

# Validate the NeoPixel number string
def valid_neopixel(neopixelstr):
  global neopixel_count
  try:
    neopixel = int(neopixelstr)
    if neopixel < 0 or neopixel > (neopixel_count - 1):
      return False
    return True
  except:
    return False

# Validate the r,g,b number string triplet
def valid_rgb(r, g, b):
  try:
    ri = int(r)
    gi = int(g)
    bi = int(b)
    if ri < 0 or ri > 255:
      return False
    if gi < 0 or gi > 255:
      return False
    if bi < 0 or bi > 255:
      return False
    return True
  except:
    return False


# The web server code


# INIT: <bcm-gpio>, <count>
#   Defines the Broadcom GPIO pin that will be used, and the count of NeoPixels
@webapp.route("/neopixel/v1/init/<bcmgpio>/<count>", methods=['POST'])
def neopixel_init(bcmgpio, count):
  global neopixel_count
  global neopixels
  if None != neopixels:
    return ('{"error": "NeoPixel library is already initialized for %d NeoPixels!"}\n' % neopixel_count)
  elif not valid_gpio(bcmgpio):
    return ('{"error": "GPIO number %s is not valid."}\n' % bcmgpio)
  elif not valid_neopixel_max(count):
    return ('{"error": "NeoPixel count %s is not valid."}\n' % count)
  else:
    try:
      neopixels = eval('neopixel.NeoPixel(board.D' + bcmgpio + ', ' + count + ')')
      neopixel_count = int(count)
      return ('{"initialized": {"gpio": %d, "count": %d}}"}\n' % (int(bcmgpio), neopixel_count))
    except:
      return ('{"error": "Failed to configure neopixel library using GPIO board.D%s, and count %d."}\n' % (bcmgpio, neopixel_count))


# POST: <pixel-number>/<r>/<g>/<b> where r, g, and b are in 0..255
@webapp.route("/neopixel/v1/<pixel>/<r>/<g>/<b>", methods=['POST'])
def neopixel_post(pixel, r, g, b):
  if None == neopixels:
    return ('{"error": "NeoPixels have not been initialized!"}\n')
  elif not valid_neopixel(pixel):
    return ('{"error": "NeoPixel number %s is not valid."}\n' % pixel)
  elif not valid_rgb(r, g, b):
    return ('{"error": "Neopixel color (%s,%s,%s) is not valid."}\n' % (r, g, b))
  else:
    n = int(pixel)
    ri = int(r)
    gi = int(g)
    bi = int(b)
    neopixels[n] = (ri, gi, bi)
    return ('{"success": {"neopixel": %d, "red": %d, "green": %d, "blue": %d}}\n' % (n, ri, gi, bi))


# Main program (to start the web server thread)
if __name__ == '__main__':
  webapp.run(host=REST_API_BIND_ADDRESS, port=REST_API_PORT)

