#!/bin/bash

LOGDIR="/home/pi/Project-Nyx/error-logs"
IMGDIR="/home/pi/Project-Nyx/images"
VIDDIR="/home/pi/Project-Nyx/videos"

if ! [ -d $LOGDIR ]
then
	mkdir /home/pi/Project-Nyx/error-logs
fi

if ! [ -d $IMGDIR ]
then
	mkdir /home/pi/Project-Nyx/images
fi

if ! [ -d $VIDDIR ]
then
	mkdir /home/pi/Project-Nyx/videos
fi
