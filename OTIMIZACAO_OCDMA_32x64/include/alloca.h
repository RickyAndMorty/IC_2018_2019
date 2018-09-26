#ifndef ALLOCA_H
#define ALLOCA_H


class alloca
{
    public:
        alloca();
        double** allocaMatrizD(int linhas,int colunas);
        double* allocaVetorD(int colunas);
        int** allocaMatrizI(int linhas,int colunas);
        int* allocaVetorI(int colunas);
        double** liberaMatrizD(double** matriz, int linhas);
        double* liberaVetorD(double* vetor);
        int** liberaMatrizI(int** matriz, int linhas);
        int* liberaVetorI(int* vetor);
        virtual ~alloca();

    protected:

    private:
};

#endif // ALLOCA_H
