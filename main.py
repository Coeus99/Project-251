
import os, glob

def main():
	dir_init()

####################
# Make Directories #
####################
def dir_init():
	if not os.path.exists("images"):
		os.makedirs("images")
	if not os.path.exists("video"):
		os.makedirs("video")
	


if __name__ == "__main__":
	main()
