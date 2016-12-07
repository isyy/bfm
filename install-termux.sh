
## bfm build/install script for termux ##
## copyright (C) 2016 isy ##
## under the GPLv3-License (SEE LICENSE.md) ##

printf "welcome to the bfm (brainf*ck-modified) installer for termux!\npress [ENTER] to continue or any other key to abort the install.\n"
read -s -n 1 input
if [[ -z $input ]]; then
	if [ -f Makefile ]; then
		if [ -f bfm ]; then
			rm -rf bfm
		fi
		make
	fi
  cp bfm $PREFIX/bin
fi
