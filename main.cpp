#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int joc[11][11],scor_total=0;

unsigned int seed_testare = 123456;
mt19937 rng(seed_testare);

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1,4);

void generare() {
    for (auto & i : joc) {
        for (int & j : i) {
            j = dist(gen);
        }
    }
}

void afisare(int matrice[11][11]) {
    cout<< "Matricea este:\n";
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}

int noduri[250][7],nrNoduri=0;
// noduri[k][0] - indicele de linie
// noduri[k][1] - indicele de coloana
// noduri[k][2] - orientarea formatiei: 0/1 - linie orizontala/verticala; 0/1 - L "colt-de-sus", 2/3 - L "colt-de-jos"; 0/1 - T 90/270 de grade, 2/3 - T 180/0 de grade;
// noduri[k][3] - lungimea liniei
// noduri[k][4] - punctaj formatiune: 5 - linie/coloana de 3; 10 - linie/coloana de 4; 20 - L; 30 - T; 50 - linie/coloana de 5;
// noduri[k][5] - orientare initiala (linie/coloana)
// noduri[k][6] - culoarea celulei nod

void determinare_linii(int matrice[11][11], int i, int j) {
    int n=0,element_curent = matrice[i][j];
    if (j<=8) {
        while (element_curent == matrice[i][j] && j+1+n <= 11 && n < 5 ) {
            element_curent = matrice[i][j+1+n];
            n++;
        }
        if (n>=3) {
            noduri[nrNoduri][0] = i;
            noduri[nrNoduri][1] = j;
            noduri[nrNoduri][2] = 0;
            noduri[nrNoduri][5] = 0;
            noduri[nrNoduri][3] = n;
            noduri[nrNoduri][6] = matrice[i][j];
            if (n==3)
                noduri[nrNoduri][4] = 5;
            if (n==4)
                noduri[nrNoduri][4] = 10;
            if (n>=5)
                noduri[nrNoduri][4] = 50;
            nrNoduri++;
        }
    }
    element_curent = matrice[i][j];
    n=0;
    if (i<=8) {
        while (element_curent == matrice[i][j] && i+1+n <= 11 && n < 5) {
            element_curent = matrice[i+1+n][j];
            n++;
        }
        if (n>=3) {
            noduri[nrNoduri][0] = i;
            noduri[nrNoduri][1] = j;
            noduri[nrNoduri][2] = 1;
            noduri[nrNoduri][5] = 1;
            noduri[nrNoduri][3] = n;
            noduri[nrNoduri][6] = matrice[i][j];
            if (n==3)
                noduri[nrNoduri][4] = 5;
            if (n==4)
                noduri[nrNoduri][4] = 10;
            if (n>=5)
                noduri[nrNoduri][5] = 50;
            nrNoduri++;
        }
    }
}

void detectatorul(int matrice[11][11]) {
    nrNoduri = 0;
    for (int i=0;i<250;i++) {
        for (int j=0;j<7;j++) {
            noduri[i][j] = 0;
        }
    }
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            //cout<<"I este: "<<i<<" J este: "<<j<<endl;
            if (matrice[i][j]!=0)
                determinare_linii(matrice, i, j);
        }
    }
}

