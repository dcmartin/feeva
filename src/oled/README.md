# `SOFTWARE.md`


## `BCM2835`
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

## WiringPi

```
sudo apt install -qq -y wiringpi
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
gpio -v
# Run gpio -v version 2.52 will appear, if there is no description, installation error
```

## Python

```
sudo apt install -qq -y python-pip
sudo pip install Rpi.GPIO
sudo pip install spidev
```


## Copy drivers
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

## Optional - clone repository

```
git clone https : //github.com/waveshare/1.5inch-RGB-OLED-Module
```
