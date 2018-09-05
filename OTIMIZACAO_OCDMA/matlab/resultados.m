
close all
clear all
K=64;
particulas = 66;
ws = 60E-19; 
c1 = 1.6; 
c2 = 1.6;
q = 256;
iteracoes = 1800;
Nst = 1 : iteracoes;
SIR_max_dB=20;
SIR_max=10^(SIR_max_dB/10);
sigma_cc2=1e-2;
CIR_target=SIR_max*(sigma_cc2/q^2);
%CIR_target=SIR_max*(200e9/10e9)
SNR_target = CIR_target;
%Power Bounds
Pmax=1e-3; %[W]
% Pmax=2*((K/5).^2)*1E-3; %[W]
Pmin=0;
%Pmin = 1E-6;
%User Class definition
n_class = 3;

Uclass(1:8)=1;
Uclass(9:16)=2;
Uclass(16:24)=1;
Uclass(24:32)=2;
Uclass(32:40)=1;
Uclass(40:48)=2;
Uclass(48:56)=1;
Uclass(56:64)=2;

Rc = 10e9;
%Target Rate for Each Class
%Rmin =[1/256  1/64  1/16]*Rc;
%Rmin =[1/10    1]*Rc;
Rmin =[1  1  1]*Rc;
%BER_target = [1E-9  5E-11];
BER_target = [5E-10 5E-10 5E-10];
tetaBER_Class = -1.5./log(5.*BER_target); % Eq. 7
SNIRminClass=-(2/3)*log(5*BER_target).*(2^2-1);
%Calculation CIR_target
%Uclass = repmat(1,K,1);10,9
[idx]=find(Uclass==1);


for k=1:n_class
    %Rate Constraint for Foschini
    [idx]=find(Uclass==k);
    Rmin_class(idx) = Rmin(k);
    CIR_target(idx) =  repmat(Rmin(k)  * (SNR_target/Rc), 1, length(idx) );
    Pmin_class(idx) = repmat(Rmin(k) * (Pmin / Rc),1,length(idx));
    tetaBER(idx) = tetaBER_Class(k);
    SNIRmin(idx) = SNIRminClass(k);
    F(idx) = Rc ./ Rmin(k);
end

%  average noise power of the receiver
rmin=2;
rmax=50;
%Ltx_i=unifrnd(rmin, rmax, 1,K);%comprimento das fibras tx
Ltx_i= [48.8779
    26.9518
    40.0057
    46.3947
    18.7903
    22.8634
    37.3182
    5.2198
    32.6824
    48.5307
    10.2101
    40.0123
    14.8661
    26.3720
    46.7481
    29.7142
    28.8779
    36.9518
    30.0057
    16.3947
    8.7903
    32.8634
    27.3182
    4.2198
    12.6824
    28.5307
    40.2101
    30.0123
    34.8661
    26.3720
    26.7481
    19.7142
    27.3182
    5.2198
    6.6824
    7.5307
    20.2101
    8.0123
    9.8661
    12.3720
    11.7481
    13.7142
    7.3182
    13.2198
    12.6824
    38.5307
    48.2101
    36.0123
    4.8661
    6.3720
    27.7481
    15.7142
    24.3182
    41.2198
    14.6824
    8.5307
    10.2101
    20.0123
    30.8661
    6.3720
    46.7481
    29.7142
    36.7481;
     39.7142]';

%Lrx_i=unifrnd(rmin, rmax, 1, K);%comprimento das fibras rx
Lrx_i=[32.0586
    4.8504
   45.3027
   43.6605
   36.0278
   48.6326
   19.1923
   25.9573
   29.8555
   20.4597
    8.1063
   11.6794
   40.0223
    8.0725
   42.6961
   27.2251]';
