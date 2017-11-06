import os
import picamera
from time import sleep
from datetime import datetime


def main():
	#Initialize directories required
	dir_init()
	print("Running...")
	for x in range(120):
		print(str(x+1)+" of "+str(120))
		take_image()
		sleep(1)
		take_video(300)
		sleep(1)
	print("Done.")

########################
#   Make Directories   #
########################
def dir_init():
	print("Initializing Directories...")
	#create images folder
	print("Creating images directory...")
	if not os.path.exists("images"):
		os.makedirs("images")
		if os.path.exists("images"):
			print("Images directory created.")
		elif not os.path.exists("images"):
			print("Failed to create images directory.")
	elif os.path.exists("images"):
		print("Images directory already exists.")
	#create videos folder
	print("Creating videos directory...")
	if not os.path.exists("videos"):
		os.makedirs("videos")
		if os.path.exists("videos"):
			print("Videos directory created.")
		elif not os.path.exists("vidoes"):
			print("Failed to create images directory.")
	elif os.path.exists("videos"):
		print("Videos directory already exists.")
	print("Done.\n")

def take_image():
	with picamera.PiCamera() as camera:
		#Sensor mode 2: 3280x2464, 1/10<=fps<=15
		print("Changing sensor mode...")
		camera.sensor_mode = 2
		print("Sensor mode is now "+str(camera.sensor_mode))
		#warmup camera
		print("Beginning preview...")
		camera.start_preview()
		sleep(2)
		print("Taking image...")
		filename = "images/"+datetime.now().strftime("%Y-%m-%d--%H%M.jpeg")
		camera.capture(filename,quality=100)
		camera.stop_preview()


def take_video(videoLength):
	with picamera.PiCamera() as camera:
		#Sensor mode 1: 1920.1080, 1/10<=fps<=30
		print("Changing sensor mode...")
		camera.sensor_mode = 1
		print("Sensor mode is now "+str(camera.sensor_mode))
		print("Beginning preview...")
		camera.start_preview()
		sleep(2)
		print("Taking video for "+str(videoLength)+" seconds...")
		filename = "videos/"+datetime.now().strftime("%Y-%m-%d--%H%M.h264")
		camera.start_recording(filename,quality=1)
		camera.wait_recording(videoLength)
		camera.stop_recording()
		camera.stop_preview()


if __name__ == "__main__":
	main()
