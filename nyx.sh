#!/bin/bash

#take images
#set filename based on files that exist
i=0
image_filename=/home/pi/Project-Nyx/images/image
while [[ -e $image_filename-$i.jpeg ]] ; do
	let i++
done
image_filename=$image_filename-$i
#take that image
#mode 2: 3280x2464, Full FOV
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename.jpeg -n
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename-0.jpeg -n
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename-1.jpeg -n
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename-2.jpeg -n
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename-3.jpeg -n
#I'm using this mode, no argument, I want good pictures
raspistill -t 2000 -md 2 -q 100 -vf -hf -o $image_filename -n
#-md 2, switch to mode 2
#-t 2000, take photo after 2 seconds
#-q 100, set image quality to 100 (0-100)
#-o $image_filename, output to file
#-n ,no camera preview

#write to disk, we don't want to lose anything!
sync
sleep 1
#let's take some video
#set filename based on existing files
#counter is different than image in case of corrupt file
v=0
video_filename=/home/pi/Project-Nyx/videos/video
while [[ -e $video_filename-$v.h264 ]] ; do
	let v++
done
video_filename=$video_filename-$v.h264
#take that video
#video options... (will affect battery life)
#mode 1: 1920x1080 @ 0.1-30fps, partial FOV
#mode 4: 1640x1232 @ 0.1-40fps, full FOV
#mode 5: 1640x922 @ 0.1-40fps, full FOV
#mode 6: 1280x720 @ 40-90fps, partial FOV
#mode 7: 640x480 # 40-90fps, partial FOV
raspivid -md 2 -t 5000 -vf -hf -o $video_filename -n
#-md 1, set to mode 1
#-t 300000, take video for 5 minutes
#-o $video_filename, output video to file
#write to disk again, we don't want to lose these!

sync
sleep 1
