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


if __name__ == "__main__":
	main()
