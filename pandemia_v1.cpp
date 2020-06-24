#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

//Funciones
int countRec(float**,int);
void aumentoTiempoRecuperados(float**, int, int);
float validacionMovePos(float);
void movePos(float **, int, int);
float calculaDistancia(float, float, float, float);
string validacionVecNeue(int , vector<int>);
int newInfected(float **, int, float);
void asignRandomXY(float **, int);
void iniciaInfectadoRecupTime(float **, int);
void ingresoDeDatos();
void ficheroEncabezado();
void ficheroWrite(int,int,int,int); 
void mostrarMatriz(float **, int, int);
float numale(float *, float *);



//Variables y Parámetros
string resp="si";
float **puntero_positions, linf, lsup, dContag;
int nHab, nCol=4, tFinal, semilla;
int nRec, newRec, nSus, nInf, newInf, time=0, tRec;

//Archivos 
ofstream result("RESULT.out");

int main() {
    ingresoDeDatos(); //nHab,dContag,linf,lsup,semilla,tFinal,tRec
        ficheroEncabezado();
        srand(semilla);
        /*------------------Generacion de arreglos*/
            puntero_positions = new float* [nHab];
        for (int i=0; i<nHab; i++) {
            puntero_positions[i] = new float [nCol];
        }
        /*----------------------------------------*/
    asignRandomXY(puntero_positions,nHab); //asignacion de posiciones aleatorias
    iniciaInfectadoRecupTime(puntero_positions,nHab); //estado de infectados, susceptibles e inicializacion de tiempo de recuperacion
            nRec=0;
            nInf=1;
            nSus=nHab-nInf; 
        /*----------------------------------------*/
        ficheroWrite(time, nSus, nInf, nRec);

        /*--------Comienzo de la iteración---------*/
        aumentoTiempoRecuperados(puntero_positions,nHab,tRec);
            newRec=countRec(puntero_positions,nHab);
            newInf=newInfected(puntero_positions, nHab, dContag);
            nRec=nRec+newRec;        
            nInf= nInf+newInf-newRec;
            nSus= nSus-newInf;
        cout << "\n\nDesea iterar? ";
        cin >> resp;

    while(time<tFinal && resp=="si") {
        movePos(puntero_positions, nHab, nCol);
            time++;
        ficheroWrite(time,nSus,nInf,nRec);
        aumentoTiempoRecuperados(puntero_positions,nHab,tRec);
            newRec=countRec(puntero_positions,nHab);
            newInf=newInfected(puntero_positions, nHab, dContag);
            nRec=nRec+newRec;        
            nSus= nSus-newInf;
            nInf= nInf+newInf-newRec;

        cout << "\n\nDesea iterar? ";
        cin >> resp;    
    } 
        /*----------------------------------------*/

}


// //////////////////////////////Contador de Recuperados
int countRec(float** array,int nFilas) {
  cout<<"\nContador de recuperados";
  int count=0;
  for (int i=0; i<nFilas; i++) {
        if( *(*(array+i)+2) == -1 ) {
            count++;
        }
    }
    return count;
}

// //////////////////////////////Tiempo Recuperados
void aumentoTiempoRecuperados(float **array, int nFilas, int time) {
  cout<<"\nAumento de tiempo en los estados recuperados";
  for (int i=0; i<nFilas; i++) {
        if( *(*(array+i)+2) != 0 ) {
            *(*(array+i)+3)=*(*(array+i)+3) + 1;
        }

        if(*(*(array+i)+3)==time+1) {
            *(*(array+i)+2) = -1;
        } else if (*(*(array+i)+3)>time+1) {
            *(*(array+i)+2) = 99;
        }
    }  
}


// /////////////////////////////Validacion - Mover Posiciones
float validacionMovePos(float pos) {
    float lado=lsup-linf;
    if(pos<linf) {
               pos = pos+lado;
               return pos;
    } else if (pos>lsup) {
               pos = pos-lado;
               return pos;
           } else {
               return pos;
           }
}


// //////////////////////////////Mover posiciones
void movePos(float **array, int filas, int col) {
    cout << "Moviendo posiciones entre el cuadrado: "<<linf<<" , "<<lsup<<endl;
    float min=-0.5, max=0.5;
    for (int i=0; i<filas; i++) {
        for (int j=0; j<2; j++) {
           *(*(array+i)+j) = *(*(array+i)+j) + numale(&min,&max);
            *(*(array+i)+j) = validacionMovePos(*(*(array+i)+j));
        }
    }
}





