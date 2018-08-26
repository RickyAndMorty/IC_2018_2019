#include "rede.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

rede::rede()
{
    //ctor
}
rede::~rede()
{
    //dtor
}
void rede::setH(int linhas, int colunas)
{
    h = memoria.allocaMatrizD(linhas,colunas);
}
void rede::setG_t(int colunas)
{
    g_t = memoria.allocaVetorD(colunas);
}
void rede::setLtx(int colunas)
{
    ltx = memoria.allocaVetorD(colunas);
}
void rede::setA_star(const double _a_star)
{
    a_star = _a_star;
}
void rede::setAlfa(double _alfa)
{
    alfa = _alfa;
}
void rede::setGamp(double _gamp)
{
    gamp = _gamp;
}
void rede::setSigma(double _sigma)
{
    sigma = _sigma;
}
void rede::setPmax(double _pmax)
{
    pmax = _pmax;
}
void rede::setPmin(double _pmin)
{
    pmim = _pmin;
}
void rede::setVmax(double _vmax)
{
    vmax = _vmax;
}
void rede::setVmin(double _vmin)
{
    vmin = _vmin;
}
void rede::setSnirTarget(double _snir_target)
{
    snir_target = _snir_target;
}
void rede::setRb(double _rb)
{
    rb = _rb;
}
void rede::setRc(double _rc)
{
    rc = _rc;
}
void rede::setUsuarios(int _usuarios)
{
    usuarios = _usuarios;
}
/*****Metodos gets ******/
double rede::getAlfa()
{
    return alfa;
}
double rede::getA_star()
{
    return a_star;
}
double* rede::getLtx()
{
    return ltx;
}
int rede::getUsuarios()
{
    return usuarios;
}
double rede::getGamp()
{
    return gamp;
}
double* rede::getG_t()
{
    return g_t;
}
double rede::getSigma()
{
    return sigma;
}
double rede::getSnirTarget()
{
    return snir_target;
}
double rede::getVmin()
{
    return vmin;
}
double rede::getVmax()
{
    return vmax;
}
double rede::getPmin()
{
    return pmim;
}
double rede::getPmax()
{
    return pmax;
}
double** rede::getH()
{
    return h;
}


/***********FUNÇÕES DA REDE*******/
void rede::setDistancia(double* ltx)
{
    this->ltx = ltx;
}
void rede::calculaG_t()
{
    int i;
    for(i = 0; i < usuarios; i ++)
    {
        g_t[i] = a_star * pow(2.7183, -alfa * ltx[i]) * gamp * 0.0025;
    }
}
void rede::calculaH()
{
    int i,j;
    double** H1 = NULL;
    double** H2 = NULL;
    H1 = memoria.allocaMatrizD(usuarios,usuarios);
    H2 = memoria.allocaMatrizD(usuarios,usuarios);
    for(i = 0; i < usuarios; i ++)
    {
        for(j = 0; j < usuarios; j ++)
        {
            H1[i][j] = g_t[j];
            H2[j][i] = g_t[j];
        }
    }
    for(i = 0; i < usuarios; i ++)
    {
        for(j = 0; j < usuarios; j ++)
        {
            if(i == j)
            {
                h[i][j] = 0.00F;
            }
            else
            {
                h[i][j] = H1[i][j] / H2[i][j];
            }

        }
    }
    H1 = memoria.liberaMatrizD(H1,usuarios);
    H2 = memoria.liberaMatrizD(H2,usuarios);
}
