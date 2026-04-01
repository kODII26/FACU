#Inversión → cambia el signo
#Rectificación → elimina parte negativa
#Cuantización → discretiza la amplitud (la hace “escalonada”)


fm = 1000;  % Frecuencia de muestreo fija por consigna
tini = -1;
tfin = 1;
fs = 5;   % Respeta 2*fs <= fm
fase = 0;


[y,t] = generar_senoidal(fs,fm,fase,tini,tfin);


[y_inv,t_inv] = inversion(y,t);

[y_rect,t_rect] = rectificacion(y,t);

N=5;
[y_cuant,t_cuant] = cuantizacion(y,t,N);

figure(1); plot(t,y); title('Original');
figure(2); plot(t_inv,y_inv); title('Invertida');
figure(3); plot(t_rect,y_rect); title('Rectificada');
figure(4); plot(t_cuant,y_cuant); title('Cuantizada');

