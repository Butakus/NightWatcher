#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char const *argv[]){

	VideoCapture cap = VideoCapture(0);
	if (!cap.isOpened()){
		cout << "Could not open the Webcam.\n";
		return 0;
	}

	namedWindow("Diff Test", WINDOW_AUTOSIZE);
	Mat cur_frame, last_frame, cur_gray, last_gray, diff;
	int key = -1;

	while (key != 'q'){
		cap >> last_frame;
		cvtColor(last_frame, last_gray, CV_BGR2GRAY);
		cap >> cur_frame;
		cvtColor(cur_frame, cur_gray, CV_BGR2GRAY);
		
		// Substract and blur
		absdiff(cur_gray, last_gray, diff);
		GaussianBlur(diff, diff, Size(11,11), 0);
		
		imshow("Diff Test", diff);
		key = waitKey(1) & 0x00ff;		
	}
	return 0;
}