void clasificare_formatiuni() {
    for (int k = 0; k <nrNoduri; k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][3] != 5) {
            for (int a = 0; a < nrNoduri; a++) {
                if (k == a)
                    continue;

                if (noduri[k][6] != noduri[a][6])
                    continue;

                if (noduri[k][4]<20) {

                    if (noduri[a][0] == i && noduri[a][1] == j) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 0;
                    }

                    if (noduri[a][0] == i && noduri[a][1] == j + 2 && noduri[k][5] == 0) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 1;
                    }
                    if (noduri[a][0] == i && noduri[a][1] == j - 2 && noduri[k][5] == 1) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 1;
                    }

                    if (noduri[a][0] == i + 2 && noduri[a][1] == j && noduri[k][5] == 1) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 2;
                    }
                    if (noduri[a][0] == i - 2 && noduri[a][1] == j && noduri[k][5] == 0) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 2;
                    }

                    if (noduri[a][0] == i + 2 && noduri[a][1] == j - 2 && noduri[k][5] == 1) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 3;
                    }
                    if (noduri[a][0] == i - 2 && noduri[a][1] == j + 2 && noduri[k][5] == 0) {
                        noduri[k][4] = 20;
                        noduri[k][2] = 3;
                    }

                } // if-uri pentru L-uri

                if (noduri[k][4]<30) {

                    if (noduri[a][0] == i && noduri[a][1] == j + 1 && noduri[a][5] == 1 && noduri[k][5] == 0 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 0;
                    } // noduri[k] - linie
                    if (noduri[a][0] == i && noduri[a][1] == j - 1 && noduri[a][5] == 0 && noduri[k][5] == 1 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 0;
                    } // noduri[k] - coloana

                    if (noduri[a][0] == i - 2 && noduri[a][1] == j + 1 && noduri[a][5] == 1 && noduri[k][5] == 0 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 1;
                    } // noduri[k] - linie
                    if (noduri[a][0] == i + 2 && noduri[a][1] == j - 1 && noduri[a][5] == 0 && noduri[k][5] == 1 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 1;
                    } // noduri[k] - coloana

                    if (noduri[a][0] == i - 1 && noduri[a][1] == j && noduri[a][5] == 1 && noduri[k][5] == 0 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 2;
                    } // noduri[k] - linie
                    if (noduri[a][0] == i + 1 && noduri[a][1] == j && noduri[a][5] == 0 && noduri[k][5] == 1 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 2;
                    } // noduri[k] - coloana

                    if (noduri[a][0] == i - 1 && noduri[a][1] == j + 2 && noduri[a][5] == 1 && noduri[k][5] == 0 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 3;
                    } // noduri[k] - linie
                    if (noduri[a][0] == i + 1 && noduri[a][1] == j - 2 && noduri[a][5] == 0 && noduri[k][5] == 1 && noduri[a][3]>=3 && noduri[a][3]<=4) {
                        noduri[k][4] = 30;
                        noduri[k][2] = 3;
                    } // noduri[k] - coloana

                } // if-uri pentru T-uri
            }
        }
    }
}

int eliminare_linie(int matrice[11][11], int k) {
    int scor =0;
    int i = noduri[k][0];
    int j = noduri[k][1];
    bool gasit=false;
    int n = 0;

    if (noduri[k][2]==0) {
        n=0; gasit=false;
        while (j+n<=10 && n < noduri[k][3] ) {
            if (matrice[i][j+n]==0)
                gasit = true;
            n++;
        }
        if(gasit==false) {
            n=0;
            while (j+n<=10 && n < noduri[k][3] ) {
                matrice[i][j+n] = 0;
                n++;
            }
        }
    }

    if (noduri[k][2]==1) {
        n=0; gasit=false;
        while (i+n<=10 && n<noduri[k][3]) {
            if ( matrice[i+n][j]==0 )
                gasit = true;
            n++;
        }
        if(gasit==false) {
            n=0;
            while ( i+n<=10 && n<noduri[k][3]) {
                matrice[i+n][j] = 0;
                n++;
            }
        }
    }

    if (gasit==false)
        switch (noduri[k][3]) {
            case 3: scor = 5;   break;
            case 4: scor = 10;  break;
            case 5: scor = 50;  break;
            default: break;
        }
    return scor;
}

