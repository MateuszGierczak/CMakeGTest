#!/bin/bash

#gcc and g++
sudo apt-get install build-essential
sudo apt-get install gcc-7 g++-7 gcc-8 g++-8 gcc-9 g++-9

#The commands below will configure alternative for each version and associate a priority with it. The default version is the one with the highest priority, in our case that is gcc-9.
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8 --slave /usr/bin/gcov gcov /usr/bin/gcov-8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 70 --slave /usr/bin/g++ g++ /usr/bin/g++-7 --slave /usr/bin/gcov gcov /usr/bin/gcov-7

#Later if you want to change the default version use the update-alternatives command:
#sudo update-alternatives --config gcc
