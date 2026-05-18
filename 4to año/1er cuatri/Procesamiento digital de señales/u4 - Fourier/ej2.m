addpath('../Funciones creadas');

sen=generar_senoidal(2, 100, 0, 0, 1);
cuad=generar_cuadrada(2, 100, 0, 0, 1);
sen2=generar_senoidal(4,100,0,0,1);

% item 1
prod1= dot(sen,cuad);
disp(prod); % no es ortogonal

prod2=dot(sen,sen2);
disp(prod2); % ortogonal

prod3=dot(cuad,sen2);
disp(prod3); % ortogonal

% item 2

S1=fft(sen);
S2=fft(cuad);
S3=fft(sen2);
prod1= dot(S1,S2);
disp(prod); % no es ortogonal

prod2=dot(S1,S3);
disp(prod2); % ortogonal

prod3=dot(S2,S3);
disp(prod3); % ortogonal

% item 3

sen2=generar_senoidal(3.5,100,0,0,1);

prod=dot(sen,sen2);
disp(prod); % es ortogonal

S4=fft(sen2);
prod=dot(S1,S4);
disp(prod);









