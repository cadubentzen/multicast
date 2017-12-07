# Multicast project #

This project as developed as part of a Real-time Systems Engineering course from Universidade Federal do Rio Grande do Norte.

##### Youtube Video Explanation #####
**TODO**

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/cfzUDSFr0QY/0.jpg)](https://youtu.be/cfzUDSFr0QY)

![BeagleBone](http://beagleboard.org/static/images/cape-headers.png)

## Building ##

The compilation process uses CMake >= 2.8 and a few flags may configure the project:
- `CMAKE_BUILD_TYPE`: Release or Debug can be used. Debug enables a few extra logs, so the programs will be more verbose.
- `BEAGLE`: Setting this enables compilation for BeagleBone Black, using ADC, GPIO and LCD peripherals.

For example, to compile in Release mode for the BeagleBone Black:

```
$ mkdir Release
$ cd Release
$ cmake -DCMAKE_BUILD_TYPE=Release -DBEAGLE=ON ..
$ make
```

In case `-DBEAGLE` is not passed or is passed as OFF, fake modules will generate values for the ADC and GPIO modules and the LCD module will print to the console.

## Running ##
After compiling, in the Debug or Release folder there will be two executables:
- **beagle**: This program is supposed to run on the BeagleBone during project presentation. To run it, our group will run `./beagle 1` because we are group number 1.
- **app**: This is the app that receives two floating points values from a ADC coming from a Multicast Socket and generates a bool array writing to another Multicast socket in a different port. To run it, we could run from example `./app 9701 9805` which means it will read float-point values from port 9701 and write a boolean array to port 9805. This program can run in a different computer or in the BeagleBone as well.

## Project Description (Portuguese) ##
Trabalho Final - Comunicação Multicast

Desenvolver as seguintes aplicações:

- Na Beagle Board

  - Thread que lê a cada segundo valores de 02 ADCs (ADC1 e ADC2), conectados respectivamente a 02 potenciômetros. Os valores devem estar entre 0 e 1. Enviar esses valores num array de 02 posições pelo endereço multicast 225.0.0.37 porta 97-- (para o grupo 01, porta 9701; para o grupo 02, porta 9702 e assim por diante).

  - Thread que recebe no endereço 225.0.0.37 e porta 98--, um array de booleano de 08 posições. A porta deve ser configurada a cada segundo por valores lidos de 04 chaves digitais conectadas a portas GPIO. Se a configuração das chaves for 0101 (por exemplo), o valor da porta será 9805 e assim por diante. Os valores contidos no vetor booleano devem ser escritos em portas GPIO associadas a um dysplay de 07 segmentos.

 

- Escrever um programa num computador (denominado de aplicação genérica) lê os arrays ofiundos das portas 97-- e escreve um array booleano de 08 posições nas portas 98--.

  - O grupo está livre para escrever qualquer programa que utilize essas funcionalidades.

As Beagles Boards deverão estar conectadas via Wifi. Quando conectadas no Wifi, as placas precisam estar alimentadas na tomada (via USB não funciona).

## Useful Information ##
### Connecting to the Bleaglebone Black ###
On a Linux system
1. Connect your BeagleBone to your computer by using a Mini USB cable.
2. Open the terminal and type `ifconfig`. You should see a network adapter that has one of the following ips `192.168.7.1` or `192.168.6.1`
3. Then the BeagleBone itself will have the ip `192.168.6.2` or `192.168.7.2`
4. Then connect via ssh with the command `ssh debian@192.168.6.2`, use sudo and/or change the ip if necessary. Make sure you're connecting with the correct username in ssh

#### Share internet connection over the USB ####
Reference: <https://elementztechblog.wordpress.com/2014/12/22/sharing-internet-using-network-over-usb-in-beaglebone-black/>

On the BeagleBone Board, run (mind the correct ip address, it could be either `192.168.6.#` or `192.168.7.#`)
```
ifconfig usb0 192.168.6.2
route add default gw 192.168.6.1
```

On the PC host, run (ATTENTION: change the `wlan0` to yout internet interface and `eth0` to the network adapter of the BeagleBone. And mind the ip address as well)
```
sudo su
ifconfig eth0 192.168.6.1
iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
iptables --append FORWARD --in-interface eth0 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward
```

## Configure ethernet ##

see host information ip 10.42.0.1


ifconfig eth0 10.42.0.2
ifconfig eth0 netmask 255.255.255.0
route add default gw 10.42.0.1 eth0


## Enable ADC read in Kernel 4.x ##

With root provileges, run
```
sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"
```

And to read from analog port, run
```
cat "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
```
in `in_voltage0_raw` change 0 to the number of the ADC, from 0 to 6.

See references to make this permanent on reboot
## Enable LCD Display on Beagle ##

If you want to display the result on a LCD display, first follow the steps in README of <https://github.com/gorskima/hd44780-i2c> to compile and add kernel module of LCD I2C display (see the usage below, copied and modified from gorskima).

#### Usage ####
1. In the train-control-beagle folder, run `insmod ../hd44780-i2c/hd44780.ko` to add the kernel module
2. Let the I2C adapter know that there's a new device attached: `echo hd44780 0x27 > /sys/class/i2c-adapter/i2c-2/new_device`. You may need to replace the device's I2C address and adapter path with proper values. For example, consider changing the `i2c-1` to `i2c-2`, if you get `bash: /sys/class/i2c-adapter/i2c-1/new_device: No such file or directory`
3. At this point a new device should appear (`/dev/lcd0`) and you should be able to write to it
4. For more information, see the github repository of the hd44780 driver.

Disable cursor blink and cursos display
```
echo "0" > /sys/class/hd44780/lcd0/cursor_blink
echo "0" > /sys/class/hd44780/lcd0/cursor_display
```

## References ##
1. ADC on BeagleBone. <http://beaglebone.cameon.net/home/reading-the-analog-inputs-adc>
2. How to read ADC values in kernel 4.x. <https://askubuntu.com/questions/882433/enable-adc-input-on-beaglebone-with-4-x-kernel>
3. <https://www.teachmemicro.com/beaglebone-black-adc/>
