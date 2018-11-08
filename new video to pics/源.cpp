#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int GetRate(const String videoName, double& rate, double& count);

int main()
{
	String path = "E:\\data\\img\\RGB\\20181107\\";
	String videoName = "VID_19710616_080230.mp4";
	String videoNames = path + videoName;
	double count, rate;
	size_t rows, cols;
	Mat frame;

	if (GetRate(videoNames, rate, count) != 0)
	{
		system("pause");
		return -1;
	}

	VideoCapture capture(videoNames);
	if (!capture.isOpened())
	{
		cout << "Movie open Error" << endl;
		return -1;
	}

	capture.read(frame);
	rows = frame.rows;
	cols = frame.cols;

	cout << "video name: " << videoNames <<endl;
	cout << "rate:" << rate << " count:" << count << endl;
	cout << "rows:" << rows << " cols:" << cols << endl;

	size_t nrows, ncols;

	nrows = rows / 2;
	ncols = cols / 2;


	int diff = 1;
	String imgpath = "E:\\data\\imgFromVideo\\";
	String foldName = "A\\";
	String imgName1 = "img";
	String imgName2 = ".jpg";
	imgpath += foldName;

	int id = 0;
	for (int i = 1; capture.read(frame); i++)
	{
		if (!(i%diff))
		{
			transpose(frame, frame);
			imwrite(imgpath + imgName1 + to_string(id) + imgName2, frame);
			id++;
			if (id >= 40)
			{
				break;
			}
		}
	}

	cout << "完成！共" << id << "张图位于" << imgpath << endl;
	capture.release();

	system("pause");
	return 0;
}

int GetRate(const String videoName, double& rate, double& count)
{
	VideoCapture capture(videoName);
	if (!capture.isOpened())
	{
		cout << "Movie open Error" << endl;
		return -1;
	}
	rate = capture.get(CV_CAP_PROP_FPS);
	count = capture.get(CV_CAP_PROP_FRAME_COUNT);
	return 0;
}