#!/bin/bash

nyx="/home/pi/Project-Nyx/nyx.sh"

while true
do
	bash $nyx >> /home/pi/Project-Nyx/logs/nyx.log 2>&1
done
