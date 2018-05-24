#!/bin/bash

log="/home/pi/Project-Nyx/logs/system.log"


while true
do
	#get system time
	echo -e "time=$(date -u +%Y%m%d%H%M%S)" >> $log 2>&1

	#get core temperature
	echo -e "$(vcgencmd measure_temp)" >> $log 2>&1

	#get voltages
	for id in core sdram_c sdram_i sdram_p
	do
		echo -e "$id:\t$(vcgencmd measure_volts $id)" >> $log 2>&1
	done
	echo -e "\n" >> $log 2>&1

	sleep 10
done
