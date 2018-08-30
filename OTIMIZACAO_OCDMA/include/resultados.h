#ifndef RESULTADOS_H
#define RESULTADOS_H
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>


class resultados
{
    private:
        int users;
        double** snir, ** pgbest;
        alloca memoria;
    public:
    void setUsers(int _users);
    void setSnir(int iterations, int users);
    void setPgbest(int linhas, int colunas);

    double** getSnir();
    double** getPgbest();

    void gravarSnir(double** matriz, int linhas, int colunas);
    void salvarSNIR(double* pgbest, double** G, double* g_t, double sigma,int iteration, int users);
    void salvarPgbest(double* _pgbest, int z);

    resultados();
    virtual ~resultados();

    protected:


};

#endif // RESULTADOS_H
