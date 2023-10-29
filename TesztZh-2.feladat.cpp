#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1() {
/*
A program a felhasználótól bekéri a szerkesztendő kép teljes elérési útvonalát, majd megnyitja ezt a képfájlt. (1p)
*/
	std::string path;
	std::cout << "Kep eleresi utvonala : "; //kacsa.jpg
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
	cv::imshow("result1", img);
	cv::waitKey();

/*
A program elvégzi automatikusan a szükséges képkorrekciós műveleteket. (3p)
*/
	//Gaussian elmosás (életlenítő szűrő) --> JÓ
	cv::Mat I = cv::imread("kacsa.jpg", 1);
	cv::Mat filtered;
	cv::GaussianBlur(I, filtered, cv::Size(5, 5), 0.5);
	cv::imshow("result2.1", filtered);
	cv::waitKey();

	//Medián elmosás (életlenítő szűrő)
	cv::medianBlur(I, filtered, 3);
	cv::imshow("result2.2", filtered);
	cv::waitKey();

	//Box elmosás (életlenítő szűrő)
	int value = 3; //always odd
	cv::boxFilter(I, filtered, -1, cv::Size(value, value));
	cv::imshow("result2.3", filtered);
	cv::waitKey();

	//színes kép hisztogram kiegyenlítése --> JÓ
	cv::Mat hsv, splitted[3], equalized[3], merged, result;
	cv::cvtColor(I, hsv, cv::COLOR_BGR2HSV); //konvertálja hsv színtérbe
	cv::split(hsv, splitted); //szétspliteljük 3 részre
	cv::equalizeHist(splitted[2], equalized[2]); //a kép világosságát javítjuk
	//-->Másolja a telítettség és színárnyalat csatornákat a módosított érték csatornára 
	splitted[1].copyTo(equalized[1]);
	splitted[0].copyTo(equalized[0]);
	cv::merge(equalized, 3, merged); //összemergeljük a szerkesztett képet
	cv::cvtColor(merged, result, cv::COLOR_HSV2BGR); //visszaállítjuk RGB-re
	cv::imshow("result2.4", result);
	cv::waitKey();

	//élesítés --> Gyenge kontrasztú képek esetében alkalmazzuk.
	cv::Mat sharp;
	cv::medianBlur(I, filtered, 3);
	cv::addWeighted(I, 2.5, filtered, -1.5, 1, sharp); //fokozza a kép kontrasztját
	cv::imshow("result2.5", sharp);
	cv::waitKey();

	//élesítés --> Gyenge kontrasztú képek esetében alkalmazzuk.
	cv::Mat blurred, unsharped;
	cv::GaussianBlur(I, blurred, cv::Size(5, 5), 1);
	cv::addWeighted(I, 1.5, blurred, -0.5, 0, unsharped);
	cv::imshow("result2.6", sharp);
	cv::waitKey();

	/*
	• A program a felhasználó által megadott érték alapján küszöbölést hajt végre. (2p)
	*/
	//automatikusnál Otsut
	//ha nem teljesen a szép, akkor adaptív
	//ha értékbekérős, akkor ez
	int thresh_value;
	std::cout << "Kerem adja meg a kuszoberteket: ";
	std::cin >> thresh_value;
	cv::Mat thresh;
	//Sima globális küszöbölés :
	cv::threshold(I, thresh, thresh_value, 255, cv::THRESH_BINARY);
	/*
	Ha a kép intenzitása a küszöbérték felett van, a kimeneti képben a pixel értéke 255 lesz, különben 0.
	Tehát a fehér pixelek a küszöbértéket meghaladó intenzitású részeken lesznek, míg a fekete pixelek a küszöbérték alatti intenzitású részeken.
	*/
	cv::threshold(I, thresh, thresh_value, 255, cv::THRESH_BINARY_INV);
	/*
	Azonban itt az eredmény inverz: Ha a kép intenzitása a küszöbérték felett van, a kimeneti képben a pixel értéke 0 lesz, különben 255.
	Tehát a fehér pixelek a küszöbérték alatti intenzitású részeken lesznek, míg a fekete pixelek a küszöbértéket meghaladó intenzitású részeken.
	*/
	cv::imshow("result2.7-sima", thresh);
	cv::waitKey();

	/*
	A program lehetőséget biztosít a felhasználó számára a kinyert rész színparamétereinek
	(színezet, színtelítettség és világosság) megadására. (4p)
	*/
	unsigned char hue = 0, sat = 0, val = 0;
	std::cout << "Kérem a színárnyalatot: ";
	std::cin >> hue;
	std::cout << "Kérem a telítettséget: ";
	std::cin >> sat;
	std::cout << "Kérem a világosságot: ";
	std::cin >> val;
	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b pixelGroup = hsv.at<cv::Vec3b>(i, j);
			pixelGroup[0] += hue;
			pixelGroup[1] += sat;
			pixelGroup[2] += val;
			hsv.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}
	cv::cvtColor(hsv, result, cv::COLOR_HSV2RGB);
	std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	formatParameters_jpg.push_back(92);
	/*
	A program eredményként kimenti a felhasználó által megadott elérési útvonalra a
	szerkesztett képet JPEG formátumban, 92%-os minőségi arányban. (2p)
	*/
	cv::imwrite("out.jpg", result, formatParameters_jpg);
	cv::imshow("img", I);
	cv::imshow("result8", result);
	cv::waitKey();
}

