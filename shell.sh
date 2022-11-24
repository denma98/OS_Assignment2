#!/bin/bash
unxz -v linux-5.19.9.tar.xz
tar xvf linux-5.19.9.tar
cd linux-5.19.9
wget --no-check-certificate https://raw.githubusercontent.com/denma98/OS/main/config-rev-9-gold

cp config-rev-9-gold .config
make mrproper

make -j2
