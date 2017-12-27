#/bin/bash

i=0

image_filename=/home/pi/Project-Nyx/images/image

while [[ -e $image_filename-$i.jpeg ]] ; do
	let i++
done

image_filename=$image_filename-$i.jpeg

raspistill -o $image_filename

sync

sleep 1

v=0

video_filename=/home/pi/Project-Nyx/videos/video

while [[ -e $video_filename-$v.h264 ]] ; do
	let v++
done

video_filename=$video_filename-$v.h264

raspivid -o $video_filename -t 300000

sync

sleep 1
