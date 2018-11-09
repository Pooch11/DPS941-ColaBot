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

Login and make and account
https://www.vexrobotics.com/customer/account/login/

BeagleBone Model
https://www.digikey.com/products/en?lang=en&site=us&KeyWords=BBBWL-SC-562-ND

## Getting the board ready



SSH into the BBB using root@192.168.7.2  <-- this is the default USB IP address for your BBB

>> ifconfig 

ensure that you can see all interface channels on the board (usb0 , usb1, eth0, wlan0)

STEP1:

>> connmanctl

From the connmanctl prompt, type in the following commands:

-- tether wifi disable

-- agent on

-- scan wifi

-- services

<Find your home router and copy the service tag key>

-- connect <paste the service tag key>

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

To have internet connection - you can have your beaglebone connect to the internet with  > connmanctl
`connmanctl > agent on`
`connmanctl > scan wifi`
`connmanctl > services`
`connmanctl > connect [_____Key Token Here_______]`

## Configuring Visual Studios

Ensure you have the latest packages to deploy onto a ARM (Linux) system.

Make a new Empty Project

Tools >
      Options > 
              Cross Platfrom > 
                             Connection Manager

Your host name should be something like 192.168.8.1 and enter in any other credentials for logging in

Note : to check your ip open a command prompt and type 'ipconfig' - you will see your default gateway has changed (since we are connected to the Bone)





