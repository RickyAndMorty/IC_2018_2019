#include "pso.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <imprimir.h>
pso::pso()
{
    //ctor
}

pso::~pso()
{
    //dtor
}
/*****************sets do PSO************************/
void pso::setSnir(int linhas, int colunas)
{
    snir = memoria.allocaMatrizD(linhas,colunas);

}
void pso::setPosicao(int linhas, int colunas)
{
    posicao = memoria.allocaMatrizD(linhas,colunas);
}
void pso::setVelocidade(int linhas, int colunas)
{
    velocidade = memoria.allocaMatrizD(linhas,colunas);
}
void pso::setG(int linhas, int colunas)
{
    G = memoria.allocaMatrizD(linhas,colunas);
}
void pso::setPibest(int linhas, int colunas)
{
    pibest = memoria.allocaMatrizD(linhas,colunas);
}
void pso::setFth(int linhas, int colunas)
{
    fth = memoria.allocaMatrizD(linhas,colunas);
}
void pso::setGii(int colunas)
{
    Gii = memoria.allocaVetorD(colunas);
}
void pso::setF(int colunas)
{
    F = memoria.allocaVetorD(colunas);
}
void pso::setJp(int colunas)
{
    jP = memoria.allocaVetorD(colunas);
}
void pso::setPgbest(int colunas)
{
    pgbest = memoria.allocaVetorD(colunas);
}
void pso::setJPibest(int colunas)
{
    jPibest = memoria.allocaVetorD(colunas);
}
void pso::setJPgbest(double _jPgbest)
{
    jPgbest = _jPgbest;
}
void pso::setC1(double _c1)
{
    c1 = _c1;
}
void pso::setC2(double _c2)
{
    c2 = _c2;
}
void pso::setW(double _w)
{
    w = _w;
}
void pso::setParticulas(int _particulas)
{
    particulas = _particulas;
}
void pso::setIncognitas(int _incognitas)
{
    incognitas = _incognitas;
}
void pso::setIteracoes(int _iteracoes)
{
    iteracoes = _iteracoes;
}
/******************************gets do PSO**************************************************************/
double** pso::getSnir()
{
    return snir;
}
double** pso::getPosicao()
{
    return posicao;
}
double** pso::getVelocidade()
{
    return velocidade;
}
double** pso::getG()
{
    return G;
}
double** pso::getPibest()
{
    return pibest;
}
double** pso::getFth()
{
    return fth;
}
double* pso::getGii()
{
    return Gii;
}
double* pso::getF()
{
    return F;
}
double* pso::getJp()
{
    return jP;
}
double* pso::getPgbest()
{
    return pgbest;
}
double* pso::getJPibest()
{
    return jPibest;
}
double pso::getJPgbest()
{
    return jPgbest;
}
double pso::getC1()
{
    return c1;
}
double pso::getC2()
{
    return c2;
}
double pso::getW()
{
    return w;
}
int pso::getParticulas()
{
    return particulas;
}
int pso::getIncognitas()
{
    return incognitas;
}
int pso::getIteracoes()
{
    return iteracoes;
}


void pso::calculaPosicao()
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
void pso::calculaPibest()
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
void pso::calculaPgbest()
{
    int i;
    for(i = 0; i < incognitas; i ++)
    {
        pgbest[i] = (((double)(rand())) / RAND_MAX) / 100.00F;//pso->Pmax;
    }
}

void pso::calculaG(double** h)
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

void pso::calculaSnir(double sigma, double* g_t)
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

void pso::calculaFth(double snir_target)
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

void pso::fitness(double pmax)
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

void pso::insertionSort(double* jP, double * MaxJ, int* idx, int M)
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
void pso::bestLocal()
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

void pso::bestGlobal()
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

double** pso::randomica(double** matriz)
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


void pso::speed(int atual)
{
    int i,j;
    double aux = 0.00;
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
            aux = (((double)(iteracoes - atual))/iteracoes)*(0.812214 - 0.711203) + 0.711203;
            w = aux;
            velocidade[i][j] = w * velocidade[i][j] + c1 * rand1[i][j]*(pibest[i][j] - posicao[i][j]) +  c2 * rand2[i][j]*(pgbest[i] - posicao[i][j]);
            w = 0.00;
        }
    }
    rand1 = memoria.liberaMatrizD(rand1, incognitas);
    rand2 = memoria.liberaMatrizD(rand2, incognitas);
}
void pso::speedBounds(double vmin, double vmax)
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
void pso::populationUpdate()
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
void pso::powerBounds(double pmin, double pmax)
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

double pso::constantes()
{
    time_t t;
    double constante;
    srand((unsigned) time(&t));
    constante = 1.00 + ((double)(rand()))/RAND_MAX;
    return constante;
}
