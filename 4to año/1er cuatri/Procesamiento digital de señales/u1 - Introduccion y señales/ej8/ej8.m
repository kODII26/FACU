addpath('../Funciones creadas');

#Genero una senoidal conocida que pueda manejar
fs=1;
fm=50;
phi=pi/4;
t_inicial=0;
t_final=1;

[sen,t]= generar_senoidal(fs,fm,phi,t_inicial,t_final);
#plot(t,sen)
sen= 5*sen; #Aumento la amplitud para que la señal tenga mas potencia

#Genero un ruido aleatorio
ruido= randn(size(sen));

#Sumo señal+ruido
suma_SN= sen+ruido;

#Calculo potencia de ambas señales por separado
pot_S= potencia(sen);
pot_N= potencia(ruido);

#Calculo SNR
ratio= 10*log10(pot_S/pot_N);
printf('Primer SNR: %f\n', ratio)

#Escalo el ruido
ruido2= 2 .* ruido;

#Vuelvo a calcular potencia de ruido
pot_N2= potencia(ruido2);

#Vuelvo a calcular SNR con el nuevo ruido
ratio2= 10*log10(pot_S/pot_N2);
printf('Segundo SNR: %f\n', ratio2)

#Despejo constante para que SNR = 0
#SNR=0 -> Ps=Pr
#Ps=Pr -> Ps= k^2*Pr -> k=sqrt(Ps/Pr)
addpath('../Funciones creadas');

#Genero una senoidal conocida que pueda manejar
fs=1;
fm=50;
phi=pi/4;
t_inicial=0;
t_final=1;

[sen,t]= generar_senoidal(fs,fm,phi,t_inicial,t_final);
#plot(t,sen)
sen= 5*sen; #Aumento la amplitud para que la señal tenga mas potencia

#Genero un ruido aleatorio
ruido= randn(size(sen));

#Sumo señal+ruido
suma_SN= sen+ruido;

#Calculo potencia de ambas señales por separado
pot_S= potencia(sen);
pot_N= potencia(ruido);

#Calculo SNR
ratio= 10*log10(pot_S/pot_N);
printf('Primer SNR: %f\n', ratio)

#Escalo el ruido
ruido2= 2 .* ruido;

#Vuelvo a calcular potencia de ruido
pot_N2= potencia(ruido2);

#Vuelvo a calcular SNR con el nuevo ruido
ratio2= 10*log10(pot_S/pot_N2);
printf('Segundo SNR: %f\n', ratio2)

#Despejo constante para que SNR = 0
#SNR=0 -> Ps=Pr
k = sqrt(pot_S / pot_N);

ruido3 = k .* ruido;
pot_N3 = potencia(ruido3);

ratio3 = 10*log10(pot_S / pot_N3);
printf('Constante k para SNR = 0 dB: %f\n', k)
printf('Tercer SNR: %f\n', ratio3)

