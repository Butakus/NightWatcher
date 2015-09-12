import cv2

if __name__ == '__main__':
	cap = cv2.VideoCapture(0)
	for _ in xrange(30): ret, frame1 = cap.read() # Trim the camera
	
	if not ret:
		print "Couldn't get the frame"
		exit(1)
	grey1 = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)

	for _ in xrange(30): ret, frame1 = cap.read() # Drop some frames to get a different one	
	ret, frame2 = cap.read()
	grey2 = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)

	diff = cv2.absdiff(grey1, grey2)
	# Blur the diff to smooth it. Need to select kernel size
	diff = cv2.GaussianBlur(diff, (21,21), 0)
	cv2.imwrite('../outputs/diffTest.png', diff)