import os
from time import sleep
from picamera import PiCamera
from datetime import datetime

class run_camera:
	def take_picture(self):
		camera = PiCamera()
		#Sensor mode 2: 3280x2464, 1/10<=fps<=15
		print("Changing sensor mode...")
		camera.sensor_mode = 2
		print("Sensor mode changed to "+str(camera.sensor_mode))
		#warmup camera
		print("Adjusting...")
		camera.start_preview()
		sleep(2)
		print("Taking photo...")
		#take photo
		filename = "images/"+datetime.now().strftime("%Y-%m-%d--%H%M.jpeg")
		camera.capture(filename,quality=100)
		#prepare for mode change
		camera.stop_preview()
		camera.close()
		if (os.path.exists(filename)):
			print("Photo taken.")
		else:
			print("Failed to take video.")

	def take_video(self,videoLength=300):
		#Sensor mode 2: 1920x1080, 1/10<=fps<=30
		camera = PiCamera()
		print("Changing sensor mode...")
		camera.sensor_mode = 1
		print("Sensor mode changed to "+str(camera.sensor_mode))
		#warm up camera
		print("Adjusting...")
		camera.start_preview()
		sleep(2)
		#take video
		print("Proposed video length is "+str(videoLength / 60.0)+" minutes.")
		print("Recording video...")
		filename = "videos/"+datetime.now().strftime("%Y-%m-%d--%H%M.h264")
		camera.start_recording(filename,quality=1)
		camera.wait_recording(videoLength)
		camera.stop_recording()
		#prepare for mode change
		camera.stop_preview()
		camera.close()
		if(os.path.exists(filename)):
			print("Video taken.")
		else:
			print("Failed to take video.")
