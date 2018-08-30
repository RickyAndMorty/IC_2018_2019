#ifndef RESULTADOS_H
#define RESULTADOS_H
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>


class resultados
{
    private:
        double** snir;
        alloca memoria;
    public:
    void salvarSNIR(double* pgbest, double** G, double* g_t, double sigma,int iteration, int users);
    void setSnir(int iterations, int users);
    void gravarMatriz(double** matriz, int linhas, int colunas);
    double** getSnir();

    resultados();
    virtual ~resultados();

    protected:


};

#endif // RESULTADOS_H
