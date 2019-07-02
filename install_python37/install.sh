#! /bin/sh

# https://websiteforstudents.com/installing-the-latest-python-3-7-on-ubuntu-16-04-18-04/


sudo apt update
sudo apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev wget

cd /tmp
wget https://www.python.org/ftp/python/3.7.2/Python-3.7.2.tar.xz

tar -xf Python-3.7.2.tar.xz
cd Python-3.7.2
./configure --enable-optimizations

make -j 8
sudo make altinstall
