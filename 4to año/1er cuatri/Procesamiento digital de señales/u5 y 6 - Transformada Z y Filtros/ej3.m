% zplane dibuja los polos y los ceros en el plano Z
pkg load signal

a= [1 -1.7 0.8 -0.1]; % son los productos desarrollados

b= [1 -2 2 -1];

disp('Polos: ');
roots(a)

disp('Ceros: ');
roots(b)

figure
zplane(b,a)
grid on

figure
impz(b,a)
grid on

% los polos son los valroes de z que hacen que H(z) valga inf (denominador = 0)
% los ceros hacen que H(z) valga cero (numerador = 0)
