addpath('Funciones');

t=[1 2 3 4 5 6 7 8 9 10 11 12];
T=[26.6 24.7 23.4 19.7 17.2 13.9 14.4 15.3 16.9 20.1 22.9 24.5];

A=[t' ones(length(t),1) sin(pi*t'/6) cos(pi*t'/6)];

coef=A\T';

fprintf('a = %.4f\n',coef(1));
fprintf('b = %.4f\n',coef(2));
fprintf('c = %.4f\n',coef(3));
fprintf('d = %.4f\n',coef(4));

Taj=A*coef;

err=sum((T'-Taj).^2);

fprintf('error cuadratico absoluto = %.4f\n',err);

t2020=13;

tempM_2020 = coef(1)*t2020 + coef(2) + coef(3)*sin(pi*t2020/6) + coef(4)*cos(pi*t2020/6);

fprintf('temp media en enero 2020 = %.1f\n',tempM_2020);

err_rel = abs(27.5-tempM_2020)/27.5;

fprintf('error relativo = %.4f\n',err_rel);
