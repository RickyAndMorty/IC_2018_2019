#include "ic_pso.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <imprimir.h>
ic_pso::ic_pso()
{
    //ctor
}

ic_pso::~ic_pso()
{
    //dtor
}
/*****************sets do PSO************************/
void ic_pso::setSnir(int linhas, int colunas)
{
    snir = memoria.allocaMatrizD(linhas,colunas);

}
void ic_pso::setPosicao(int linhas, int colunas)
{
    posicao = memoria.allocaMatrizD(linhas,colunas);
}
void ic_pso::setVelocidade(int linhas, int colunas)
{
    velocidade = memoria.allocaMatrizD(linhas,colunas);
}
void ic_pso::setG(int linhas, int colunas)
{
    G = memoria.allocaMatrizD(linhas,colunas);
}
void ic_pso::setPibest(int linhas, int colunas)
{
    pibest = memoria.allocaMatrizD(linhas,colunas);
}
void ic_pso::setFth(int linhas, int colunas)
{
    fth = memoria.allocaMatrizD(linhas,colunas);
}
void ic_pso::setGii(int colunas)
{
    Gii = memoria.allocaVetorD(colunas);
}
void ic_pso::setF(int colunas)
{
    F = memoria.allocaVetorD(colunas);
}
void ic_pso::setJp(int colunas)
{
    jP = memoria.allocaVetorD(colunas);
}
void ic_pso::setPgbest(int colunas)
{
    pgbest = memoria.allocaVetorD(colunas);
}
void ic_pso::setJPibest(int colunas)
{
    jPibest = memoria.allocaVetorD(colunas);
}
void ic_pso::setJPgbest(double _jPgbest)
{
    jPgbest = _jPgbest;
}
void ic_pso::setC1(double _c1)
{
    c1 = _c1;
}
void ic_pso::setC2(double _c2)
{
    c2 = _c2;
}
void ic_pso::setW(double _w)
{
    w = _w;
}
void ic_pso::setParticulas(int _particulas)
{
    particulas = _particulas;
}
void ic_pso::setIncognitas(int _incognitas)
{
    incognitas = _incognitas;
}
void ic_pso::setIteracoes(int _iteracoes)
{
    iteracoes = _iteracoes;
}
/******************************gets do PSO**************************************************************/
double** ic_pso::getSnir()
{
    return snir;
}
double** ic_pso::getPosicao()
{
    return posicao;
}
double** ic_pso::getVelocidade()
{
    return velocidade;
}
double** ic_pso::getG()
{
    return G;
}
double** ic_pso::getPibest()
{
    return pibest;
}
double** ic_pso::getFth()
{
    return fth;
}
double* ic_pso::getGii()
{
    return Gii;
}
double* ic_pso::getF()
{
    return F;
}
double* ic_pso::getJp()
{
    return jP;
}
double* ic_pso::getPgbest()
{
    return pgbest;
}
double* ic_pso::getJPibest()
{
    return jPibest;
}
double ic_pso::getJPgbest()
{
    return jPgbest;
}
double ic_pso::getC1()
{
    return c1;
}
double ic_pso::getC2()
{
    return c2;
}
double ic_pso::getW()
{
    return w;
}
int ic_pso::getParticulas()
{
    return particulas;
}
int ic_pso::getIncognitas()
{
    return incognitas;
}
int ic_pso::getIteracoes()
{
    return iteracoes;
}


void ic_pso::calculaPosicao()
{
    int i,j;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            posicao[i][j] = (((double)(rand())) / RAND_MAX) / 100.00F;
        }
    }

}
void ic_pso::calculaPibest()
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            pibest[i][j] = posicao[i][j];
        }
    }
}
void ic_pso::calculaPgbest()
{
    int i;
    for(i = 0; i < incognitas; i ++)
    {
        pgbest[i] = (((double)(rand())) / RAND_MAX) / 100.00F;//pso->Pmax;
    }
}

void ic_pso::calculaG(double** h)
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < incognitas; j ++)
        {
            if(i == j)
            {
                G[i][j] = 1.00;
            }
            else
            {
                G[i][j] = h[i][j];
            }
        }
    }
}

void ic_pso::calculaSnir(double sigma, double* g_t)
{
    int i,j,z;
    double aux1;
    for(z = 0; z < particulas; z ++)
    {
        for(i= 0; i < incognitas; i ++)
        {
            aux1 = 0.00;
            for(j = 0; j < incognitas; j ++)
            {
                aux1 = aux1 + (posicao[i][z] * G[i][j]);
            }
            snir[i][z] = (posicao[i][z] / (aux1 - posicao[i][z] + (sigma / g_t[i])));
        }
    }
}

