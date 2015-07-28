import cv2

if __name__ == '__main__':
	cap = cv2.VideoCapture(0)

	ret, frame = cap.read()
	if not ret:
		print "Couldn't get the frame"
		exit(0)
	cv2.imwrite('../outputs/imgTest.png', frame)