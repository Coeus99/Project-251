#!/bin/bash

#take n images
#save with datetime
#go to milli-second

#number of images
n=10
#timer for video
t=120000

#take images
for ((i=1;i<11;i++))
do
	fn=images/nyx_`date -u +%Y%m%d%H%M%S`.jpeg
	raspistill -vf -hf -md 2 -q 100 -o $fn
	echo "Took image $i of $n: $fn"
done

#sync to disk
sync

#take video

echo "Taking $t milli-second video."
fn=videos/nyx_`date -u +%Y%m%d%H%M%S`.h264
raspivid -vf -hf -md 2 -t $t -o $fn
echo "Took video: $fn"

#sync to disk
sync
