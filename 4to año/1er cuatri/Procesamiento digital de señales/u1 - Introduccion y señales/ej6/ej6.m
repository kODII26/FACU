addpath('../Funciones creadas');


#Genero una senoidal
fs=1;
phi=0;
t_inicial=0;
t_final=1;
[y,t]= generar_senoidal(fs,fm,phi,t_inicial,t_final);

#Sobremuestreo
[yi, ti] = sobremuestreo(y, t, fm, 4);

plot(t, y, 'o')
hold on
plot(ti, yi, '-')
legend('Original', 'Interpolada')

