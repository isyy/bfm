## bfm build/install script ##
## copyright (C) 2016 isy ##
## under the GPLv3-License (SEE LICENSE.md) ##

printf "welcome to the bfm (brainf*ck-modified) installer!\npress [ENTER] to continue or any other key to abort the install.\n"
read -s -n 1 input
if [[ -z $input ]]; then
	if [ -f Makefile ]; then
		if [ -f bfm ]; then
			rm -rf bfm
		fi
		make
	fi
	sudo cp bfm /bin
	sudo cp bfm /usr/bin
fi
