# `oled/README.md`

## Enable `python`
Python libraries included require two additional packages to be installed using `pip`, for example:

```
sudo apt install -qq -y python-pip
sudo pip install Rpi.GPIO
sudo pip install spidev
```

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
