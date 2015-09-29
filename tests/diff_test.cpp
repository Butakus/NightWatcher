#include <iostream>
#include <opencv2/opencv.hpp>

#define IMG_NAME "/outputs/diff_test_"

#define STR(a) _STR_EXPAND(a)
#define _STR_EXPAND(a) #a

using namespace cv;
using namespace std;

// Drop n frames from the camera buffer
void drop(VideoCapture cap, int n){
	Mat dropped;
	for (int i=0; i<n; ++i) cap >> dropped;
}

int main(int argc, char const *argv[]){
#ifndef ROOT_PATH
	cout << "[ERROR]: ROOT_PATH variable not defined.\n";
	return 0;
#endif

	VideoCapture cap = VideoCapture(0);
	if (!cap.isOpened()){
		cout << "Could not open the Webcam.\n";
		return 0;
	}
	drop(cap, 30);  // Drop the 30 first frames

	Mat frame1, frame2, diff;

	cap >> frame1;
	drop(cap, 10);
	cap >> frame2;
	// Convert to gray
	cvtColor(frame1, frame1, CV_BGR2GRAY);
	cvtColor(frame2, frame2, CV_BGR2GRAY);
	// Substract and blur
	absdiff(frame1, frame2, diff);
	GaussianBlur(diff, diff, Size(21,21), 0);

	imwrite(STR(ROOT_PATH) IMG_NAME ".png", diff);

	return 0;
}