void Exercise2() {
	/*
	 A program a felhasználótól bekéri a kép teljes elérési útvonalát.
	*/
	std::string path;
	std::cout << "Kep eleresi utvonala : ";
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
	cv::imshow("res1", img);
	cv::waitKey();

	/*
	A program bekér a felhasználótól egy küszöbértéket, és a küszöbölést* követően első
	lépésként kimaszkolja azokat a részeket a szerkesztendő képről, amelyek az alábbi
	kritériumnak megfelelnek: (4p)
	-Az adott pixelérték színértéke a küszöbérték kétszeresét nem haladja meg,
	-Az adott pixelérték szaturációs értéke a 50 és 170-as sávba,
	-Az adott pixelérték világossági értéke a 100 és 200-as sávba esik.
	Fontos rész, hogy a maszkolás mellett ezeket a pixeleknek az indexeit is tárolja a program
	tetszőlegesen megválasztott adatstruktúrában (tömb, verem, stb.)
	*/
	cv::Mat mask, hsv, splitted[3];
	unsigned char thresholdValue = 0;
	std::cout << "Kerek egy kuszoberteket: ";
	std::cin >> thresholdValue;
	cv::cvtColor(img, hsv, cv::COLOR_RGB2HSV); //RGB-ből HSV-be konvertálás
	cv::split(hsv, splitted); //HSV színtér csatornáit szátválasztja és splitted tömben eltárolja
	cv::threshold(splitted[0], mask, thresholdValue, 255, cv::THRESH_BINARY); //Hue-n elvégzi a küszöbölést, eredményt elmenti a mask-ban
	cv::Mat masked(hsv.size(), CV_8UC3); //Létrehoz egy üres képet (masked) ugyanakkora mérettel, mint a HSV kép.
	std::vector<cv::Point> indexes;
	cv::imshow("mask", mask);
	cv::waitKey();
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			//Végigmegy a képen egy dupla for ciklussal, és ellenőrzi minden pixelre, 
			//hogy a mask maszkban nem nulla-e. Ha nem nulla, akkor további ellenőrzéseket végez
			if (mask.at<uchar>(i, j)) {
				cv::Vec3b pixelgroup = hsv.at<cv::Vec3b>(i, j);
				if (pixelgroup[0] <= thresholdValue * 2 &&
					(pixelgroup[1] >= 50 && pixelgroup[1] <= 170) &&
					(pixelgroup[2] >= 100 && pixelgroup[2] <= 200)
					) {
					//Ha minden feltétel teljesül, 
					//akkor a pixel értékét a masked képben az eredeti hsv kép értékére állítja.
					masked.at<cv::Vec3b>(i, j) = pixelgroup;
					indexes.push_back(cv::Point(i, j)); //A pixel koordinátáit elmenti a indexes vektorban.
				}

			}
		}
	}
	//std::cout << indexes;
	/*
		A program csak a maszkolt részek felét hagyja meg véletlenszerűen az eredeti képen, a többi
		részt törli az eredeti szerkesztendő képről, majd ezt követően eltünteti a megmaradt apróbb
		hibákat a felhasználó által megadott méret** szerint. (2p)
	*/
	//veletlenszeru torles es morfologia
	cv::Mat structElement = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	//itt sokfajta megoldas is van a vector bejarasara, ez a fapados verzio
	for (int i = 0; i < indexes.size(); ++i) {
		float n = std::rand() / RAND_MAX;
		//itt a vector adott elemet erjuk el a begin a legelso elem lesz mig az i hogy hanyadik elemnel jarunk
		if (n > 0.5) indexes.erase(indexes.begin() + i);
	}
	cv::Mat mask2(mask.size(), CV_8UC1);
	for (int i = 0; i < indexes.size(); ++i) {
		mask2.at<uchar>(indexes.at(i).x, indexes.at(i).y) = 255;
	}

	cv::Mat opened;
	cv::Mat eroded;
	cv::Mat tempMask[3], finalMask;
	cv::Mat hsv_result;

	cv::erode(mask2, eroded, structElement);
	cv::dilate(eroded, opened, structElement);

	for (int i = 0; i < 3; ++i)
		tempMask[i] = opened.clone();

	cv::merge(tempMask, 3, finalMask);
	cv::bitwise_and(hsv, finalMask, hsv_result);

	cv::imshow("finalMask", finalMask);
	cv::imshow("hsv_result", hsv_result);
	cv::waitKey();

	/*
	A program a törölt képrészeket feltölti a felhasználó által megadott háttérszín értékeivel. (2p)
	*/
	unsigned char hue, sat, val;
	std::cout << "Kérem a színárnyalatot: ";
	std::cin >> hue;
	std::cout << "Kérem a telítettséget: ";
	std::cin >> sat;
	std::cout << "Kérem a világosságot: ";
	std::cin >> val;
	for (int i = 0; i < hsv_result.rows; ++i) {
		for (int j = 0; j < hsv_result.cols; ++j) {
			cv::Vec3b pixelGroup = hsv_result.at<cv::Vec3b>(i, j);
			if (pixelGroup == cv::Vec3b(0, 0, 0))
				pixelGroup = cv::Vec3b(hue, sat, val);
			hsv_result.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}

	cv::Mat result;
	cv::cvtColor(hsv_result, result, cv::COLOR_HSV2RGB);

	cv::imshow("result", result);
	cv::waitKey();
}

int main() {
	//Exercise1();
	Exercise2();
	return 0;
}