int eliminare_L(int matrice[11][11], int k) {
    int i = noduri[k][0];
    int j = noduri[k][1];
    bool gasit=false;

    switch (noduri[k][2]) {
        case 0:
            gasit=false;
            for (int col = j; col <= j + 2; col++)
                if (matrice[i][col] == 0) gasit = true;
            for (int lin = i; lin <= i + 2; lin++)
                if (matrice[lin][j] == 0) gasit = true;

            if (gasit==false) {
                for (int col = j; col <= j + 2; col++)
                    matrice[i][col] = 0;
                for (int lin = i; lin <= i + 2; lin++)
                    matrice[lin][j] = 0;
            }
            break;
        case 1:
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j + 2; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i; lin <= i + 2; lin++)
                    if (matrice[lin][j+2] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j + 2; col++)
                        matrice[i][col] = 0;
                    for (int lin = i; lin <= i + 2; lin++)
                        matrice[lin][j+2] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j-2; col <= j; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i; lin <= i + 2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j-2; col <= j; col++)
                        matrice[i][col] = 0;
                    for (int lin = i; lin <= i + 2; lin++)
                        matrice[lin][j] = 0;
                }
            }
            break;
        case 2:
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i-2; lin <= i; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i+2][col] = 0;
                    for (int lin = i-2; lin <= i; lin++)
                        matrice[lin][j] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i+2][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                     for (int col = j; col <= j+2; col++)
                        matrice[i+2][col] = 0;
                     for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }
            break;
        case 3:
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i][col] == 0) gasit=false;
                for (int lin = i-2; lin <= i; lin++)
                    if (matrice[lin][j+2] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i+2][col] = 0;
                    for (int lin = i-2; lin <= i; lin++)
                        matrice[lin][j] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j-2; col <= j; col++)
                    if (matrice[i+2][col] == 0) gasit=false;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j-2; col <= j; col++)
                        matrice[i+2][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }
            break;
        default: cout<<"Am intampinat o problema la L-uri!\n"; break;
    }
    if (gasit==false)
        return 20;
    else
        return 0;
}

int eliminare_T(int matrice[11][11], int k) {
    int i = noduri[k][0];
    int j = noduri[k][1];
    bool gasit=false;

    switch (noduri[k][2]) {
        case 0: // T
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j+1] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j+1] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j-1; col <= j+1; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j-1; col <= j+1; col++)
                        matrice[i][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j+1] = 0;
                }
            }
            break;
        case 1: // _|_
           if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i+2][col] == 0) gasit=true;
                for (int lin = i-2; lin <= i; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i+2][col] = 0;
                    for (int lin = i-2; lin <= i; lin++)
                        matrice[lin][j] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j-1; col <= j+1; col++)
                    if (matrice[i+2][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j-1; col <= j+1; col++)
                        matrice[i+2][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }
            break;
        case 2: // |--
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i-1; lin <= i+1; lin++)
                    if (matrice[lin][j] == 0) gasit=true;
                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i][col] = 0;
                    for (int lin = i-1; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }

            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j; col <= j+2 && col<=10; col++)
                    if (matrice[i+1][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;
                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i+1][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }

            break;
        case 3: // --|
            if(noduri[k][5]==0) //linie
            {
                gasit=false;
                for (int col = j; col <= j+2; col++)
                    if (matrice[i][col] == 0) gasit=true;
                for (int lin = i-1; lin <= i+1; lin++)
                    if (matrice[lin][j+2] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j; col <= j+2; col++)
                        matrice[i][col] = 0;
                    for (int lin = i-1; lin <= i+1; lin++)
                        matrice[lin][j+2] = 0;
                }
            }
            if(noduri[k][5]==1) //coloana
            {
                gasit=false;
                for (int col = j-2; col <= j; col++)
                    if (matrice[i+1][col] == 0) gasit=true;
                for (int lin = i; lin <= i+2; lin++)
                    if (matrice[lin][j] == 0) gasit=true;

                if (gasit==false) {
                    for (int col = j-2; col <= j; col++)
                        matrice[i+1][col] = 0;
                    for (int lin = i; lin <= i+2; lin++)
                        matrice[lin][j] = 0;
                }
            }
            break;
        default: cout<<"Am intampinat o problema la T-uri la k = "<<k<<endl; break;
    }

    if (gasit==false)
          return 30;
    else
        return 0;
}

int eliminatorul(int matrice[11][11]) {
    int scor_local= 0;

    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=50)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }

    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=30)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_T(matrice,k);
    }

    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=20)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_L(matrice,k);
    }

    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=10)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }

    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=5)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }

    return scor_local;
}

