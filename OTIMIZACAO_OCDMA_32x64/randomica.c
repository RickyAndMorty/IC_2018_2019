#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** alloca2DD(int linhas, int colunas)
{
    int i;
    double** matriz = NULL;
    matriz = ((double**)malloc(linhas * sizeof(double*)));
    if(matriz == NULL)
    {
        printf("Erro.\n");
        exit(1);
    }
    for(i = 0; i < linhas; i ++)
    {
        matriz[i] = ((double*)malloc(colunas * sizeof(double)));
        if(matriz[i] == NULL)
        {
            printf("Erro.\n");
            exit(1);
        }
    }
    return matriz;
}

double constante1()
{
    return (1.00 + ((double)(rand()))/RAND_MAX);//2.0
}

double constante2()
{
    //time_t t;
	//srand((unsigned) time(&t));
    return (1.00 + ((double)(rand()))/RAND_MAX);//2.0
}
double** randomica(int linhas, int colunas)
{
    double** matriz = NULL;
    matriz = alloca2DD(linhas,colunas);
    int i,j;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < linhas; i ++)
    {
        for(j = 0; j < colunas; j ++)
        {
            matriz[i][j] = ((double)(rand())) /RAND_MAX;
        }
    }
    return matriz;
}
