#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int createMaskByKmeans(Mat frame, Mat & mask)

{
	if (mask.type()!=CV_8UC1)//�ж�
	{
		cout << "fail" << endl;
		return 0;
	}
	

	int width = frame.cols;
	int height = frame.rows;


	//���ԭͼ����
	int pixNum = width * height;
	//ȡ�ɼ���
	int k = 2;
	//kmeans�㷨��ÿ�����ݵ��Ӧһ����ǩ��0��ʼ������k����0,1,2��samplecount x 1ά�ȣ�
	Mat labels;
	//���ĵ�
	Mat centers;
	//����kmeans�õ�����

	Mat sampleData =frame.reshape(3, pixNum);
	//��Ҫ�Զ����������
	Mat km_data;

	sampleData.convertTo(km_data, CV_32F);



	//ִ��kmeans
	//�㷨�����ı�׼����ȡ�������ȵĵ�����������opencv�е��Ż���������
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	//KMEANS_PP_CENTERS��ʾ��kmeans++�㷨����ʼ������
	kmeans(km_data, k, labels, criteria, k, KMEANS_PP_CENTERS, centers);



	//����mask
	//����������Ԫ�ص����飬0��255
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



	imshow("ԭͼ", src);
	imshow("mask", mask);
	waitKey(0);



}





