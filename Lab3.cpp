#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

/*
fekete fehér képre tetszőleges szűrő alkalmazása, majd hisztogram kiegyenlítés
*/
void Exercise1()
{
	//--> csak fekete-fehérre működik

	cv::Mat I = cv::imread("shape.png", 0);
	cv::Mat filtered, equalized;

	// Ez a szűrő a pixelek közötti mediánt (középső érték) választja ki,
	// ami segíthet kiszűrni a zajokat a képen.
	cv::medianBlur(I, filtered, 5);

	//hisztogramot egyenlít ki 
	//Ez a lépés segít javítani a kontrasztot és a láthatóságot.
	cv::equalizeHist(filtered, equalized);

	cv::imshow("result1", equalized);
	cv::waitKey();
}

/*
kép élesítése szűrő segítségével
*/
void Exercise2()
{
	cv::Mat I = cv::imread("shape.png", 0);
	cv::Mat filtered, sharp;

	cv::medianBlur(I, filtered, 5);
	cv::addWeighted(I, 2.5, filtered, -1.5, 1, sharp); //fokozza a kép kontrasztját

	cv::imshow("result2", sharp);
	cv::waitKey();
}

/*
színes kép hisztogram kiegyenlítése
*/
void Exercise3()
{
	cv::Mat I = cv::imread("shape.png", 1);
	cv::Mat hsv, splitted[3], equalized[3], merged, result;

	cv::cvtColor(I, hsv, cv::COLOR_BGR2HSV); //konvertálja hsv színtérbe

	cv::split(hsv, splitted); //szétspliteljük 3 részre
	cv::equalizeHist(splitted[2], equalized[2]); //a kép világosságát javítjuk
	//-->Másolja a telítettség és színárnyalat csatornákat a módosított érték csatornára 
	splitted[1].copyTo(equalized[1]);
	splitted[0].copyTo(equalized[0]);

	cv::merge(equalized, 3, merged); //összemergeljük a szerkesztett képet
	cv::cvtColor(merged, result, cv::COLOR_HSV2BGR); //visszaállítjuk RGB-re
	cv::imshow("result3", result);
	cv::waitKey();
}

int main()
{
	Exercise1();
	Exercise2();
	Exercise3();
	return 0;
}
