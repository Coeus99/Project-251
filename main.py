import os

def main():
	print("Initializing Directories...")
	dir_init()

########################
#   Make Directories   #
########################
def dir_init():
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

if __name__ == "__main__":
	main()
