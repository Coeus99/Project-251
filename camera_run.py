from time import sleep
import picamera import PiCamera

camera = Picamera()

####################################
# Main function, pilots code
####################################
def main():
	while(TRUE):


####################################
# Takes video for a specified time
####################################
def take_video(time):
#Sensor mode 1: 1920x1080, 1/10<=fps<=30
camera.sensor_mode(1)

#warmup camera
camera.start_preview()
sleep(2)

#take photo
camera.capture("%t.jpg")

#prepare for mode change
camera.stop_preview()


####################################
# Takes high resolution photo
####################################
def take_picture():
#Sensor mode 2: 3280x2464, 1/10<=fps<=15
camera.sensor_mode(2)
#warm up camera
camera.start_preview()
sleep(2)

camera.start_recording(quality = 10)
sleep(time)
camera.stop_recording()

#prepare for mode change
camera.stop_preview()


if __name__ == "__main__":
	main()