from time import sleep
from picamera import PiCamera
from datetime import datetime

camera = PiCamera()
####################################
# Main function, pilots code
####################################
def main():
	videoLength = 60
	take_picture()
	take_video(videoLength)


####################################
# Takes picture at high res
####################################
def take_picture():
	#Sensor mode 1: 1920x1080, 1/10<=fps<=30
	camera.sensor_mode = 1

	#warmup camera
	camera.start_preview()
	sleep(2)

	filename = datetime.now().strftime("%Y-%m-%d--%H%M.jpeg")
	#take photo
	camera.capture(filename,quality=100)

	#prepare for mode change
	camera.stop_preview()


####################################
# Takes video given a length
####################################
def take_video(length):
	#Sensor mode 2: 3280x2464, 1/10<=fps<=15
	#camera.sensor_mode = 2
	camera.resolution = (1280,720)

	#warm up camera
	camera.start_preview()
	sleep(2)

	filename = datetime.now().strftime("%Y-%m-%d--%H%M.h264")
	#take video
	camera.start_recording(filename)
	camera.wait_recording(length)
	camera.stop_recording()

	#prepare for mode change
	camera.stop_preview()


if __name__ == "__main__":
	main()
