import cv2
import time

# Seconds recording
CAP_TIME = 5
# Enable color frame
COLOR = True

if __name__ == '__main__':
	cap = cv2.VideoCapture(0)

	fourcc = cv2.cv.CV_FOURCC('X','V','I','D')
	writer = cv2.VideoWriter()
	writer.open('../outputs/videoTest.avi', fourcc, 30.0, (640,480), COLOR)
	
	start = time.time()
	now = start
	while cap.isOpened() and now - start < CAP_TIME:
		ret, frame = cap.read()
		if not ret:
			print 'Could not get the frame'
			exit(1)
		if not COLOR:
			frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		writer.write(frame)
		now = time.time()

	writer.release()
	cap.release()