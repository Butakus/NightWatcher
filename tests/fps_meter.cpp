#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char const *argv[]){

	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Could not open the Webcam.\n";
		return 0;
	}

	namedWindow("FPS Meter", WINDOW_AUTOSIZE);
	Mat frame;

	// Init
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	cap >> frame;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	double frame_time = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
	double fps = 0.95 * fps + 0.05 * (1000.0 / frame_time);

	cout << "Webcam FPS Meter.\n";
	cout << "Press 'q' to quit.\n";
	while (waitKey(1) & 0x00ff != 'q'){
		t1 = chrono::high_resolution_clock::now();
		cap >> frame;
		t2 = chrono::high_resolution_clock::now();
		imshow("FPS Meter", frame);
		frame_time = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		fps = 0.95 * fps + 0.05 * (1000.0 / frame_time);
		cout << "FPS: " << fps << "        \r" << flush;
	}
	cout << "FPS: " << fps << "\n";
	return 0;
}