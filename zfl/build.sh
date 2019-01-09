#!/bin/bash

cd ../


make itop4412_zfl_defconfig
echo "make itop4412_zfl_defconfig !"

make

cp u-boot.bin ./zfl/
echo "copy u-boot.bin done."

cd spl/
if [ ! -f itop4412-spl.bin ] ; then
	echo "notice: not found itop4412-spl.bin !"
	cd ../zfl/
	exit 0
else
	echo "copying itop4412-spl.bin..."
fi

cp itop4412-spl.bin ../zfl/
echo "copy u-boot-spl.bin done."

echo "build success !!!"