void ic_pso::calculaFth(double snir_target)
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            if(snir[i][j] > snir_target)
            {
                fth[i][j] = 1.00F;
            }
            else
            {
                fth[i][j] = 0.00F;
            }
        }
    }
}

void ic_pso::fitness(double pmax)
{
    int i,j;
    double** aux1 = NULL;
    double* aux2 = NULL;
    aux1 = memoria.allocaMatrizD(incognitas,particulas);
    aux2 = memoria.allocaVetorD(particulas);
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            aux1[i][j] = (fth[i][j] * (1.00 - (posicao[i][j] / pmax)));
        }
    }
    for(i = 0; i < particulas; i ++)
    {
        aux2[i] = 0.00;
    }
    for(i = 0; i < particulas; i ++)
    {
        for(j = 0; j < incognitas; j ++)
        {
            aux2[i] = aux2[i] + aux1[j][i];
        }
    }
    for(i = 0; i < particulas; i ++)
    {
        jP[i] = (1.00 / incognitas) * aux2[i];
    }
    aux1 = memoria.liberaMatrizD(aux1,incognitas);
    aux2 = memoria.liberaVetorD(aux2);
}

void ic_pso::insertionSort(double* jP, double * MaxJ, int* idx, int M)
{
    int i,j;
    double chave;
    double * original = NULL;
    original = memoria.allocaVetorD(M);
    for(i = 0; i < M; i ++)
    {
        MaxJ [i] = original[i] = jP[i];
    }
    for(j = 1; j < M; j ++)
    {
        chave = MaxJ[j];
        i  = j - 1;
        while((i > -1) && (MaxJ[i] > chave))
        {
            MaxJ[i + 1] = MaxJ[i];
            i = i - 1;
        }
        MaxJ[i + 1] = chave;
    }
    for(i = 0; i < M; i ++)
    {
        j = 0;
        while(MaxJ[i] != original[j])
        {
            j ++;
        }
        original[j] = -1;
        idx[i] = j;
    }
}
void ic_pso::bestLocal()
{
    int i,j;
    for(i = 0; i < particulas; i ++)
    {
        if(jP[i] > jPibest[i])
        {
            for(j = 0; j < incognitas; j ++)
            {
                pibest[j][i] = posicao[j][i];
            }
            jPibest[i] = jP[i];
        }
    }
}

void ic_pso::bestGlobal()
{
    int i;
    double* MaxJ = NULL;
    int * idx = NULL;
    MaxJ = memoria.allocaVetorD(particulas);
    idx = memoria.allocaVetorI(particulas);
    insertionSort(jP,MaxJ,idx,particulas);
    if(MaxJ[particulas - 1] > jPgbest)
    {
        jPgbest = MaxJ[particulas - 1];
        for(i = 0; i < incognitas; i ++)
        {
            pgbest[i] = posicao[i][idx[particulas - 1]];
        }
    }
    MaxJ = memoria.liberaVetorD(MaxJ);
    idx = memoria.liberaVetorI(idx);
}

double** ic_pso::randomica(double** matriz)
{
    int i,j;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            matriz[i][j] = ((double)(rand())) /RAND_MAX;
        }
    }
    return matriz;
}


void ic_pso::speed()
{
    int i,j;
    //double aux = 0.00;
    double** rand1 = NULL;
    double** rand2 = NULL;
    rand1 = memoria.allocaMatrizD(incognitas,particulas);
    rand2 = memoria.allocaMatrizD(incognitas,particulas);
    rand1 = randomica(rand1);
    rand2 = randomica(rand2);
    imprimir print;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            //aux = (((double)(rand()))/RAND_MAX)/2.00;
            //w = 0.5 + aux;
            velocidade[i][j] = w * velocidade[i][j] + c1 * rand1[i][j]*(pibest[i][j] - posicao[i][j]) +  c2 * rand2[i][j]*(pgbest[i] - posicao[i][j]);
            //w = 0.00;
        }
    }
    rand1 = memoria.liberaMatrizD(rand1, incognitas);
    rand2 = memoria.liberaMatrizD(rand2, incognitas);
}
void ic_pso::speedBounds(double vmin, double vmax)
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            if(velocidade[i][j] > vmax)
            {
                velocidade[i][j] = vmax;
            }
            else if(velocidade[i][j] < vmin)
            {
                velocidade[i][j] = vmin;
            }
        }
    }
}
void ic_pso::populationUpdate()
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            posicao[i][j] += velocidade[i][j];
        }
    }
}
void ic_pso::powerBounds(double pmin, double pmax)
{
    int i,j;
    for(i = 0; i < incognitas; i ++)
    {
        for(j = 0; j < particulas; j ++)
        {
            if(posicao[i][j] < pmin)
            {
                posicao[i][j] = pmin;
            }
            else if(posicao[i][j] > pmax)
            {
                posicao[i][j] = pmax;
            }
        }
    }
}
