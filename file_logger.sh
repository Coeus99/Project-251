#!/bin/bash

log="/home/pi/Project-Nyx/logs/file_logger.log"
images="/home/pi/Project-Nyx/images/"

while true
do
	echo -e "At time $(date +%Y%m%d%H%M%S) these images existed:\n{" >> $log
	ls $images >> $log
	echo -e "}"
	sleep 600
done

