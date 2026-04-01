#Amplitud: punto vertical maximo o minimo
#Periodo T de la senoide: tiempo entre dos maximos/minimos seguidos
#fs= 1/T
#Tm: long de cada saltito
#phi= -2pi*fs*t1

A=3;
T=0.05;
fs=1/T;
Tm= 0.00125;
t1=5*Tm;
phi=-2*pi*fs*t1;
t=0:Tm:0.1-Tm;
x = A*sin(2*pi*fs*t+phi);
plot(t,x)

