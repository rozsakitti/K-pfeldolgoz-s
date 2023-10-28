# Visual Studio Code beállítások C++-hoz
- [ ] Hozz létre egy üres C++ projektet (empty) 
- [ ] Adj hozzá egy main.cpp fájlt 
- [ ] Nyisd meg a projekt beállításokat:
      ◦ (projekt helyi menüje: Properties)
      - A Platform legyen x64
      - A Configuration Release vagy All …
		![image](https://github.com/rozsakitti/K-pfeldolgoz-s/assets/90957539/829127fc-fa87-4a86-8216-5896bbdb5815)
- [ ] Válaszd ki a C/C++ pontot --> Additional Include Directories--> add meg az include fájlok elérési útját: C:\Users\Admin\opencv\build\include 
- [ ] Válaszd ki a Linker/Genaral pontot --> Additional Library Directories: C:\Users\Admin\opencv\build\x64\vc16\lib
- [ ] Válaszd ki a Linker Input pontját!
     
 --> Válassz konfigurációt: Release és az additional dependecies: opencv_world480.lib
     
  --> Válassz konfigurációt: Debug és az additional dependencies: opencv_world480d.lib

- [ ] Próba kód: proba.jpg-t behelyez a megfelelő helyre
      
    	#include <opencv2/core.hpp>
    	#include <opencv2/highgui.hpp>
    	int main() { 
    	cv::Mat img = cv::imread("proba.jpg");
    	cv::imshow("próba", img);
    	cv::waitKey();
    	return 0;
    	}

 
