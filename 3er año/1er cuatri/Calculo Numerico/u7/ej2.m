clear;
clc;
close all;

f = @(t,y) -y + sin(t) + cos(t);

inter = [0 2];
y0 = 0;

y_exacta = sin(2); %esto sale de resolver la EDO

Lvec = [20 40 80 160 320 640];

fprintf('Valor exacto y(2) = %.10f\n\n',y_exacta);

fprintf('   L        Euler          RK2            RK4\n');

for i=1:length(Lvec)

    L = Lvec(i);

    [tE,yE] = euler(f,inter,y0,L);
    [t2,y2] = rk2(f,inter,y0,L);
    [t4,y4] = rk4(f,inter,y0,L);

    fprintf('%4d   %12.8f   %12.8f   %12.8f\n',...
            L,yE(end),y2(end),y4(end));

end
