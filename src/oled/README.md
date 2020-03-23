# `oled/README.md`

## Connect
Connect the OLED panel to the RaspberryPi using the provided cable; colors indicated in the image below are referenced in the following table; use the following `GPIO` pins.

Raspberry Pi|PIN|Color|RGB OLED|
---|---|---|---|
3.3V current|17|RED|`VCC`|
`GPIO24`|18|GREEN|`DC`|
`MOSI`|19|BLUE|`DIN`|	
Ground|20|BLACK|`GND`|
`GPIO25`|22|WHITE|`RST`|	
`SCLK`|23|YELLOW|`CLK`|	
`CE0`|24|ORANGE|`CS`|	

<img src="docs/gpio-cable-connect.png" width="50%">

## Build & test
Run the `make` command to build the `main` executable.  This program will run a series of tests to ensure proper installation, connection, and operation of the OLED display; for example

```
make
```

## Install for `python`
The provided Python libraries require additional packages to be installed; these packages must be installed using `pip` command.  Install the `pip` command as follows:

```
sudo apt install -qq -y python3-pip
sudo python3 -m pip install --upgrade pip
```

Then install the required packages; for example:

```
sudo python3 -m pip install --upgrade RPi.GPIO
sudo python3 -m pip install --upgrade spidev
sudo python3 -m pip install --upgrade Pillow
```

Ensure the `/dev/spidev0.0` device exists and set permissions for general access:

```
ls -al /dev/spidev0.0 && sudo chmod 666 /dev/spidev0.0 || echo "/dev/spidev.0.0 does not exist"
```

If the devices does not exist, please run `raspi-config` and enable the `SPI` interface.; for example:

```
sudo raspi-config
```

### Test `python`

Test using the provided `main.py`, for example:

```
ls -l /dev/spidev.0.0
cd python
python3 main.py
```

# Source Material
The following are the original sources utilized to build this component.

## Download `BCM2835` (optional)
Open Raspberry Pi terminal, and run the following commands:

```
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
tar zxvf bcm2835-1.60.tar.gz
cd bcm2835-1.60/
./configure
make
make check
sudo make install
```

Refer to the official website: http://www.airspayce.com/mikem/bcm2835/

## Install `wiringpi` (optional)
To install WiringPi which is an option in the OLED driver software; see the `makefile`

```
sudo apt install -qq -y wiringpi
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
```

Test installation, for example:

```
# Run gpio -v version 2.52 will appear, if there is no description, installation error
gpio -v
```

## Download original drivers (optional)
Download the drivers and test the assembly and installation of the OLED display.  
The `main` program will display a demonstration on the screen verifying proper installation.

```
sudo apt install -qq -y p7zip-full
wget http://www.waveshare.net/w/upload/e/eb/1.5inch_RGB_OLED_Module_Code.7z
mkdir code
cd code
7z x ../1.5inch_RGB_OLED_Module_Code.7z
cd RaspberryPi/c/
chmod 777 ./main
sudo ./main
```

## Clone original repository (optional)

```
git clone https : //github.com/waveshare/1.5inch-RGB-OLED-Module
```
