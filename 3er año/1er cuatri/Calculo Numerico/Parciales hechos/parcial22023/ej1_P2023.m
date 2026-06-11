x=[0 0.2 0.4 0.6 0.8 1 1.2 1.4 1.6 1.8 2.0];

y=[4.24 4.44 4.91 5.44 5.65 5.33 3.91 1.86 0.07 -1.16 -1.94];

A=[ones(length(x),1) cos((pi.*x')/2) cos(pi*x'/2).^2];

a=A\y';

a0=a(1);
a1=a(2);
a2=a(3);
fprintf('a0 = %.2f\n',a0);
fprintf('a1 = %.2f\n',a1);
fprintf('a2 = %.2f\n',a2);

%error para x=1 con 4 decimales
y_real=5.33;
y_ajuste=a0+a1*cos((pi*1)/2)+a2*cos((pi*1)/2)^2;

err= y_real-y_ajuste;
fprintf('error = %.4f\n',err);
