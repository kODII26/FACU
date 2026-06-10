% euler , rk2 y rk4 son metodos de un paso(usan info del yn para predecir yn+1)
% adams es multipaso:
% adam bashforth (predictor): para hallar yn usa fn,fn-1,fn-2,fn-3
%adam moulton(corrector): para usarlo primero hay que predecir yn+1
% usa yn+1 , fn+1 , fn, fn-1 , fn-2

%usamos rk4 primero ya que AB necesita y0,y1,y2,y3 para arrancar y el
%problema solo nos da y0


f = @(t,y) t.*exp(3*t)-2*y;

yexacta = @(t) (t.*exp(3*t))/5 - exp(3*t)/25 + exp(-2*t)/25;

a = 0;
b = 1;
y0 = 0;

h = 0.05;
N = round((b-a)/h);

t = linspace(a,b,N+1)';

%% Valores iniciales usando RK4

[t_rk,y_rk] = rk4(f,[a b],y0,N);

y = zeros(N+1,1);

y(1:4) = y_rk(1:4);

%% Adams predictor-corrector

for n=4:N

    fn   = f(t(n),y(n));
    fn1  = f(t(n-1),y(n-1));
    fn2  = f(t(n-2),y(n-2));
    fn3  = f(t(n-3),y(n-3));

    % Adams-Bashforth 4 (predictor)

    yp = y(n) + h/24 * (55*fn - 59*fn1 + 37*fn2 - 9*fn3);

    fnp1 = f(t(n+1),yp);

    % Adams-Moulton 4 (corrector)

    y(n+1) = y(n) + h/24 * (9*fnp1 + 19*fn - 5*fn1 + fn2);

end

%% Solucion exacta

yex = yexacta(t);

%% Error final

errRK4 = abs(y_rk(end)-yexacta(1));
errPC  = abs(y(end)-yexacta(1));

fprintf('RK4               = %.12f\n',y_rk(end));
fprintf('PredictorCorrector= %.12f\n',y(end));
fprintf('Exacta            = %.12f\n\n',yexacta(1));

fprintf('Error RK4         = %.6e\n',errRK4);
fprintf('Error P-C         = %.6e\n',errPC);

%% Grafico

figure(1)

plot(t,yex,'k')
hold on

plot(t_rk,y_rk,'o-')
plot(t,y,'*-')

legend('Exacta','RK4','Adams PC')
grid on
