#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <rede.h>
#include <pso.h>
#include <imprimir.h>
#include <resultados.h>
#include <math.h>

using namespace std;
// Função que converte potência em dB
void  calculaSNR(double* snr, double** snir, int k, int m)
{
    int i;
    for(i = 0; i < k; i ++)
    {
        snr[i] = 10.00F * (logf(snir[i][m-1] * ((256*256) /0.0100 )) / logf(10.00F));
    }

}
// Função que insere as distâncias do acoplador em estrela até os clientes (ONUs)
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
    Ltx_i[32] = 27.3182;
    Ltx_i[33] = 5.2198;
    Ltx_i[34] = 6.6824;
    Ltx_i[35] = 7.5307;
    Ltx_i[36] = 20.2101;
    Ltx_i[37] = 8.0123;
    Ltx_i[38] = 9.8661;
    Ltx_i[39] = 12.3720;
    Ltx_i[40] = 11.7481;
    Ltx_i[41] = 13.7142;
    Ltx_i[42] = 7.3182;
    Ltx_i[43] = 13.2198;
    Ltx_i[44] = 12.6824;
    Ltx_i[45] = 38.5307;
    Ltx_i[46] = 48.2101;
    Ltx_i[47] = 36.0123;
    Ltx_i[48] = 4.8661;
    Ltx_i[49] = 6.3720;
    Ltx_i[50] = 27.7481;
    Ltx_i[51] = 15.7142;
    Ltx_i[52] = 24.3182;
    Ltx_i[53] = 41.2198;
    Ltx_i[54] = 14.6824;
    Ltx_i[55] = 8.5307;
    Ltx_i[56] = 10.2101;
    Ltx_i[57] = 20.0123;
    Ltx_i[58] = 30.8661;
    Ltx_i[59] = 6.3720;
    Ltx_i[60] = 46.7481;
    Ltx_i[61] = 29.7142;
    Ltx_i[62] = 36.7481;
    Ltx_i[63] = 39.7142;
}
int main()
{
    double Ltx[64];// Vetor de distâcias entre acoplador estrela e ONUs
    double _snir[64];
    distancia(Ltx);
    int particulas = 66;// Quantidade de partículas do PSO

    rede ocdma;// Objeto do tipo rede OCDMA
    pso enxame;// Objeto do tipo pso, que representa as características do algoritmo
    imprimir print;
    resultados resultado;
    ocdma.setUsuarios(64);// Configura a rede com 64 usuários

    cout << "Usuarios: " << " " << ocdma.getUsuarios() << endl;
    ocdma.setGamp(100.00);// Configura os ganhos do amplificador
    cout << "Gamp: " << " " << ocdma.getGamp() << endl;
    ocdma.setA_star(0.0016);//
    cout << "A_star: " << " " << ocdma.getA_star() << endl;
    ocdma.setAlfa(0.0416);
    cout << "Alfa: " << " " << ocdma.getAlfa() << endl;
    ocdma.setPmax(0.0100);// Configura a potência mínima de transmissão
    cout << "Pmax: " << " " << ocdma.getPmax() << endl;
    ocdma.setPmin(pow(10.00,-10.00));//Configura a potência máxima de transmissão
    cout << "Pmin: " << " " << ocdma.getPmin() << endl;
    ocdma.setVmax(0.0020);// Configura a velociade máxima das partículas do PSO
    cout << "Vmax: " << " " << ocdma.getVmax() << endl;
    ocdma.setVmin(-0.0020);// Configura a velocidade míníma das partículas do PSO
    cout << "Vmin: " << " " << ocdma.getVmin() << endl;
    ocdma.setSnirTarget(1.5259*pow(10.00,-5.00));//Configura a relação sinal-ruído target
    cout << "SnirTarget: " << " " << ocdma.getSnirTarget() << endl;
    // Interferência
    ocdma.setSigma(2 * (ocdma.getGamp() - 1.00) * 193.0 * pow(10.00,12.00) * 100.00 * pow(10.00,9.00) * 6.63 * pow(10.00,-34.00));// Configura a interferência
    cout << "Sigma: " << " " << ocdma.getSigma() << endl;

    ocdma.setLtx(ocdma.getUsuarios());// Aloca o vetor das distâncias do acoplador estrela, em função do número de usuários da rede

    ocdma.setDistancia(Ltx);// Atribui uma distância para cada posição do vetor de distâncias




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

    enxame.setC1(1.526200);//Configura a constante de aceleração local
    enxame.setC2(1.732994);//Configura a constante de aceleração global
    //enxame.setW(0.812214);
    enxame.setJPgbest(0.00);//
    enxame.setIteracoes(2000);// Configura o número de iteraçãoes
    enxame.setIncognitas(ocdma.getUsuarios());// Configura o número de incónitas do PSO
    enxame.setParticulas(particulas);// Configura o número de partículas do PSO

    enxame.setSnir(ocdma.getUsuarios(), particulas);// Configura o espaço do busca do PSO

    enxame.setPosicao(ocdma.getUsuarios(), particulas);// Configura a posição das partículas

    enxame.setG(ocdma.getUsuarios(),ocdma.getUsuarios());

    enxame.setFth(ocdma.getUsuarios(), particulas);//

    enxame.setVelocidade(ocdma.getUsuarios(), particulas);// Configura a matriz de velocidades do PSO

    enxame.setPibest(ocdma.getUsuarios(), particulas);// Configura a matriz dos melhores locais do PSO

    enxame.setGii(ocdma.getUsuarios());

    enxame.setF(ocdma.getUsuarios());

    enxame.setPgbest(ocdma.getUsuarios());// Configura os melhores globais do PSO

    enxame.setJp(particulas);

    enxame.setJPibest(particulas);
    //cout << "Particulas" << " " << enxame.getParticulas() << endl;

    resultado.setSnir(enxame.getIteracoes(),ocdma.getUsuarios());// Objeto que guardará as iterações do algoritmo
    resultado.setUsers(ocdma.getUsuarios());
    resultado.setPgbest(enxame.getIteracoes(),ocdma.getUsuarios());

    resultado.setPower(enxame.getIteracoes());



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
        resultado.salvarSNIR(enxame.getPgbest(),enxame.getG(),ocdma.getG_t(),ocdma.getSigma(),i,ocdma.getUsuarios());
        resultado.salvarPgbest(enxame.getPgbest(),i);

        resultado.salvarPower(enxame.getPgbest(),i,ocdma.getUsuarios());
        cout << "i = " << " " << i << endl;
    }
    resultado.gravarSnir(resultado.getSnir(),enxame.getIteracoes(),ocdma.getUsuarios());
    resultado.gravarPgbest(resultado.getPgbest(),enxame.getIteracoes());
    calculaSNR(_snir,enxame.getSnir(),ocdma.getUsuarios(),enxame.getParticulas());
    cout << "Posicao" << " " << endl;
    print.imprimir1DD(_snir,ocdma.getUsuarios());

    resultado.gravarSnirdB(_snir,ocdma.getUsuarios());

    resultado.gravarPower(resultado.getPower(),enxame.getIteracoes());

    return 0;
}
