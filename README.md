# This is the DPS941 Robot - Colaberative repo

Members
## Robotics Group 5
Adam

Edwin

Kevin

Vimal


### Robot C Download Link

http://www.robotc.net/download/arduino/ 

### Other Links 

Login and make and account for RobotC IDE

https://www.vexrobotics.com/customer/account/login/

BeagleBone Model

https://www.digikey.com/products/en?lang=en&site=us&KeyWords=BBBWL-SC-562-ND

Debian Images

https://beagleboard.org/latest-images

## Getting the board ready

After getting the latest image of debian (this readme was done with debian 9.6 Oct 5 edition)
``cd /boot``

``sudo nano uEnv.txt``

Change the dtb to:
``#dtb= `` to 
``dtb=am335x-boneblack-wireless-roboticscape.dtb``

###Set up some internet in order to install the latest packages. Namely zip and gdb.

SSH into the BBB using root@192.168.7.2  <-- this is the default USB IP address for your BBB

>> ifconfig 

ensure that you can see all interface channels on the board (usb0 , usb1, eth0, wlan0)

>> ls -l /dev/ttyO*

>> $ /dev/ttyO4 -> ttyS4 (one for each available uart port on your board)



you should have an output that looks like this:

STEP1:

>> connmanctl

From the connmanctl prompt, type in the following commands:

-- tether wifi disable

To have internet connection - you can have your beaglebone connect to the internet with  > connmanctl

``connmanctl > agent on``

``connmanctl > scan wifi``

``connmanctl > services``

``connmanctl > connect [_____Key Token Here_______]``

<Find your home router and copy the service tag key>. You can later link to the BeagleBone in order to restore internet access to your device.
      

NOTE:  This will connect your BBB wireless to your home router giving the BBB internet access

STEP2:

exit the connmanctl program and get back to a standard command prompt on the BBB

STEP3:

> sudo apt-get update

NOTE:  Let this run, it will update the package DBs and could take several minutes.  Don't interrupt it

STEP4:

> sudo apt-get install zip

NOTE:  This will install the compression zip utilities on the BBB.  These are required for Visual Studio to create the remote GDB connections

It may also be necessary to updage GDB - 

>sudo apt-get install GDB


STEP5:

Start connmanctl again and type

-- tether wifi enable

STEP6:

Connect your laptop to the BeagleBone SSID, and go through the process of creating a cross-compiler remote connection with Visual Studio.

The default password for the connection is: BeagleBone 




## Configuring Visual Studios

Ensure you have the latest packages to deploy onto a ARM (Linux) system.

Make a new Empty Project

Tools >
      Options > 
              Cross Platfrom > 
                             Connection Manager

Your host name should be something like 192.168.8.1 and enter in any other credentials for logging in


## Latest update


GND TP1 then run as root: 

dd if=/opt/scripts/device/bone/bbbw-eeprom.dump 
of=/sys/devices/platform/ocp/44e0b000.i2c/i2c-0/0-0050/eeprom 

(that dd line is "1" line not two..) 

reboot and everything will be okay.. 

sudo config-pin P9.11 uart
sudo config-pin P9.13 uart


Note : to check your ip open a command prompt and type 'ipconfig' - you will see your default gateway has changed (since we are connected to the Bone)

## Configure the UART ports (WIP)

When configuring the board with ``dtb=am335x-boneblack-wireless-roboticscape.dtb`` all UART ports were open.