int eliminatorul_detestare(int matrice[11][11]) {
    int scor_local= 0;
    afisare(matrice);
    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=50)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }
    afisare(matrice);
    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=30)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_T(matrice,k);
    }
    afisare(matrice);
    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=20)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_L(matrice,k);
    }
    afisare(matrice);
    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=10)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }
    afisare(matrice);
    for (int k=0;k<nrNoduri;k++) {
        int i = noduri[k][0];
        int j = noduri[k][1];
        if (noduri[k][4]!=5)
            continue;
        if (matrice[i][j]==0)
            continue;
        scor_local += eliminare_linie(matrice,k);
    }
    afisare(matrice);
    return scor_local;
}

void gravitas(int matrice[11][11]) {
    for (int i = 10; i >= 0; i--) {
        for (int j = 10; j >= 0; j--) {
            int n = 0;
            if (matrice[i][j] == 0) {
                while (matrice[i][j] == 0 && n < i ) {
                    n++;
                    matrice[i][j] = matrice[i-n][j];
                }
                matrice[i-n][j] = 0;
            }
        }
    }
}

void regenerare(int matrice[11][11]) {
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            if (matrice[i][j] == 0)
                matrice[i][j] = dist(gen);
}

void regenerare_testare(int matrice[11][11]) {
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            if (matrice[i][j] == 0)
                matrice[i][j] = dist(rng);
}

int gasire_punctaj_maxim(int matrice[11][11]) {
    int scor_temp = 0;
    clasificare_formatiuni();
    scor_temp = eliminatorul(matrice);
    return scor_temp;
}

void copiere(int matrice[11][11],int copie_matrice[11][11]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            copie_matrice[i][j] = matrice[i][j];
        }
    }
}

