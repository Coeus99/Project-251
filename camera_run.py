from time import sleep
from picamera import PiCamera
from datetime import datetime

camera = PiCamera()

class run_camera:
	def take_picture(self):
		#Sensor mode 2: 3280x2464, 1/10<=fps<=15
		camera.sensor_mode = 2
		#warmup camera
		camera.start_preview()
		sleep(2)
		#take photo
		filename = datetime.now().strftime("%Y-%m-%d--%H%M.jpeg")
		camera.capture(filename,quality=100)
		#prepare for mode change
		camera.stop_preview()

	def take_video(self,videoLength):
		#Sensor mode 2: 1920x1080, 1/10<=fps<=30
		camera.sensor_mode = 1
		#warm up camera
		camera.start_preview()
		sleep(2)
		#take video
		filename = datetime.now().strftime("%Y-%m-%d--%H%M.h264")
		camera.start_recording(filename)
		camera.wait_recording(videoLength)
		camera.stop_recording()
		#prepare for mode change
		camera.stop_preview()