// ///////////////////////////////Validacion - No Repeat en Nuevos Infectados
string validacionVecNeue(int i, vector<int> arr) {
    string find="false";
                    for(int k : arr) {
                        if (k==i) find="true";
                    }
    return find;
}
// //////////////////////////////Calculo de nuevos infectados
int newInfected(float **puntero_positions, int nFilas, float contagio) {
cout<<"\nCalculo de nuevos infectados"<<endl;
float dist, dx, dy;
vector<int> vecNeue;
int neue=0;
string find;
for (int i=0; i<nFilas; i++) {
    if( *(*(puntero_positions+i)+2) == 1 ) {
        for (int j=0; j<nFilas; j++) {
            if( *(*(puntero_positions+j)+2) == 0 ) {
                find=validacionVecNeue(j,vecNeue);
                if(find=="false") {
                    float ax=*(*(puntero_positions+i)+0);
                    float ay=*(*(puntero_positions+i)+1);
                    float bx=*(*(puntero_positions+j)+0);
                    float by=*(*(puntero_positions+j)+1);
                    dist=calculaDistancia(ax,ay,bx,by);
                    cout<<"\nLa distancia de ["<< i << "] a [" << j << "] es: " << dist;
                    if (dist < contagio) {
                            cout << "\nOh no! Se contagio [" << j << "]";
                            vecNeue.push_back(j);
                            neue++;
                        }
                }
            }
        }
    }
}
for(int i : vecNeue) {
    for(int j=0; j<nFilas; j++) {
        if (i==j) {
            *(*(puntero_positions+j)+2) = 1;
        }
    }
}
return neue;
}





// //////////////////////////////Asignacion de valores aleatorios en matriz
void asignRandomXY(float **array, int filas){
    for (int i=0; i<filas; i++) {
        for (int j=0; j<2; j++) {
           *(*(array+i)+j) = numale(&linf,&lsup);
        }
    }
}

// //////////////////////////////Inicializacion del primer infectado
void iniciaInfectadoRecupTime(float **puntero_positions, int nFilas){
        for(int i=0; i<nFilas; i++) {
            if(i==0) { *(*(puntero_positions+i)+2)=1; }
            else { *(*(puntero_positions+i)+2)=0; }
            *(*(puntero_positions+i)+3)=0;
        }
}





// ///////////////////////////////Ingreso de datos
void ingresoDeDatos() {
    cout << "Ingrese nro de habitantes:";
    cin >> nHab;
    cout << "Ingrese la distancia de contagio:";
    cin >> dContag;
    cout << "Ingrese limite inferior de coordenadas:";
    cin >> linf;
    cout << "Ingrese limite superior de coordenadas:";
    cin >> lsup;
    cout << "Ingrese el valor de la semilla:";
    cin >> semilla;
    cout << "Duracion del periodo de pandemia: ";
    cin >> tFinal;
    cout << "Duracion de tiempo de contagio: ";
    cin >> tRec;


}

void ficheroEncabezado() {
        result<<"#---------------------------------------------------"<<endl;
        result<<"#                 SIR simulation 2020               "<<endl;
        result<<"#                         by mirinnes               "<<endl;
        result<<"#----------------------------------------------------"<<endl;
        result<<"#                                                     "<<endl;
        result<<"#CANT HAB: "<<nHab<<endl;
        result<<"#REGION: ["<<linf<<","<<lsup<<"]x["<<linf<<","<<lsup<<"]"<<endl;
        result<<"#PERIOD DUR: "<<tFinal<<endl;
        result<<"#LONG CONTAG: "<<dContag<<endl;
        result<<"#D   S    I    R"<<endl;
}

void ficheroWrite(int time,int nSus,int nInf,int nRec) {
    result<<time+1<<"    "<<nSus<<"    "<<nInf<<"    "<<nRec<<endl;
}

// ///////////////////////////////Otras
//void mostrarMatriz(float **array, int filas, int col) {
//    cout << "\nMostrar matriz\n";
//    float aux [col];
//    for (int i=0; i<filas; i++) {
//        for (int j=0; j<col; j++) {
//            aux[j] =  *(*(array+i)+j);
//        }
//            cout << i << " : " << aux[0] << " " << aux[1] << " - " << aux[2] << " " << aux[3] << endl; //En aux[3] podria ser aux[3]+1 por que es confuso ya que tiene inicialmente el dia "0"
//    }
//}

float numale(float *liminf, float *limsup) {   
	float aux;  

	aux=(float)rand()/(float)RAND_MAX;
	
    return aux*(*limsup-*liminf)+*liminf;
}

float calculaDistancia(float ax, float ay, float bx, float by){
    float dx, dy, dist;
    dx = ax-bx;
    dy = ay-by;
    return dist = sqrt((dx*dx) + (dy*dy));
}