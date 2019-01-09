#!/bin/bash

if [ ! -f E4412_N.bl1.bin ] ; then
	echo "not find files: E4412_N.bl1.bin !!!"
	exit 0
fi

echo "writting ..."

signed_bl1_position=1
bl2_position=17
uboot_position=65

if [ -z $1 ] ; then
	#<BL1 fusing>
	echo "---------------------------------------"
	echo "BL1 fusing"
	dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=/dev/sdb seek=$signed_bl1_position

	#<BL2 fusing>
	echo "---------------------------------------"
	echo "BL2 fusing"
	dd iflag=dsync oflag=dsync if=./itop4412-spl.bin of=/dev/sdb seek=$bl2_position

	#<u-boot fusing>
	echo "---------------------------------------"
	echo "u-boot fusing"
	dd iflag=dsync oflag=dsync if=./u-boot.bin of=/dev/sdb seek=$uboot_position
else
	#<BL1 fusing>
	echo "---------------------------------------"
	echo "BL1 fusing"
	dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

	#<BL2 fusing>
	echo "---------------------------------------"
	echo "BL2 fusing"
	dd iflag=dsync oflag=dsync if=./itop4412-spl.bin of=$1 seek=$bl2_position

	#<u-boot fusing>
	echo "---------------------------------------"
	echo "u-boot fusing"
	dd iflag=dsync oflag=dsync if=./u-boot.bin of=$1 seek=$uboot_position
fi

echo "writting success"
