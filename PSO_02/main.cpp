#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <rede.h>
#include <pso.h>
#include <imprimir.h>
#include <math.h>

using namespace std;

void  calculaSNR(double* snr, double** snir, int k, int m)
{
    int i;
    for(i = 0; i < k; i ++)
    {
        snr[i] = 10.00F * (logf(snir[i][m-1] * ((256*256) /0.0100 )) / logf(10.00F));
    }

}

void distancia(double* Ltx_i)
{
    Ltx_i[0] = 48.8779;
    Ltx_i[1] = 26.9518;
    Ltx_i[2] = 40.0057;
    Ltx_i[3] = 46.3947;
    Ltx_i[4] = 18.7903;
    Ltx_i[5] = 22.8634;
    Ltx_i[6] = 37.3182;
    Ltx_i[7] = 5.2198;
    Ltx_i[8] = 32.6824;
    Ltx_i[9] = 48.5307;
    Ltx_i[10] = 10.2101;
    Ltx_i[11] = 40.0123;
    Ltx_i[12] = 14.8661;
    Ltx_i[13] = 26.3720;
    Ltx_i[14] = 46.7481;
    Ltx_i[15] = 29.7142;
    Ltx_i[16] = 28.8779;
    Ltx_i[17] = 36.9518;
    Ltx_i[18] = 30.0057;
    Ltx_i[19] = 16.3947;
    Ltx_i[20] = 8.7903;
    Ltx_i[21] = 32.8634;
    Ltx_i[22] = 27.3182;
    Ltx_i[23] = 4.2198;
    Ltx_i[24] = 12.6824;
    Ltx_i[25] = 28.5307;
    Ltx_i[26] = 40.2101;
    Ltx_i[27] = 30.0123;
    Ltx_i[28] = 34.8661;
    Ltx_i[29] = 26.3720;
    Ltx_i[30] = 26.7481;
    Ltx_i[31] = 19.7142;
}
int main()
{
    double Ltx[32];
    double snr[32];
    distancia(Ltx);

    int particulas = 64;

    rede ocdma;
    pso enxame;
    imprimir print;
    ocdma.setUsuarios(32);
    cout << "Usuarios: " << " " << ocdma.getUsuarios() << endl;
    ocdma.setGamp(100.00);
    cout << "Gamp: " << " " << ocdma.getGamp() << endl;
    ocdma.setA_star(0.0016);
    cout << "A_star: " << " " << ocdma.getA_star() << endl;
    ocdma.setAlfa(0.0416);
    cout << "Alfa: " << " " << ocdma.getAlfa() << endl;
    ocdma.setPmax(0.0100);
    cout << "Pmax: " << " " << ocdma.getPmax() << endl;
    ocdma.setPmin(pow(10.00,-10.00));
    cout << "Pmin: " << " " << ocdma.getPmin() << endl;
    ocdma.setVmax(0.0020);
    cout << "Vmax: " << " " << ocdma.getVmax() << endl;
    ocdma.setVmin(-0.0020);
    cout << "Vmin: " << " " << ocdma.getVmin() << endl;
    ocdma.setSnirTarget(1.5259*pow(10.00,-5.00));
    cout << "SnirTarget: " << " " << ocdma.getSnirTarget() << endl;
    // Interferência
    ocdma.setSigma(2 * (ocdma.getGamp() - 1.00) * 193.0 * pow(10.00,12.00) * 100.00 * pow(10.00,9.00) * 6.63 * pow(10.00,-34.00));
    cout << "Sigma: " << " " << ocdma.getSigma() << endl;

    ocdma.setLtx(ocdma.getUsuarios());

    ocdma.setDistancia(Ltx);




    /*******Imprimindo resultados*******/
    /*cout << "Distancias do acoplador estrela" << endl;
    print.imprimir1DD(ocdma.getLtx(),ocdma.getUsuarios());*/


    ocdma.setG_t(ocdma.getUsuarios());
    ocdma.calculaG_t();
    /*cout << "G_t" << endl;
    print.imprimir1DD(ocdma.getG_t(),ocdma.getUsuarios());*/

    ocdma.setH(ocdma.getUsuarios(),ocdma.getUsuarios());
    ocdma.calculaH();
    /*cout << "Matriz H" << endl;
    print.imprimir2DD(ocdma.getH(),ocdma.getUsuarios(),ocdma.getUsuarios());*/

/*****************************AQUI COMEÇA OS MÉTODOS DO PSO********************************************************/

    enxame.setC1(1.526200);
    enxame.setC2(1.732994);
    enxame.setW(0.812214);
    enxame.setJPgbest(0.00);
    enxame.setIteracoes(1800);
    enxame.setIncognitas(ocdma.getUsuarios());
    enxame.setParticulas(particulas);

    enxame.setSnir(ocdma.getUsuarios(), particulas);

    enxame.setPosicao(ocdma.getUsuarios(), particulas);

    enxame.setG(ocdma.getUsuarios(),ocdma.getUsuarios());
    enxame.setFth(ocdma.getUsuarios(), particulas);

    enxame.setVelocidade(ocdma.getUsuarios(), particulas);

    enxame.setPibest(ocdma.getUsuarios(), particulas);

    enxame.setGii(ocdma.getUsuarios());
    enxame.setF(ocdma.getUsuarios());

    enxame.setPgbest(ocdma.getUsuarios());

    enxame.setJp(particulas);
    enxame.setJPibest(particulas);
    cout << "Particulas" << " " << enxame.getParticulas() << endl;


    enxame.calculaPosicao();
    enxame.calculaPibest();
    enxame.calculaPgbest();
    enxame.calculaG(ocdma.getH());
    enxame.calculaSnir(ocdma.getSigma(),ocdma.getG_t());
    enxame.calculaFth(ocdma.getSnirTarget());
    enxame.fitness(ocdma.getPmax());

    for(int i = 0; i < enxame.getIteracoes(); i ++)
    {
        enxame.calculaSnir(ocdma.getSigma(),ocdma.getG_t());
        enxame.calculaFth(ocdma.getSnirTarget());
        enxame.fitness(ocdma.getPmax());
        enxame.bestLocal();
        enxame.bestGlobal();
        enxame.speed();
        enxame.speedBounds(ocdma.getVmin(), ocdma.getVmax());
        enxame.populationUpdate();
        enxame.powerBounds(ocdma.getPmin(),ocdma.getPmax());
        cout << "i = " << " " << i << endl;
    }
    calculaSNR(snr,enxame.getSnir(),ocdma.getUsuarios(),enxame.getParticulas());
    cout << "Posicao" << " " << endl;
    print.imprimir1DD(snr,ocdma.getUsuarios());

    /*cout << "Posicao" << " " << endl;
    print.imprimir2DD(enxame.getPosicao(),enxame.getIncognitas(),enxame.getParticulas());*/
    return 0;
}
