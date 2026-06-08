
f = @(x) x.^2 .* exp(-x);
Iexacta = 2 - 5/exp(1);

%Gauss n=2
[xg,w] = gauss_xw(2);

t = (xg+1)/2;

Igauss2 = 0.5*(w'*f(t));

%Trapecio
Itrap = intNCcompuesta(f,0,1,1,2);

fprintf('Valor exacto = %.12f\n',Iexacta);
fprintf('Gauss n=2    = %.12f\n',Igauss2);
fprintf('Trapecio     = %.12f\n',Itrap);

fprintf('Error Gauss  = %.6e\n',abs(Iexacta-Igauss2));
fprintf('Error Trap   = %.6e\n',abs(Iexacta-Itrap));

%Gauss n=3
[xg,w] = gauss_xw(3);

t = (xg+1)/2;

Igauss3 = 0.5*(w'*f(t));

%Simpson
Isimp = intNCcompuesta(f,0,1,1,3);

fprintf('\n');
fprintf('Gauss n=3    = %.12f\n',Igauss3);
fprintf('Simpson      = %.12f\n',Isimp);

fprintf('Error Gauss  = %.6e\n',abs(Iexacta-Igauss3));
fprintf('Error Simp   = %.6e\n',abs(Iexacta-Isimp));

%La cuadratura de Gauss proporciona errores menores que las fórmulas de Newton-Cotes utilizando
%la misma cantidad de puntos de integración. Esto ocurre porque los nodos y pesos se eligen de manera
%óptima, logrando un mayor grado de precisión para un mismo número de evaluaciones de la función.
