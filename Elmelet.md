# <p align="center">OpenCV</p>
### legfontosabb műveletek:
- Elérés:
  Mátrixelem: at(),
  Sor: row()
  Oszlop: col()
  Régió: cv::Rect osztállyal.
- Matlab stílusú inicializálók: zeros, ones, eye
- resize()
- reshape()
- mul()
### cv::Mat osztály főbb adattagjai és metódusai:
- rows
- cols
- type()
- channels()
- copyTo()
- setTo()
- clone()

# <p align="center">Színkezelés</p>
## Színmodellek
### Szürkeskála: 
- Csak intenzitásértékeket tárol egy csatornán.
#### OpenCv:
- Mátrix típus: CV_8UC1
- Pont típus: img.at<uchar>(i, j)
- Tartomány: I ∈ [0, 255]
### RGB:
- Piros, zöld és kék alapszínekből keveri ki a színeket.
- 16 millió szín kódolható
#### OpenCv:
- Mátrix típus: CV_8UC3
- Pont típus: img.at<Vec3b>(i, j)
- Tartomány: R, G, B ∈ [0, 255]
- Csatornák indexe: 0 – kék , 1 – zöld , 2 – piros
### HSV:
- Hue: megadja a szín pontos típusát.
- Saturation: a szürke aránya a képen.
- Value/Brightness: az adott pixel világosságát jelenti.
#### OpenCv:
- OpenCV:
- Mátrix típus: CV_8UC3
- Pont típus: img.at<Vec3b>(i, j)
- Tartomány:
    - H ∈ [0, 360]
    - S ∈ [0,100]
    - V ∈ [0,100]
- Csatornák indexe: 0 – Hue , 1 – Saturation , 2 – Value

## <p align="center">Küszöbölés</p>
- Lényege, hogy az adott kép teljes intenzitásintervallumát kisebb intervallumokra osztjuk fel.
- Azt az értéket, ahol a teljes intervallumot szétdaraboljuk, küszöbértéknek nevezzük.
- Az egyes intervallumokhoz bináris esetben 1-et vagy 0-t rendelünk, eredményül kapunk egy bináris maszkot.
### OpenCV-ben eljárások:
- #### egyszerű küszöbölés
    -  Választunk egy tetszőleges globális küszöbértéket, amivel elvégezzük a küszöbölést a kép összes pixelére.
    -  Azokban az esetekben jó, amikor meg tudjuk pontosan határozni előre ezt az értéket, és nem fog változni a feldolgozás során.
- #### globális küszöbölés
- #### adaptív küszöbölés
    - Abban az esetben, ha a képen a megvilágítás nem volt mindenütt állandó, változó küszöbértéket választunk.
    - A változó küszöbérték leköveti a képrészeken a megváltozott megvilágítást, fényviszonyokat.
### KÉPEK VÁGÁSA
- Lényege, hogy a teljes kép egy adott részét hagyjuk csak meg
- Definiálunk egy vágási tartományt, amelyen belül az eredeti kép pixeleinek értékét megtartjuk.
- Eredményként értelemszerűen kisebb képet fogunk kapni.
### MORFOLÓGIAI OPERÁTOROK
- A morfológia a képek strukturális és alakelemzését jelenti 
- Lényege, hogy egy megválasztott alakzat segítségével bejárjuk a teljes képet, és egy definiált műveletet megadva állítjuk elő az eredményképet.
  #### A főbb morfológiai műveletek:
  
Dilatáció (vastagító hatása van)

Erózió ( vékonyító hatása van)

Nyitás ( eltünteti a kisebb hibákat, és zajokat)

Zárás (az üres alakzatokat tölti fel)
