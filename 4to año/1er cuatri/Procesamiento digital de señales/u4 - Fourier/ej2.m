addpath('../Funciones creadas');
% GENERACION DE SEÑALES
sen = generar_senoidal(2,100,0,0,1);

cuad = generar_cuadrada(2,100,0,0,1);

sen2 = generar_senoidal(4,100,0,0,1);

% item 1, ortogonalidad en dominio temporal
disp('item 1 - dominio temporal');
prod1 = dot(sen,cuad);
disp('Producto interno senoidal 2Hz y cuadrada 2Hz:');
disp(prod1);
if(abs(prod1) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

prod2 = dot(sen,sen2);
disp('Producto interno senoidal 2Hz y senoidal 4Hz:');
disp(prod2);
if(abs(prod2) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

prod3 = dot(cuad,sen2);
disp('Producto interno cuadrada 2Hz y senoidal 4Hz:');
disp(prod3);
if(abs(prod3) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

% item 2, ortogonalidad en frecuencia
disp('');
disp('item 2 - dominio frecuencial');
S1 = fft(sen);
S2 = fft(cuad);
S3 = fft(sen2);

prod1 = dot(S1,S2);
disp('Producto interno FFT senoidal 2Hz y cuadrada 2Hz:');
disp(prod1);
if(abs(prod1) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

prod2 = dot(S1,S3);
disp('Producto interno FFT senoidal 2Hz y senoidal 4Hz:');
disp(prod2);
if(abs(prod2) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> Son ortogonales');
endif

prod3 = dot(S2,S3);
disp('Producto interno FFT cuadrada 2Hz y senoidal 4Hz:');
disp(prod3);
if(abs(prod3) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif


% item 3, cambio de frecuencia a 3.5
disp('');
disp('item 3 - cambio de frecuencia a 3.5Hz');
sen3 = generar_senoidal(3.5,100,0,0,1);
prod = dot(sen,sen3);
disp('Producto interno temporal entre 2Hz y 3.5Hz:');
disp(prod);

if(abs(prod) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

S4 = fft(sen3);

prod = dot(S1,S4);

disp('Producto interno frecuencial entre 2Hz y 3.5Hz:');
disp(prod);

if(abs(prod) < 1e-10)
  disp('=> Son ortogonales');
else
  disp('=> No son ortogonales');
endif