BT=1;
Gamp=BT.*100;
Ni=BT.*2.*(Gamp-1).*(193e12).*(100e9).*6.63e-34;
Pn=Ni;
% Fiber optic
%F = ones(1,K);
%F = [1 1 1 1 1 1 1 1 ];
% Fixed stop criterion
It=100;
% ----- Partitioned Optical Power Control ----
% random node position in the range [rmin rmax]
lt=length(Ltx_i);
lr=length(Lrx_i);
%.... transmitting-node fiber attenuation plus star coupler loss....
gama_dB=0.2;  %rela��o de perda excessiva [dB]
%gama_dB=0.4;  %rela��o de perda excessiva [dB]
gama = 10^(gama_dB/10);
a_star_dB=10*log10(K) - ( log2(K)  * gama_dB);
a_star = 10^(-28/10);
%...............................................
a_fiber_dB = 0.2; %dB/Km
a_fiber = 10^(a_fiber_dB/10);  %1/Km
%essa � a equa��o do alfa
alfa=a_fiber_dB/(10*log10(exp(1)));
%...................................................
g_t = a_star.* exp(-alfa.*Ltx_i).*Gamp.*0.0025;
%....................................................
% ...... receiving-node fiber attenuation
g_r = exp(-alfa*Lrx_i);
%....................................................
% interference matrix
H =  repmat(g_t, K,1)./repmat(g_t',1,K) - eye(K);
H_dB = 10*log10(H);

G = eye(K) + H;% G � usada no PSO
Gii = g_t;


% ......Optimal Power Control Problem ..........
%By B matrix inversion
u = Pn  * (CIR_target ./ Gii)';  %  (Pmin./Gii)' % = SNR_min*Pn
B = repmat(CIR_target',1,K) .* (G - eye(K));
Eig_B=eig(B);
%VER COM O PROFESSOR O QUE EST� ACONTECENDO AQUI.
if(max(Eig_B) >= 1)
    disp('Unfeasable Problem');
    disp('Try other Interference Matrix');
    return
else
    Popt=inv(eye(K)-B)*u; %esta � a equa��o (12) do artigo de
    %                  power control do Tarhuni 2005, utilizado como base
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Aqui o c�digo come�a a carregar os resultados dos arquivos.txt
% arquivo = fopen('C:/Users/Ricardo Santos/Desktop/PSO_double/resultados/P.txt');
% % A = fscanf(arquivo,'%f',[colunas linhas]);
% P = fscanf(arquivo,'%f',[particulas K]);
% fclose(arquivo);
% clear arquivo

arquivo = fopen('C:/git/IC_2018_2019/OTIMIZACAO_OCDMA/resultados/SNIRdB.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
SNIRdb = fscanf(arquivo,'%f');
fclose(arquivo);
clear arquivo

% arquivo = fopen('C:/git/IC_2018_2019/resultados/jPgbest.bin');
% % A = fscanf(arquivo,'%f',[colunas linhas]);
% jPgbest = fscanf(arquivo,'%f');
% fclose(arquivo);
% clear arquivo ans


arquivo = fopen('C:/git/IC_2018_2019/OTIMIZACAO_OCDMA/resultados/SNIR.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
sniraux = fscanf(arquivo,'%f',[K iteracoes]);
fclose(arquivo);
clear arquivo ans



arquivo = fopen('C:/git/IC_2018_2019/OTIMIZACAO_OCDMA/resultados/Pgbest.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
bestaux = fscanf(arquivo,'%f',[K iteracoes]);
fclose(arquivo);
clear arquivo ans

figure(1)
%subplot(3,1,1);
semilogy(Nst,bestaux(1,:)')
hold on
semilogy(Nst,bestaux')
semilogy(Nst,repmat(Popt,1,iteracoes),'k--')
Nstt=transpose(bestaux');
save power_pso Nstt -ASCII
Nstt=transpose(repmat(Popt,1,iteracoes));
save power_pso_op Nstt -ASCII
%xlabel('Itera��es')
ylabel('P(W)')
%title(['Allocated Power, K = ',num2str(K,3),', Swarm Population, M = ',num2str(particulas,5),' particles  ', '\phi_1 = ',num2str(c1),'  \phi_2 = ',num2str(c2)])

figure(2)
%subplot(3,1,2); 
plot(Nst,sum(repmat(Popt,1,iteracoes))./sum(bestaux),'LineWidth',2)
Nstt=transpose(sum(repmat(Popt,1,iteracoes))./sum(bestaux));
%legend('Taxa de converg�ncia pelo n�mero de itera��es')
%xlabel('Itera��es')
ylabel('Fitness')
save conver Nstt -ASCII


figure(3)
%subplot(3,1,3); 
plot(10*log10((q^2/sigma_cc2).*sniraux'))
hold on
%plot(10*log10((q^2/sigma_cc2).*sniraux)-7)
%plot(repmat(10*log10((sigma_cc2).*SNR_target),1,iteracoes),'k--','LineWidth',2.5)
xlabel('Itera��es')
ylabel('SNIR (dB)')

figure(4)
arquivo = fopen('C:/git/IC_2018_2019/OTIMIZACAO_OCDMA/resultados/power.bin');
power = fscanf(arquivo,'%f',[1 iteracoes]);
semilogy(Nst,repmat(sum(Popt),1,iteracoes),'k--')
hold on
plot(1:iteracoes,power)
fclose(arquivo);
clear arquivo




