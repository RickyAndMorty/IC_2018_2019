#include "imprimir.h"
#include <iostream>
#include <math.h>


using namespace std;

imprimir::imprimir()
{
    //ctor
}

imprimir::~imprimir()
{
    //dtor
}

void imprimir::imprimir1DD(double* vetor, int colunas)
{
    for(i = 0; i < colunas; i ++)
    {
        //cout.setf(ios::scientific);
        cout << " " << vetor[i] << endl;
    }
}
void imprimir::imprimir2DD(double** matriz, int linhas, int colunas)
{
    for(i = 0; i < linhas; i ++)
    {
            for(j = 0; j < colunas; j ++)
            {
                cout.setf(ios::scientific);
                cout << " " << matriz[i][j];
            }
            cout << "" << endl;
    }
}

