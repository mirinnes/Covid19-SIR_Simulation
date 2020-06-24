#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <math.h>
using namespace std;

//Funciones
//float numale(float *, float *);
void mostrarMatriz(float **, int, int);
//int newInfected(float **, float **, int, int, float);
//void asignRandom(float **, int, int);
//void escribirMatrizIn(float **, int, int);
//void escribirMatrizFin(float **, int, int);
//void clean(float **, int);
//void movePos(float **, int, int);


//Variables y Parámetros
float **puntero_positions, linf, lsup, contag;
int nHab, nSus, nInf=1, nCol=3, tFinal, semilla, newInf;
//ofstream fout("position_ini.dat"), foutnew("position_fin.dat");


int main() {
        // ///////////////////////////////Ingreso de datos
    cout << "Ingrese nro de habitantes:";
    cin >> nHab;
    //cout << "Ingrese la distancia de contagio:";
    //cin >> contag;
    //cout << "Ingrese limite inferior de coordenadas:";
    //cin >> linf;
    //cout << "Ingrese limite superior de coordenadas:";
    //cin >> lsup;
    //cout << "Ingrese el valor de la semilla:";
    //in >> semilla;
    //   srand(semilla);
    //    nSus=nHab-1;

    // //////////////////////////////Generacion de los Array [nHabx3]
        puntero_positions = new float* [nHab];

        for (int i=0; i<nHab; i++) {
            puntero_positions[i] = new float [nCol];
        }

        cout << "\nDigitando los elementos de la matriz: \n";
        for(int i=0; i<nHab; i++) {
            for(int j=0; j<nCol-1; j++){
                cout<<"Digite un numero ["<<i<<"]["<<j<<"]: ";
                cin>>*(*(puntero_positions+i)+j); 
            }
        }

        for(int i=0; i<nHab; i++) {
                cout<<"Digite el estado de ["<<i<<"][3]: ";
                cin>>*(*(puntero_positions+i)+2); 
            
        }

    mostrarMatriz(puntero_positions,nHab,nCol);
}

void mostrarMatriz(float **array, int filas, int col) {
    float aux [3];
    for (int i=0; i<filas; i++) {
        for (int j=0; j<col; j++) {
            aux[j] =  *(*(array+i)+j);
        }
            cout << aux[0] << " " << aux[1] << " " << aux[2] << endl;
    }
    cout << "\n\n";
}


