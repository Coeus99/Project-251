import os

def main():
	clearDir = input("Would you like to clear the current directories?(1/0)\n")
	dir_init(clearDir)

########################
#   Make Directories   #
########################
def dir_init(clearDir=0):
	#create images folder
	if not os.path.exists("images"):
		os.makedirs("images")
	#create videos folder
	if not os.path.exists("videos"):
		os.makedirs("videos")
	#if clear flag is true, clear folder contents
	if(clearDir == 1):
		for photo in os.listdir("images"):
			file_path = os.path.join("images",photo)
			try:
				if os.path.isfile(file_path):
					os.unlink(file_path)
			except Exception as e:
				print(e)
		for video in os.listdir("videos"):
			file_path = os.path.join("videos",video)
			try:
				if os.path.isfile(file_path):
					os.unlink(file_path)
			except Exception as e:
				print(e)


if __name__ == "__main__":
	main()
