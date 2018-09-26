#include "alloca.h"
#include <stdio.h>
#include <stdlib.h>

// Esta classe é responsável por alocar vetores e matrizes dinamicamente.
alloca::alloca()
{
    //ctor
}

alloca::~alloca()
{
    //dtor
}
//Metodo que aloca uma matriz do tipo double e retorna o endereço do ponteiro que aponta para a posição alocada.
double** alloca::allocaMatrizD(int linhas,int colunas)
{
    int i;
    double** matriz = ((double**)calloc(linhas,sizeof(double*)));
    for(i = 0; i < linhas; i ++)
    {
        matriz[i] = ((double*)calloc(colunas,sizeof(double)));
    }
    return matriz;
}
//Metodo que aloca um vetor do tipo double e retorna o endereço do ponteiro que aponta para a posição alocada.
double* alloca::allocaVetorD(int colunas)
{
    double* vetor = ((double*)calloc(colunas,sizeof(double)));
    return vetor;
}
int** alloca::allocaMatrizI(int linhas,int colunas)
{
    int i;
    int** matriz = ((int**)calloc(linhas,sizeof(int*)));
    for(i = 0; i < linhas; i ++)
    {
        matriz[i] = ((int*)calloc(colunas,sizeof(int)));
    }
    return matriz;
}
int* alloca::allocaVetorI(int colunas)
{
    int* vetor = ((int*)calloc(colunas,sizeof(int)));
    return vetor;
}
double** alloca::liberaMatrizD(double** matriz, int linhas)
{
    int i;
    for(i = 0; i < linhas; i ++)
    {
        free(matriz[i]);
        matriz[i] = NULL;
    }
    free(matriz);
    matriz = NULL;
    return matriz;
}
double* alloca::liberaVetorD(double* vetor)
{
    free(vetor);
    vetor = NULL;
    return vetor;
}
int** alloca::liberaMatrizI(int** matriz, int linhas)
{
    int i;
    for(i = 0; i < linhas; i ++)
    {
        free(matriz[i]);
        matriz[i] = NULL;
    }
    free(matriz);
    matriz = NULL;
    return matriz;
}
int* alloca::liberaVetorI(int* vetor)
{
    free(vetor);
    vetor = NULL;
    return vetor;
}


