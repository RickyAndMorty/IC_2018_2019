#ifndef PSO_H
#define PSO_H
#include "alloca.h"

class pso
{
    private:
        double** snir,** posicao, ** G, ** velocidade, ** pibest, ** fth;
        double *Gii, * F, * jP, *pgbest, * jPibest;
        double jPgbest,c1,c2,w;
        int incognitas, particulas, iteracoes;
        alloca memoria;
    public:
        pso();
        /***************SETs***********************/
        void setSnir(int linhas, int colunas);
        void setPosicao(int linhas, int colunas);
        void setVelocidade(int linhas, int colunas);
        void setG(int linhas, int colunas);
        void setPibest(int linhas, int colunas);
        void setFth(int linhas, int colunas);
        void setGii(int colunas);
        void setF(int colunas);
        void setJp(int colunas);
        void setPgbest(int colunas);
        void setJPibest(int colunas);
        void setJPgbest(double _jPgbest);
        void setC1(double _c1);
        void setC2(double _c2);
        void setW(double _w);
        void setParticulas(int _particulas);
        void setIncognitas(int _incognitas);
        void setIteracoes(int _iteracoes);
        /***************GETs***********************/
        double** getSnir();
        double** getPosicao();
        double** getVelocidade();
        double** getG();
        double** getPibest();
        double** getFth();
        double* getGii();
        double* getF();
        double* getJp();
        double* getPgbest();
        double* getJPibest();
        double getJPgbest();
        double getC1();
        double getC2();
        double getW();
        int getParticulas();
        int getIncognitas();
        int getIteracoes();
        virtual ~pso();
/*****************************MÉTODOS DO PSO******************************************************/
        void calculaPosicao();
        void calculaPibest();
        void calculaPgbest();
        void calculaG(double** h);
        void calculaSnir(double sigma, double* g_t);
        void calculaFth(double snir_target);
        void fitness(double pmax);
        void insertionSort(double* jP, double * MaxJ, int* idx, int M);
        double** randomica(double** matriz);
        double constantes();

        void bestLocal();
        void bestGlobal();
        void speed(int atual);

        void speedBounds(double vmin, double vmax);
        void populationUpdate();
        void powerBounds(double pmin, double pmax);

    protected:


};

#endif // PSO_H
