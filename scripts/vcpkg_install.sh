#!/bin/bash

#install dependecies
sudo apt-get install curl unzip tar

#install vcpkg
vcpkg_dir_name=vcpkg
vcpkg_path=$HOME/$vcpkg_dir_name

git clone https://github.com/Microsoft/vcpkg.git $vcpkg_path

cd $vcpkg_path && ./bootstrap-vcpkg.sh && ./vcpkg integrate install && rm -rf $vcpkg_path


