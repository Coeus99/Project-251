#/bin/bash

if [[ -e /home/pi/Documents/Project-Nyx/images/image-0.jpeg ]] ; then
	echo "Nyx has already ran, please empty directories."
else
	while true ; do bash /home/pi/Documents/Project-Nyx/nyx.sh ; done
fi
