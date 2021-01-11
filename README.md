C gpio experiments on Raspberry PI 4B board.

The following 8 tests are included: ( see below for tests summary )
1. uart test
2. led test
3. button test
4. pwm led test
5. i2c lcd test
6. tongsong
7. servo
8. spi oled test

-------------------------------------------------------------------
To compile and flash to sd card:
cd rpi4b-c-gpio
Download OS:
wget https://downloads.raspberrypi.org/raspios_lite_armhf/images/raspios_lite_armhf-2020-12-04/2020-12-02-raspios-buster-armhf-lite.zip
unzip 2020-12-02-raspios-buster-armhf-lite.zip
Use balenaEtcher to burn img to sd card.
eject sd card.
Plugin sd card to PC.
To enable SPI add dtparam=spi=on in /boot/config.txt
sudo cp config.txt /media/$USER/boot
sync
sudo umount /media/$USER/boot
eject sd card.
Plugin the sd card to Raspberry PI 4B board.
Connect gpio Pin 8 to serial USB cable TX.
Connect gpio pin 10 to serial USB cable RX. 
Connect gpio pin 39 to serial USB cable ground. 
Type "script ~/outputfile.txt" on PC.
Plugin serial USB cable to PC.
Type "sudo screen /dev/ttyUSB0 115200" on PC.
Power on Raspberry PI 4B board.
It should prompt login message.
user pi
password raspberry
sudo raspi-config
set password, wifi, locale, timezone, peripheral etc.
vi nosleep.sh ( add following line to disable sleep feature )
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.ta
rget
./nosleep.sh
sudo dmesg -n 1
sudo vi /etc/rc.local ( add sudo dmesg -n 1 )
sudo ifconfig
sudo apt-get update
sudo apt-get upgrade
sync
sudo shutdown -h now
Power on Raspberry PI 4B board.
./nosleep.sh
sudo apt-get install python-dev python-pip python-setuptools python3-dev python3-pip python3-setuptools dnsutils apache2 vsftpd ftp
sudo cat /proc/device-tree/soc/spi@7e204000/status
sudo cat /proc/device-tree/soc/i2c@7e804000/status
sudo cat /proc/device-tree/soc/pwm@7e20c000/status
ls /sys/class/pwm
sudo cat /sys/kernel/debug/clk/clk_summary |grep pwm  ( 100 MHz )
sudo cat /sys/kernel/debug/clk/pwm/clk_rate
sudo apt-get install i2c-tools
sudo i2cdetect -y 1
adding uart on power on:
dtoverlay -a | grep uart
dtoverlay -h uart2       ( use pin 27, 28 )

-------------------------------------------------------------------------
Download gpio library on Raspberry PI 4B board:
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
gpio -v      ( make sure it's v2.52 or above )
gpio readall
cd ~/rpi4b-c-gpio
make gpio_test
sudo ./gpio_test
When done all tests, hit 'q' to exit tests.
sudo shutdown -h now
Power off Raspberry PI 4B board.
Unplug serial USB cable from PC.
Type "exit" on PC.

-------------------------------------------------------------------------
Here are the summary of the tests: ( see GPIO-Pinout-rpi4b.png and https://www.raspberrypi.org/documentation/usage/gpio)
These tests used Seeed Grove  starter kit LED, button, buzzer, Grove-LCD RGB Backlight V3.0 JHD1313M2, Analog Servo and Adafruit SSD1306 128x32 SPI OLED Display.
1. uart test.
   This test will send uart2 tx to uart2 rx for loopback.
   It sends ' ' to '~' to uart2 tx and receive ' ' to '~' from uart2 rx.
   Connect gpio pin 27 to pin 28.
2. led test.
   This test will blink led 5 times. 
   Connect gpio pin 18 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground.
3. button test. 
   Connect gpio pin 18 to led control. 
   Connect gpio pin 2 to led 5V. 
   Connect gpio pin 9 to led ground. 
   Connect gpio pin 16 to button control.
   Connect gpio pin 4 to button 5V.
   Connect gpio pin 6 to button ground.
4. pwm led test.
   This test will dim led 10 times.
   Connect gpio pin 33 to led control.
   Connect gpio pin 2 to led 5V.
   Connect gpio pin 9 to led ground.
5. i2c lcd test.
   This test will change lcd backlight color for 5 cycles.
   Then it will display two sentences on lcd display.
   Connect gpio pin 3 to lcd display SDA.
   Connect gpio pin 5 to lcd display SCL.
   Connect gpio pin 2 to lcd display 5V.
   Connect gpio pin 9 to lcd display ground.
6. tongsong.
   This test will generate song using buzzer.
   Connect gpio pin 33 to buzzer control.
   Connect gpio pin 2 to buzzer 5V.
   Connect gpio pin 9 to buzzer ground. 
7. servo.
   This test will turn servo 90 degree - 180 degree - 90 degree - 0 degree etc.
   Connect gpio pin 33 to servo control.
   Connect gpio pin 2 to servo 5V.
   Connect gpio pin 9 to servo ground.
8. spi oled test.
   This test will show some ascii characters on the oled display.
   Connect gpio pin 18 to oled display DC.
   Connect gpio pin 24 to oled display CS.
   Connect gpio pin 19 to oled display TX.
   Connect gpio pin 23 to oled display CLK.
   Connect gpio pin 1 to oled display 3.3V.
   Connect gpio pin 9 to oled display ground.

-----------------------------------------------------------------------------