void schimba (int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

int swap(int matrice[11][11]) {
    int copie_matrice[11][11];
    int punctaj_maxim =0,punctaj_temporar;
    int m=0,pozL=0,pozC=0;
    for ( int i = 0;i < 10;i++) {
        for (int j = 0; j < 10; j++) {

            copiere(matrice, copie_matrice);
            schimba(copie_matrice[i][j], copie_matrice[i][j + 1]);
            detectatorul(copie_matrice);
            if (nrNoduri != 0) {
                punctaj_temporar = gasire_punctaj_maxim(copie_matrice);
                if (punctaj_maxim < punctaj_temporar) {
                    punctaj_maxim = punctaj_temporar;
                    m = 1;
                    pozL = i;
                    pozC = j;
                }
            }

            copiere(matrice, copie_matrice);
            schimba(copie_matrice[i][j], copie_matrice[i + 1][j]);
            detectatorul(copie_matrice);
            if (nrNoduri != 0) {
                punctaj_temporar = gasire_punctaj_maxim(copie_matrice);
                if (punctaj_maxim < punctaj_temporar) {
                    punctaj_maxim = punctaj_temporar;
                    m = 2;
                    pozL = i;
                    pozC = j;
                }
            }
        }
    }

    switch (m) {
        case 1: {
            schimba(matrice[pozL][pozC], matrice[pozL][pozC + 1]);
            copiere(matrice, joc);
            return 1;
        }
        case 2: {
            schimba(matrice[pozL][pozC], matrice[pozL + 1][pozC]);
            copiere(matrice, joc);
            return 1;
        }
        default:
            break;
    }
    return 0;
}

int joc_testare[11][11] = { // aceasi matrice ca cea din prezentare
    {2, 4, 3, 2, 4, 4, 2, 2, 1, 1, 1},
    {3, 3, 4, 2, 2, 2, 2, 2, 4, 4, 1},
    {3, 1, 2, 2, 3, 3, 1, 3, 1, 4, 3},
    {2, 2, 4, 4, 1, 2, 3, 4, 4, 3, 2},
    {2, 3, 1, 2, 1, 1, 4, 3, 3, 3, 4},
    {2, 2, 2, 3, 3, 3, 1, 3, 4, 3, 3},
    {1, 3, 4, 3, 3, 2, 4, 3, 2, 3, 3},
    {1, 2, 1, 1, 2, 4, 1, 4, 2, 2, 3},
    {4, 3, 3, 4, 1, 4, 1, 4, 2, 2, 2},
    {2, 1, 4, 3, 2, 1, 4, 3, 4 ,2, 4},
    {3, 4, 4, 4, 3, 1, 4, 4, 4, 4, 1}
};

int gasire_punctaj_maxim_testare(int matrice[11][11]) {
    int scor_temp = 0;
    clasificare_formatiuni();
    scor_temp = eliminatorul_detestare(matrice);
    return scor_temp;
}

int swap_testare(int matrice[11][11]) {
    int copie_matrice[11][11];
    int punctaj_maxim =0,punctaj_temporar;
    int m=0,pozL=0,pozC=0;
    for ( int i = 0;i < 10;i++) {
        for (int j = 0; j < 10; j++) {

            copiere(matrice, copie_matrice);
            schimba(copie_matrice[i][j], copie_matrice[i][j + 1]);
            detectatorul(copie_matrice);
            if (nrNoduri != 0) {
                punctaj_temporar = gasire_punctaj_maxim(copie_matrice);
                if (punctaj_maxim < punctaj_temporar) {
                    punctaj_maxim = punctaj_temporar;
                    m = 1;
                    pozL = i;
                    pozC = j;
                }
            }

            copiere(matrice, copie_matrice);
            schimba(copie_matrice[i][j], copie_matrice[i + 1][j]);
            detectatorul(copie_matrice);
            if (nrNoduri != 0) {
                punctaj_temporar = gasire_punctaj_maxim(copie_matrice);
                if (punctaj_maxim < punctaj_temporar) {
                    punctaj_maxim = punctaj_temporar;
                    m = 2;
                    pozL = i;
                    pozC = j;
                }
            }
        }
    }

    switch (m) {
        case 1: {
            schimba(matrice[pozL][pozC], matrice[pozL][pozC + 1]);
            copiere(matrice, joc_testare);
            return 1;
        }
        case 2: {
            schimba(matrice[pozL][pozC], matrice[pozL + 1][pozC]);
            copiere(matrice, joc_testare);
            return 1;
        }
        default:
            break;
    }
    return 0;
}

int swap_count=0,loop_prot = 0;
double average_score, average_swaps;
int lista_jocuri[102][6];
// 1 - puncte, 2 - swap-uri, 3 - cascade, 4 - 'scor_atins?', 5 - motiv_oprire (0 = No swap, 1 = Scor atins),

int main() {

    int testare; // variabila folosita pentru alegerea modului de rulare
    cout<<"Alegeti modul de rulare dorit\n 1. Testare pe un anumit joc.\n 2. Simulare a 100 de jocuri.\n";
    cin>>testare;
    if (testare==1) {
        time_t time_inceput;
        time(&time_inceput);

        cout<<"Ati ales modul testare!\n";
        afisare(joc_testare);
        int existaSwap = 1, nrCascade = 0;

        while (loop_prot < 10000 && scor_total < 10000 && existaSwap == 1) {
            detectatorul(joc_testare);
            clasificare_formatiuni();
            if (nrNoduri != 0) {
                scor_total += eliminatorul_detestare(joc_testare);
                gravitas(joc_testare);
                regenerare_testare(joc_testare);
                nrCascade++;
            } else {
                existaSwap = swap_testare(joc_testare);
                swap_count++;
            }
            loop_prot++;
        }
        if (existaSwap == 0 and scor_total < 10000) {
            lista_jocuri[0][1] = scor_total;
            lista_jocuri[0][2] = swap_count;
            lista_jocuri[0][3] = nrCascade;
            lista_jocuri[0][4] = 0;
            lista_jocuri[0][5] = 0;
        } else if (scor_total >= 10000) {
            lista_jocuri[0][1] = scor_total;
            lista_jocuri[0][2] = swap_count;
            lista_jocuri[0][3] = nrCascade;
            lista_jocuri[0][4] = 1;
            lista_jocuri[0][5] = 1;
        } else if (loop_prot == 10000) {
            cout << "S-a iesit datorita protectiei! " << endl << "Scorul la care s-a ajuns este: " << scor_total <<
                    endl;
            afisare(joc_testare);
        }

        ofstream fisier("rezultate_testare.csv");

        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului!\n";
            return 1;
        }
        fisier<<"Joc de testare,";
        for (int i=1; i<6;i++) {
            if (i==4 && lista_jocuri[0][i] == 0)
                fisier << "False"; // nu s-a atins scorul
            else if (i==4 && lista_jocuri[0][i] == 1)
                fisier << "True"; // s-a atins scorul
            else if (i==5 && lista_jocuri[0][i] == 0)
                fisier << "No swaps"; // motiv = No swaps
            else if (i==5 && lista_jocuri[0][i] == 1)
                fisier << "Scor atins"; // motiv = Scor atins
            else
                fisier << lista_jocuri[0][i];
            if (i<5) fisier<<',';
        }

        fisier.close();

        time_t time_sfarsit;
        time(&time_sfarsit);
        cout << ctime(&time_inceput) << endl;
        cout << ctime(&time_sfarsit);

    }
    else if (testare==2) {
        cout << "Ati ales simularea a 100 de jocuri!" << endl;

        time_t time_inceput;
        time(&time_inceput);
        for (int nrJocuri = 1; nrJocuri <= 100; nrJocuri++) {
            swap_count = 0;
            loop_prot = 0;

            int existaSwap = 1, nrCascade = 0;
            scor_total = 0;
            cout << "Jocul cu nr: " << nrJocuri << endl;
            generare();
            afisare(joc);

            while (loop_prot < 10000 && scor_total < 10000 && existaSwap == 1) {
                detectatorul(joc);
                clasificare_formatiuni();
                if (nrNoduri != 0) {
                    scor_total += eliminatorul(joc);
                    gravitas(joc);
                    regenerare(joc);
                    nrCascade++;
                } else {
                    existaSwap = swap(joc);
                    swap_count++;
                }
                loop_prot++;
            }
            if (existaSwap == 0 and scor_total < 10000) {
                lista_jocuri[nrJocuri][1] = scor_total;
                lista_jocuri[nrJocuri][2] = swap_count;
                lista_jocuri[nrJocuri][3] = nrCascade;
                lista_jocuri[nrJocuri][4] = 0;
                lista_jocuri[nrJocuri][5] = 0;
            } else if (scor_total >= 10000) {
                lista_jocuri[nrJocuri][1] = scor_total;
                lista_jocuri[nrJocuri][2] = swap_count;
                lista_jocuri[nrJocuri][3] = nrCascade;
                lista_jocuri[nrJocuri][4] = 1;
                lista_jocuri[nrJocuri][5] = 1;
            } else if (loop_prot == 10000) {
                cout << "S-a iesit datorita protectiei! " << endl << "Scorul la care s-a ajuns este: " << scor_total <<
                        endl;
                afisare(joc);
            }

            average_score += scor_total;
            average_swaps += swap_count;
        }

        average_score /= 100;
        average_swaps /= 100;

        ofstream fisier("rezultate.csv");

        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fisierului!\n";
            return 1;
        }

        for (int i = 1; i <= 100; i++) {
            for (int j = 0; j < 6; j++) {
                if (j==0)
                    fisier << i;
                else if (j==4 && lista_jocuri[i][j] == 0)
                    fisier << "False"; // nu s-a atins scorul
                else if (j==4 && lista_jocuri[i][j] == 1)
                    fisier << "True"; // s-a atins scorul
                else if (j==5 && lista_jocuri[i][j] == 0)
                    fisier << "No swaps"; // motiv = No swaps
                else if (j==5 && lista_jocuri[i][j] == 1)
                    fisier << "Scor atins"; // motiv = Scor atins
                else
                    fisier << lista_jocuri[i][j];
                if (j < 5) fisier << ",";
            }
            fisier << "\n";
        }
        fisier << "Scor average," << average_score<< "," << "Swap-uri average,"<< average_swaps<<endl;

        fisier.close();

        time_t time_sfarsit;
        time(&time_sfarsit);
        cout << ctime(&time_inceput) << endl;
        cout << ctime(&time_sfarsit);
    }
    return 0;
    }
