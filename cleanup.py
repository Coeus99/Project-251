import os

def main():
	images = input("Clear out images directory?(1/0)\n")
	videos = input("Clear out videos directory?(1/0)\n")

	if(images == 1):
		print("Cleaning images directory...")
		if not os.path.exists("images"):
			print("Images directory doesn't exist.")
		else:
			for file in os.listdir("images"):
				path = os.path.join("images",file)
				os.unlink(path)
		print("Finished cleaning.")
	if(videos == 1):
		print("Cleaning videos directory...")
		if not os.path.exists("videos"):
			print("Videos directory does not exist.")
		else:
			for file in os.listdir("videos"):
				path = os.path.join("videos",file)
				os.unlink(path)
		print("Finished cleaning.")
	print("Done.")

if __name__ == "__main__":
	main()
