#!/bin/bash

cd ./zfl

if [ -z $1 ] ; then
	echo "Wrong Parameter !!!"
	echo "--- 1 编译 ---"
	echo "--- 2 清除生成的文件 ---"
	echo "--- 3 烧写bin到SD卡 ---"
	exit 0
fi

if [ $1 -gt 3 ] ; then
	echo "Wrong Parameter !!!"
	echo "--- 1 编译 ---"
	echo "--- 2 清除生成的文件 ---"
	echo "--- 3 烧写bin到SD卡 ---"
	exit 0
fi

if [ $1 -eq 1 ] ; then
	echo "--- 编译uboot ---> "
	./build.sh
	exit 0
fi

if [ $1 -eq 2 ] ; then
	echo "--- 清除生成的文件 ---> "
	./clean.sh
	exit 0
fi

if [ $1 -eq 3 ] ; then
	echo "--- 烧写bin到SD卡 ---> "
	sudo ./mkuboot.sh
	exit 0
fi

