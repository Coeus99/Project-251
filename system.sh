#!/bin/bash

log="/home/pi/Project-Nyx/logs/system.log"


while true
do
	#get date
	echo -n "$(date -u +%Y%m%d)," >> $log 2>&1

	#get time
	echo -n "$(date -u +%H%M%S)," >> $log 2>&1

	#get core temperature
	tempvar="$(vcgencmd measure_temp)"
	echo -n ${tempvar:5}, >> $log 2>&1

	#get voltages
	for id in core sdram_c sdram_i sdram_p
	do
		tempvar="$(vcgencmd measure_volts $id)"
		echo -n ${tempvar:5},  >> $log 2>&1
	done
	echo -n -e "\r\n" >> $log 2>&1

	sleep 10
done
