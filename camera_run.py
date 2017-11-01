from time import sleep
from picamera import PiCamera
from datetime import datetime

camera = PiCamera()
####################################
# Main function, pilots code
####################################
def main():
	take_picture()


####################################
# Takes picture at high res
####################################
def take_picture():
	#Sensor mode 1: 1920x1080, 1/10<=fps<=30
	camera.sensor_mode = 1

	#warmup camera
	camera.start_preview()
	sleep(2)
	
	filename = datetime.now().strftime("%Y-%m-%d::%H%M.jpeg")
	#take photo
	camera.capture(filename,quality = 100)

	#prepare for mode change
	camera.stop_preview()


####################################
# Takes video given a length
####################################
def take_video(length):
	#Sensor mode 2: 3280x2464, 1/10<=fps<=15
	camera.sensor_mode = 2
	#warm up camera
	camera.start_preview()
	sleep(2)

	#take video
	camera.start_recording("test.h264",quality = 10)
	sleep(length)
	camera.stop_recording()

	#prepare for mode change
	camera.stop_preview()


if __name__ == "__main__":
	main()
