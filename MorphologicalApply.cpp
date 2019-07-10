#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;

int main(int argc, char** argv)
{
	Mat src, dst;
	src = imread("D:/test.jpg");
	if (!src.data)
	{
		printf("could not load image.");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "result image";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

	Mat gray_src;
	cvtColor(src, gray_src, CV_RGB2GRAY);
	imshow("gray image", gray_src);

	Mat binImg;
	//对图像取反后再操作
	adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	imshow("binary image", binImg);

	//水平结构元素
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	//垂直结构元素
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));
	//矩形结构
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	Mat temp;
	erode(binImg, temp, kernel);
	dilate(temp, dst, kernel);
	//法二
// 	morphologyEx(binImg, dst, CV_MOP_OPEN, vline);
	bitwise_not(dst, dst);//图像变回来
	blur(dst, dst, Size(3, 3), Point(-1, -1));
	imshow("Final Result", dst);

	waitKey(0);
	return 0;
}
