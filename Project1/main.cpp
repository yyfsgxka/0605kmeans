#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int createMaskByKmeans(Mat frame, Mat & mask)

{
	if (mask.type()!=CV_8UC1)//判断
	{
		cout << "fail" << endl;
		return 0;
	}
	

	int width = frame.cols;
	int height = frame.rows;


	//获得原图像素
	int pixNum = width * height;
	//取成几类
	int k = 2;
	//kmeans算法后每个数据点对应一个标签从0开始，共有k个，0,1,2（samplecount x 1维度）
	Mat labels;
	//中心点
	Mat centers;
	//制作kmeans用的数据

	Mat sampleData =frame.reshape(3, pixNum);
	//需要自动聚类的数据
	Mat km_data;

	sampleData.convertTo(km_data, CV_32F);



	//执行kmeans
	//算法结束的标准，获取期望精度的迭代最大次数，opencv中的优化迭代条件
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	//KMEANS_PP_CENTERS表示用kmeans++算法来初始化簇心
	kmeans(km_data, k, labels, criteria, k, KMEANS_PP_CENTERS, centers);



	//制作mask
	//定义有两个元素的数组，0，255
	uchar display[2] = { 0,255 };

	for (int row = 0; row < height; row++) {

		for (int col = 0; col < width; col++) {

			mask.at<uchar>(row, col) = display[labels.at<int>(row*width + col)];

		}

	}



	return 0;

}

int main()

{
	Mat src = imread("lion.jpg");
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);



	imshow("原图", src);
	imshow("mask", mask);
	waitKey(0);



}





