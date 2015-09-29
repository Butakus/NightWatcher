#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

// Key codes returned by waitKey()
#define KEY_q 1048689
#define KEY_r 1048690
#define KEY_s 1048691

#define IMG_NAME "/outputs/img_test_"
#define VID_NAME "/outputs/vid_test_"
#define FPS 8

#define STR(a) _STR_EXPAND(a)
#define _STR_EXPAND(a) #a

using namespace cv;
using namespace std;

// Drop n frames from the camera buffer
void drop(VideoCapture cap, int n){
	Mat dropped;
	for (int i=0; i<n; ++i) cap >> dropped;
}

int main(int argc, char** argv){
#ifndef ROOT_PATH
	cout << "[ERROR]: ROOT_PATH variable not defined.\n";
	return 0;
#endif
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Could not open the Webcam.\n";
		return 0;
	}

	VideoWriter writer = VideoWriter();
	namedWindow("Webcam Test", WINDOW_AUTOSIZE);
	Mat frame;
	int key = -1;
	bool running = true, recording = false;
	int img_count = 0, vid_count = 0;
	chrono::high_resolution_clock::time_point t1;
	chrono::high_resolution_clock::time_point t2;
	const double frame_time = 1000.0 * 1.0 / FPS;

	cout << "Webcam OpenCV tester. Options:\n";
	cout << "- Press 's' to capture an image.\n";
	cout << "- Press 'r' to start recording.\n";
	cout << "- Press 'q' to quit.\n";
	while(running){
		cap >> frame;
		imshow("Webcam Test", frame);

		key = waitKey(1);
		switch(key){
			case KEY_q:
				running = false;
				break;

			case KEY_s:
				cout << "Saving image: " << STR(ROOT_PATH) IMG_NAME + to_string(img_count) + ".png" << "\n";
				imwrite(STR(ROOT_PATH) IMG_NAME + to_string(img_count) + ".png", frame);
				img_count ++;
				break;

			case KEY_r:
				cout << "Recording video... Press 's' to stop.\n";
				writer.open(
					STR(ROOT_PATH) VID_NAME + to_string(vid_count) + ".avi",					//File name
					CV_FOURCC('X','V','I','D'),													//FOURCC code for encoding
					FPS,																		//FPS
					Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)),	//Frame size
					true																		//isColor param
				);
				if (!writer.isOpened()){
					cout << "Could not open VideoWriter with file " << STR(ROOT_PATH) VID_NAME + to_string(vid_count) + ".avi" << "\n";
					break;
				}
				while (waitKey(1) != KEY_s){
					t1 = chrono::high_resolution_clock::now();
					cap >> frame;
					imshow("Webcam Test", frame);
					writer << frame;
					do{
						t2 = chrono::high_resolution_clock::now();
					}
					while (chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() < frame_time);
				}
				cout << "Saving video: " << STR(ROOT_PATH) VID_NAME + to_string(vid_count) + ".avi" << "\n";
				writer.release();
				vid_count++;
				break;

			default:
				break;
		}
	}
	destroyAllWindows();
	cap.release();
	return 0;
}