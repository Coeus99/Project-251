import os
from camera_run import run_camera
from time import sleep

camera = run_camera()

def main():
	#Initialize directories required
	dir_init()
	print("Running...")
	for x in range(12):
		camera.take_picture()
		camera.take_video(300)

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
	print("Done.")

if __name__ == "__main__":
	main()
