#!/bin/bash

#install vcpkg if VCPKG_ROOT variable is set
if [[ -z "$VCPKG_ROOT" ]]; then
	echo "Please add following command: export VCPKG_ROOT=\$HOME/vcpkg to .bashrc file"
else
	#install dependecies
	sudo apt-get install curl unzip tar

	sudo git clone https://github.com/Microsoft/vcpkg.git $VCPKG_ROOT
	cd $VCPKG_ROOT && sudo ./bootstrap-vcpkg.sh && sudo ./vcpkg integrate install && sudo ./vcpkg integrate bash
fi


