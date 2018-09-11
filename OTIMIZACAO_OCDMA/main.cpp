#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <rede.h>
#include <pso.h>
#include <imprimir.h>
#include <resultados.h>
#include <math.h>
#include <time.h>
#include "randomica.c"

using namespace std;
// Fun��o que converte pot�ncia em dB
void  calculaSNR(double* snr, double** snir, int k, int m)
{
    int i;
    for(i = 0; i < k; i ++)
    {
        snr[i] = 10.00F * (logf(snir[i][m-1] * ((256*256) /0.0100 )) / logf(10.00F));
    }

}
// Fun��o que insere as dist�ncias do acoplador em estrela at� os clientes (ONUs)
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
int verificaSNIR(double* snir, int users)
{
    int i;
    for(i = 0; i < users; i ++)
    {
        if((snir[i] < 20.00) || (snir[i] > 21.00))
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    double Ltx[64];// Vetor de dist�cias entre acoplador estrela e ONUs
    double _snir[64];
    distancia(Ltx);
    int particulas = 66;// Quantidade de part�culas do PSO

    rede ocdma;// Objeto do tipo rede OCDMA
    pso enxame;// Objeto do tipo pso, que representa as caracter�sticas do algoritmo
    imprimir print;
    resultados resultado; // Objeto que guardar� as itera��es do algoritmo
    ocdma.setUsuarios(64);// Configura a rede com 64 usu�rios

    cout << "Usuarios: " << " " << ocdma.getUsuarios() << endl;
    ocdma.setGamp(100.00);// Configura os ganhos do amplificador
    cout << "Gamp: " << " " << ocdma.getGamp() << endl;
    ocdma.setA_star(0.0016);//Configura as perdas do acoplador em estrela
    cout << "A_star: " << " " << ocdma.getA_star() << endl;
    ocdma.setAlfa(0.0416);//Configura a perda por propaga��o na fibra
    cout << "Alfa: " << " " << ocdma.getAlfa() << endl;
    ocdma.setPmax(0.0100);// Configura a pot�ncia m�nima de transmiss�o
    cout << "Pmax: " << " " << ocdma.getPmax() << endl;
    ocdma.setPmin(pow(10.00,-10.00));//Configura a pot�ncia m�xima de transmiss�o
    cout << "Pmin: " << " " << ocdma.getPmin() << endl;
    ocdma.setVmax(0.0020);// Configura a velociade m�xima das part�culas do PSO
    cout << "Vmax: " << " " << ocdma.getVmax() << endl;
    ocdma.setVmin(-0.0020);// Configura a velocidade m�n�ma das part�culas do PSO
    cout << "Vmin: " << " " << ocdma.getVmin() << endl;
    ocdma.setSnirTarget(1.5259*pow(10.00,-5.00));//Configura a rela��o sinal-ru�do target
    cout << "SnirTarget: " << " " << ocdma.getSnirTarget() << endl;
    // Calcula a interfer�ncia
    ocdma.setSigma(2 * (ocdma.getGamp() - 1.00) * 193.0 * pow(10.00,12.00) * 100.00 * pow(10.00,9.00) * 6.63 * pow(10.00,-34.00));// Configura a interfer�ncia
    cout << "Sigma: " << " " << ocdma.getSigma() << endl;

    ocdma.setLtx(ocdma.getUsuarios());// Aloca o vetor das dist�ncias do acoplador estrela, em fun��o do n�mero de usu�rios da rede

    ocdma.setDistancia(Ltx);// Atribui uma dist�ncia para cada posi��o do vetor de dist�ncias




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

/*****************************AQUI COME�A OS M�TODOS DO PSO********************************************************/
    time_t t;
	srand((unsigned) time(&t));

    enxame.setC1(constante1());//Configura a constante de acelera��o local
    enxame.setC2(constante2());//Configura a constante de acelera��o global
    //enxame.setW(0.812214);
    enxame.setJPgbest(0.00);//
    enxame.setIteracoes(1800);// Configura o n�mero de itera��oes
    enxame.setIncognitas(ocdma.getUsuarios());// Configura o n�mero de inc�nitas do PSO
    enxame.setParticulas(particulas);// Configura o n�mero de part�culas do PSO

    enxame.setSnir(ocdma.getUsuarios(), particulas);// Configura o espa�o do busca do PSO

    enxame.setPosicao(ocdma.getUsuarios(), particulas);// Configura a posi��o das part�culas

    enxame.setG(ocdma.getUsuarios(),ocdma.getUsuarios());//Aloca a matriz G

    enxame.setFth(ocdma.getUsuarios(), particulas);//Aloca a matriz Fth

    enxame.setVelocidade(ocdma.getUsuarios(), particulas);// Configura a matriz de velocidades do PSO

    enxame.setPibest(ocdma.getUsuarios(), particulas);// Configura a matriz dos melhores locais do PSO

    enxame.setGii(ocdma.getUsuarios());//Aloca o vetor Gii

    enxame.setF(ocdma.getUsuarios());//Aloca o vetor F

    enxame.setPgbest(ocdma.getUsuarios());// Aloca o vetor Pgbest

    enxame.setJp(particulas);//Aloca o vetor Jp

    enxame.setJPibest(particulas);//Aloca o vetor JPibest
    //cout << "Particulas" << " " << enxame.getParticulas() << endl;

    resultado.setSnir(enxame.getIteracoes(),ocdma.getUsuarios());//Aloca a matriz auxiliar SNIR
    resultado.setUsers(ocdma.getUsuarios());//seta a quantidade de usu�rios da rede, no objeto auxiliar
    resultado.setPgbest(enxame.getIteracoes(),ocdma.getUsuarios());//Aloca a matriz Pgbest, auxiliar

    resultado.setPower(enxame.getIteracoes());//Vetor que guarda a pot�ncia m�dia consumida em cada itera��o



    enxame.calculaPosicao();//M�todo que calcula a posi��o das particulas
    enxame.calculaPibest();// Metodo que calcula a melhor posi��o local de cada particula
    enxame.calculaPgbest();//Metodo que calcula a melhor posi��o global de cada particula
    enxame.calculaG(ocdma.getH());
    enxame.calculaSnir(ocdma.getSigma(),ocdma.getG_t());//Metodo que calcula a SNIR
    enxame.calculaFth(ocdma.getSnirTarget());// Metodo que verifica a evolu��o do exame de part�culas
    enxame.fitness(ocdma.getPmax());//Metodo que calcula a fun��o fitness
    /************Aqui come�a as itera��es do algoritmo PSO*************************/
    for(int i = 0; i < enxame.getIteracoes(); i ++)// La�o que ser� executado em fun��o do n�mero de itera��es
    {
        enxame.calculaSnir(ocdma.getSigma(),ocdma.getG_t());//Metodo que calcula a SNIR
        enxame.calculaFth(ocdma.getSnirTarget());// Metodo que verifica a evolu��o do exame de part�culas
        enxame.fitness(ocdma.getPmax());//Metodo que calcula a fun��o fitness
        enxame.bestLocal();// M�todo que calcula a melhor posi��o local
        enxame.bestGlobal();//M�todo que calcula a melhor posi��o global
        enxame.speed();//M�todo que calcula a velocidade das part�culas (equa��o principal do pso)
        enxame.speedBounds(ocdma.getVmin(), ocdma.getVmax());// M�todo que limita a velocidade de cada particula do pso
        enxame.populationUpdate();//M�todo que atualiza a posi��o das particulas do pso
        enxame.powerBounds(ocdma.getPmin(),ocdma.getPmax());//M�todo que limita a posi��o de cada particula do pso no espa�o de busca
        resultado.salvarSNIR(enxame.getPgbest(),enxame.getG(),ocdma.getG_t(),ocdma.getSigma(),i,ocdma.getUsuarios());//M�todo que salva o resultado da SNIR em cada itera��o
        resultado.salvarPgbest(enxame.getPgbest(),i);// M�todo que salva a posi��o global das particulas em cada itera��o

        resultado.salvarPower(enxame.getPgbest(),i,ocdma.getUsuarios());//M�todo que salva a pot�ncia m�dia consumida em cada itera��o
        cout << "i = " << " " << i << endl;
    }


    resultado.gravarSnir(resultado.getSnir(),enxame.getIteracoes(),ocdma.getUsuarios());//M�todo que grava a SNIR em um arquivo.txt ou arquivo.bin
    resultado.gravarPgbest(resultado.getPgbest(),enxame.getIteracoes());//M�todo que grava a matriz Pgbest em um arquivo.txt ou arquivo.bin
    calculaSNR(_snir,enxame.getSnir(),ocdma.getUsuarios(),enxame.getParticulas());//M�todo que transforma a snir em dB
    cout << "Posicao" << " " << endl;
    print.imprimir1DD(_snir,ocdma.getUsuarios());

    resultado.gravarSnirdB(_snir,ocdma.getUsuarios());//M�todo para gravar a snir em dB

    resultado.gravarPower(resultado.getPower(),enxame.getIteracoes());// M�todo para gravar a pot�ncia m�dia consumida pelas ONUs

    resultado.gravarConstantes(enxame.getC1(),enxame.getC2(),enxame.getW());// Metodo para gravar as constantes encontradas
    cout << "Constantes"  << endl;

    cout << verificaSNIR(_snir,ocdma.getUsuarios()) << endl;
    cout << enxame.getC1()  << endl;
    cout << enxame.getC2()  << endl;
    return 0;
}
