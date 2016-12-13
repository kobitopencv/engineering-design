#include <tchar.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\text.hpp>

using namespace cv;

int main(){
	VideoCapture cap(0);
	int cnt = 0;
	int j = 0;
	char str[32];
	
	Ptr<BackgroundSubtractorMOG2>bgs = createBackgroundSubtractorMOG2(500, 16, true);
	
	while (waitKey(1) != 32){
		Mat frm, mask, output;
		cap >> frm;
		bgs->apply(frm, mask);
		bitwise_and(frm, frm, output, mask);
		imshow("frm", output);
		sprintf_s(str, "cap%d.jpg", j++);
		if (cnt == 300){
			imwrite(str, output);
			cnt = 0;
		}
	}
	return 0;
}
