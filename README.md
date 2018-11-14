# This is the DPS941 Robot - Colaberative repo

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

With Debian Image 2018-10-01 flash the board and restart

### Login
Credentials: debian Password: temppwd

### Run this command

Check the version

debian@beaglebone:~$ sudo /opt/scripts/tools/version.sh
### Output
```
git:/opt/scripts/:[1aa73453b2c980b75e31e83dab7dd8b6696f10c7]
]eprom:[A335BNLT▒O
model:[TI_AM335x_BeagleBone_Black]
dogtag:[BeagleBoard.org Debian Image 2018-10-01]
bootloader:[eMMC-(default)]:[/dev/mmcblk1]:[U-Boot 2018.09-00002-g0b54a51eee]:[location: dd MBR
kernel:[4.4.113-ti-r149]
nodejs:[v4.9.1]
device-tree-override:[dtb=]
uboot_overlay_options:[enable_uboot_overlays=1]
uboot_overlay_options:[uboot_overlay_pru=/lib/firmware/AM335X-PRU-RPROC-4-4-TI-00A0.dtbo]
uboot_overlay_options:[enable_uboot_cape_universal=1]
pkg check: to individually upgrade run: [sudo apt install --only-upgrade <pkg>]
pkg:[bb-cape-overlays]:[4.4.20180928.0-0rcnee0~jessie+20180928]
pkg:[bb-wl18xx-firmware]:[1.20180517-0rcnee0~jessie+20180517]
pkg:[kmod]:[18-3rcnee1~jessie+20171005]
pkg:[roboticscape]:[0.3.4-git20170602-0rcnee4~jessie+20171108]:[GOT_REPLACED_BY_NEXT]
WARNING:pkg:[librobotcontrol]:[NOT_INSTALLED]
pkg:[firmware-ti-connectivity]:[20170823-1rcnee1~jessie+20180328]
groups:[debian : debian adm kmem dialout cdrom floppy audio dip video plugdev users systemd-jou
cmdline:[console=ttyO0,115200n8 bone_capemgr.uboot_capemgr_enabled=1 root=/dev/mmcblk1p1 ro roo
dmesg | grep pinctrl-single
[    1.193856] pinctrl-single 44e10800.pinmux: 142 pins at pa f9e10800 size 568
dmesg | grep gpio-of-helper
[    1.194910] gpio-of-helper ocp:cape-universal: Allocated GPIO id=0
[    1.195525] gpio-of-helper ocp:cape-universal: Allocated GPIO id=1
[    1.195683] gpio-of-helper ocp:cape-universal: Allocated GPIO id=2
[    1.195824] gpio-of-helper ocp:cape-universal: Allocated GPIO id=3
[    1.195975] gpio-of-helper ocp:cape-universal: Allocated GPIO id=4
[    1.196113] gpio-of-helper ocp:cape-universal: Allocated GPIO id=5
[    1.196252] gpio-of-helper ocp:cape-universal: Allocated GPIO id=6
[    1.196398] gpio-of-helper ocp:cape-universal: Allocated GPIO id=7
[    1.196575] gpio-of-helper ocp:cape-universal: Allocated GPIO id=8
[    1.196728] gpio-of-helper ocp:cape-universal: Allocated GPIO id=9
[    1.196866] gpio-of-helper ocp:cape-universal: Allocated GPIO id=10
[    1.197005] gpio-of-helper ocp:cape-universal: Allocated GPIO id=11
[    1.197157] gpio-of-helper ocp:cape-universal: Allocated GPIO id=12
[    1.197298] gpio-of-helper ocp:cape-universal: Allocated GPIO id=13
[    1.197437] gpio-of-helper ocp:cape-universal: Allocated GPIO id=14
[    1.197581] gpio-of-helper ocp:cape-universal: Allocated GPIO id=15
[    1.197724] gpio-of-helper ocp:cape-universal: Allocated GPIO id=16
[    1.197880] gpio-of-helper ocp:cape-universal: Allocated GPIO id=17
[    1.198021] gpio-of-helper ocp:cape-universal: Allocated GPIO id=18
[    1.198167] gpio-of-helper ocp:cape-universal: Allocated GPIO id=19
[    1.198317] gpio-of-helper ocp:cape-universal: Allocated GPIO id=20
[    1.198502] gpio-of-helper ocp:cape-universal: Allocated GPIO id=21
[    1.198645] gpio-of-helper ocp:cape-universal: Allocated GPIO id=22
[    1.198793] gpio-of-helper ocp:cape-universal: Allocated GPIO id=23
[    1.199250] gpio-of-helper ocp:cape-universal: Allocated GPIO id=24
[    1.199433] gpio-of-helper ocp:cape-universal: Allocated GPIO id=25
[    1.199592] gpio-of-helper ocp:cape-universal: Allocated GPIO id=26
[    1.199738] gpio-of-helper ocp:cape-universal: Allocated GPIO id=27
[    1.199892] gpio-of-helper ocp:cape-universal: Allocated GPIO id=28
[    1.200040] gpio-of-helper ocp:cape-universal: Allocated GPIO id=29
[    1.200184] gpio-of-helper ocp:cape-universal: Allocated GPIO id=30
[    1.200337] gpio-of-helper ocp:cape-universal: Allocated GPIO id=31
[    1.200473] gpio-of-helper ocp:cape-universal: Allocated GPIO id=32
[    1.200602] gpio-of-helper ocp:cape-universal: Allocated GPIO id=33
[    1.200739] gpio-of-helper ocp:cape-universal: Allocated GPIO id=34
[    1.200750] gpio-of-helper ocp:cape-universal: ready
END
```

### If your wlan0 is not showing up you need to do these additional steps

Get a jumper cable wire and connect GND to TP1 then

``sudo dd if=/opt/scripts/device/bone/bbbw-eeprom.dump of=/sys/devices/platform/ocp/44e0b000.i2c/i2c-0/0-0050/eeprom ``

``sudo reboot``

Disconnect the wire

### Check Ports

`` ls -l /dev/ttyO*``

you should have an output that looks like this:

![ttyO*](https://i.imgur.com/TGbXa8T.png)

### Configure pins for uart protocol

``sudo config-pin P9.11 uart``

``sudo config-pin P9.13 uart``

## Run code on RobotC

Configure the robot c code from this repo (TelemetryCode.c) to communicate properly with these pins 

While RobotC is broadcasting - use the cat command to see if the output is being received.
![img](https://i.imgur.com/Fhaj1Yc.png)

### To install the latest packages. Namely zip and gdb in order to execute code remotely.

We need internet connectivity on the Beagle Bone.
SSH into the BBB using root@192.168.7.2  <-- this is the default USB IP address for your BBB

>> ifconfig 

ensure that you can see all interface channels on the board (usb0 , usb1, eth0, wlan0)

STEP1:

>> connmanctl

From the connmanctl prompt, type in the following commands:

-- tether wifi disable

To have internet connection - you can have your beaglebone connect to the internet with  > connmanctl

``connmanctl > agent on``

``connmanctl > scan wifi``

``connmanctl > services``

``connmanctl > connect [_____Key Token Here_______]``

<Find your home router or hotspot and copy the service tag key>. You can later link to the BeagleBone in order to restore internet access to your device.

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

Your host name should be something like 192.168.8.1 and enter in any other needed credentials for logging in

You should be able to run UartConnection.cpp on the beaglebone.









