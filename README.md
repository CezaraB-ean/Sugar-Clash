# Sugar-Clash
! Important !
Nu recomand rularea din Command Prompt deoarece am incercat si am primit erori care consider ca ar lua mai mult timp si efort decat instalarea CLion si urmarirea pasilor de mai jos. Va multumesc.

Mod de rulare:
Creati un proiect nou in CLion 2025.2.2 si alegeti standardul C++20.
In fisierul principal al proiectului veti avea un fisier 'main.cpp'. In acesta copiati codul din fisierul 'main.cpp' din repository.
Pentru fisierele de rezultate creati doua fisiere de tip .csv in folder-ul 'cmake-build-debug' (in acesta va aparea si fisierul .exe al proiectului dupa prima rulare).
Redenumiti fisierele de rezultate astfel: "rezultate.csv" si "rezultate_testare.csv".
Rulati proiectul asigurandu-va ca nu exista nicio eroare sau biblioteci lipsa.
Programul va cere un input in consola. Tastati 1 sau 2 pentru modul de testare (cu seed fix, mod determinist), respectiv modul de simulare (100 de jocuri complet aleatoare)

Clarificari:
 - swap* = o schimbare intre un element si vecinul acestuia de pe linie sau coloana;
     *In program exista functia 'swap', care determina mai intai cel mai bun swap existent dintr-o matrice de tip joc, si mai apoi realizeaza doar cel mai bun swap gasit

- scorul - fiecare formatiune valoreaza un anumit punctaj, care este adaugat intr-o variabila numita 'scor_local' in functia principala de eliminare; punctajul tuturor
      formatiunilor eliminate pentru un apel al functiei 'eliminatorul' este adaugat in variabila globala 'scor_total' care este scorul pe un anume joc

- suprapunerile - formatiunile sunt eliminate in ordine descrescatoare punctajelor pe care acestea le ofera la eliminare (linii de 5> T-uri> L-uri> linii de 4> linii de 3
      Inainte de eliminarea unei formatiuni se verifica daca in aceasta exista minim un 0, daca exista (adica daca elementul care este acum 0 a facut parte dintr-o formatiune mai valoroasa), se trece la urmatoarea formatiune gasita, ignorandu-se astfel toate formatiunile care au avut deja minim un element ("bomboana") eliminat

- reproducere a 100 de jocuri - momentan nu este posibila producerea a 100 de jocuri intr-un mod determinist; a fost implementata doar reproducerea determinista a unui joc de testare care, consider eu, reprezinta foarte bine pasii de eliminare si modul de tratare al suprapunerilor formatiunilor

- fisierele de rezultat - acestea sunt in format .csv; CLion afiseaza aceste fisiere in modul text in care datele sunt separate prin virgula, insa se poate schimba modul de vizualizare a datelor pentru a ajunge la modul de afisare prezentat in .pptx

- stagnare - in cateva sute de jocuri generate nu s-a ajuns la niciun joc in care sa nu existe minim un swap astfel incat jocul sa continue; pentru un scor tinta mai mare sau pentru mii, zeci sau chiar sute de mii de jocuri generate exista sansa sa se gaseasca un astfel de joc, insa, fara un mod determinist de a rula programul pentru toate jocurile generate nu se poate verifica realist daca rata de succes de 100% este reala sau artificial crescuta datorita unor interactiuni dintre generarea aleatorie a "bomboanelor" si modului de detectare si eliminare a formatiunilor existente neprevazute sau chiar eronate;

- rulare folosind CLI: asa cum am precizat la inceputul fisierului acest mod nu este recomandat, insa pentru expertii in acest mod de a rula fisiere se aduce la cunostinta ca nu exista parametrii necesari la rulare, programul va cere un input de tip int ( 1 sau 2 ) dupa care se va alege modul de rulare, pentru orice alta valoare programul va ajunge instantaneu la instructiunea 'return 0;' si se va incheia rularea (programul va specifica clar ca doreste 1 sau 2, instructiuni mai usoare de urmat nu exista, consider eu)

Observatii: 

Intrucat cerinta presupune crearea unui program cat mai eficient din punct de vedere al timpului am folosit limbajul C++ si am abordat problema in cel mai 
brut-force mod posibil (o multitudine de bucle for, copieri de matrici, zeci sau chiar sute de posibile schimbari de elemente pentru o stare a jocului, etc.), pentru a arata eficienta acestui limbaj in pofida unei abordari neeficiente. 
Cu abordarea precizata mai sus programul a rulat, pe un calculator cu piese vechi de mai mult de 5 ani, pentru 1000 de jocuri (de 10 ori mai multe decat in cerinta) intr-un timp de aproximativ 3 minute (adica ~180 secunde). 
Asadar, timpul cerut a fost depasit cu doar 50% pentru o rulare a programului folosind de 10 ori mai multe jocuri
