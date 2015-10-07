#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char const *argv[]){
	
	namedWindow("Key Tester", WINDOW_AUTOSIZE);
	int key = -1;

	while (key != 'q'){
		key = waitKey(0) & 0x00ff;
		cout << "Key code: " << key << " (\'" << (char)key << "\')\n";
	}
	return 0;
}