#include "resultados.h"

resultados::resultados()
{
    //ctor
}

resultados::~resultados()
{
    //dtor
}
void resultados::setUsers(int _users)
{
    users = _users;
}

void resultados::setPgbest(int linhas, int colunas)
{
    pgbest = memoria.allocaMatrizD(linhas,colunas);
}
double** resultados::getPgbest()
{
    return pgbest;
}
void resultados::salvarSNIR(double* pgbest, double** G, double* g_t, double sigma,int iteration, int users)
{
    int i,j;
    double* aux1 = NULL;
    double** aux2 = NULL;
    aux1 = memoria.allocaVetorD(users);
    aux2 = memoria.allocaMatrizD(users,users);

    for(i= 0; i < users; i ++)
    {
        for(j = 0; j < users; j ++)
        {
            aux2[i][j] = pgbest[j];
        }
    }
    for(i = 0; i < users; i ++)
    {
        for(j = 0; j < users; j ++)
        {
            aux1[i] = aux1[i] + (aux2[i][j] * G[i][j]);
        }
    }

    for(i = 0; i < users; i ++)
    {
        snir[iteration][i] = (pgbest[i] / (aux1[i] - pgbest[i] + (sigma / g_t[i])));
    }
    aux1 = memoria.liberaVetorD(aux1);
    aux2 = memoria.liberaMatrizD(aux2, users);
}

void resultados::setSnir(int iterations, int users)
{
    snir = memoria.allocaMatrizD(iterations,users);
}

void resultados::gravarMatriz(double** matriz, int linhas, int colunas)
{
    FILE *pArq;
    int i,j;
    if((pArq = fopen("C:/git/IC_2018_2019/resultados/teste.txt", "w")) == 0x0)
    {
        printf("erro.");
        exit(1);
    }

    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            fprintf(pArq, "%e\t", matriz[i][j]);
        }
        fprintf(pArq, "\n");
    }

    if(fclose(pArq))
    {
        printf("erro.");
        exit(1);
    }
}
void resultados::salvarPgbest(double* _pgbest, int z)
{
    int i;
    for(i = 0; i < users; i ++)
    {
        pgbest[z][i] = _pgbest[i];
    }
}
double** resultados::getSnir()
{
    return snir;
}
