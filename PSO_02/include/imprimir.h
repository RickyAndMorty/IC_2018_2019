#ifndef IMPRIMIR_H
#define IMPRIMIR_H


class imprimir
{
    public:
        imprimir();
    void imprimir1DD(double* vetor, int colunas);
    void imprimir2DD(double** matriz, int linhas, int colunas);
    void imprimir1DI(int* vetor, int colunas);
    void imprimir2DI(int** matriz, int linhas, int colunas);
    virtual ~imprimir();


    protected:

    private:
        int i,j;
};

#endif // IMPRIMIR_H
