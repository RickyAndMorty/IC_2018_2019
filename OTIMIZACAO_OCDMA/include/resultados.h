#ifndef RESULTADOS_H
#define RESULTADOS_H
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>


class resultados
{
    private:
        int users;
        double** snir, ** pgbest, *power;
        alloca memoria;
    public:
    void setUsers(int _users);
    void setSnir(int iterations, int users);
    void setPgbest(int linhas, int colunas);
    void setPower(int iterations);

    double** getSnir();
    double** getPgbest();
    double* getPower();
    void salvarSNIR(double* pgbest, double** G, double* g_t, double sigma,int iteration, int users);
    void salvarPgbest(double* _pgbest, int z);

    void salvarPower(double* pgbest,int iteration, int users);
    void gravarPower(double* _power, int users);

    void gravarSnir(double** matriz, int linhas, int colunas);

    void gravarPgbest(double** pgbest, int iterations);
    void gravarSnirdB(double* _snir, int users);
    void gravarConstantes(double c1,double c2, double w);

    resultados();
    virtual ~resultados();

    protected:


};

#endif // RESULTADOS_H
