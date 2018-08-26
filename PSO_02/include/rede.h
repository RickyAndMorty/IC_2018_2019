#ifndef REDE_H
#define REDE_H
#include "alloca.h"

class rede
{
    protected:

    private:
    double** h, * g_t, *ltx, a_star, alfa, sigma, pmax, pmim;
    double vmax, vmin, snir_target, rc, rb, gamp;
    int usuarios;
    alloca memoria;
    public:
        rede();
    void setH(int linhas, int colunas);
    void setG_t(int colunas);
    void setLtx(int colunas);
    void setA_star(double a_star);
    void setAlfa(double alfa);
    void setGamp(double gamp);
    void setSigma(double sigma);
    void setPmax(double pmax);
    void setPmin(double pmin);
    void setVmax(double vmax);
    void setVmin(double vmin);
    void setSnirTarget(double snir_target);
    void setRc(double rc);
    void setRb(double rb);
    void setUsuarios(int usuarios);
    double** getH();
    double* getG_t();
    double* getLtx();
    double getA_star();
    double getAlfa();
    double getGamp();
    double getSigma();
    double getPmax();
    double getPmin();
    double getVmax();
    double getVmin();
    double getSnirTarget();
    double getRc();
    double getRb();
    int getUsuarios();

    void calculaH(double** h);
    void setDistancia(double* ltx);
    void calculaG_t();
    void calculaH();
    virtual ~rede();


};

#endif // REDE_H
