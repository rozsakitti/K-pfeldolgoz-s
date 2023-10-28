#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1()
{
	//beolvassuk a kepet, elso parameter az eleresi utvonal kepnevvel
	//masodik parameter a megnyitasi mod, ami itt szurkeskalas
	cv::Mat Image = cv::imread("shape.png", 0);

	//letrehozunk egy valtozot, ami a sor szamat fogja tarolni
	int line = 5;

	//bejarjuk az adott sor oszlopait, es kiiratjuk
	//at metodussal kerjuk le a pixeleket, elso parameter a sor, a masodik az oszlopot jeloli
	for (int i = 0; i < Image.cols; ++i) {
		std::cout << Image.at<uchar>(5, i) << " ";
	}
}

void Exercise2()
{
	//letrehozunk egy 10x10-es 8 bites egycsatornas matrixot, amit 0-val toltunk fel 
	cv::Mat M(100, 100, CV_8UC1, cv::Scalar::all(0));


	//-->ha a sorok és oszlopok összege páros, akkor az adott elem értékét 100-ra állítja
	for (int i = 0; i < M.rows; ++i) {
		for (int j = 0; j < M.cols; ++j) {
			if ((i + j) % 2 == 0) M.at<uchar>(i, j) = 100;
		}
	}

	cv::imshow("M", M);
	cv::waitKey();
}

int main()
{
	Exercise1();
	Exercise2();

	return 0;
}
