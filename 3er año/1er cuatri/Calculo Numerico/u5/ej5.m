clear;
clc;
close all;

%% =====================
%% ETAPA 1
%% =====================

t1 = [0 1 2];

x1 = [0 2 6];
y1 = [0 4 6];


dfx1 = [0 0]; % ya que parte del reposo y en t=2 se detiene
dfy1 = [0 0];

[ax1,bx1,cx1,dx1] = cubic_spline_clamped(t1,x1,dfx1);
[ay1,by1,cy1,dy1] = cubic_spline_clamped(t1,y1,dfy1);
% llamo 2 veces, una para ver como evoluciona en x y otra en y

%% =====================
%% ETAPA 2
%% =====================

t2 = [2 3 4];

x2 = [6 3 0];
y2 = [6 2 0];

dfx2 = [0 0]; % ya que parte del reposo y en t=4 se detiene
dfy2 = [0 0];

[ax2,bx2,cx2,dx2] = cubic_spline_clamped(t2,x2,dfx2);
[ay2,by2,cy2,dy2] = cubic_spline_clamped(t2,y2,dfy2);

%% =====================
%% EVALUACION
%% =====================

tt1 = linspace(0,2,300);
tt2 = linspace(2,4,300);

xt1 = spline_eval(tt1,t1,ax1,bx1,cx1,dx1);
yt1 = spline_eval(tt1,t1,ay1,by1,cy1,dy1);

xt2 = spline_eval(tt2,t2,ax2,bx2,cx2,dx2);
yt2 = spline_eval(tt2,t2,ay2,by2,cy2,dy2);

%% =====================
%% x vs t
%% =====================

figure

plot(tt1,xt1,'b','linewidth',2)
hold on

plot(tt2,xt2,'r','linewidth',2)

plot(t1,x1,'ko')

grid on

title('x vs t')

xlabel('t')
ylabel('x')

legend('Etapa 1','Etapa 2')

%% =====================
%% y vs t
%% =====================

figure

plot(tt1,yt1,'b','linewidth',2)
hold on

plot(tt2,yt2,'r','linewidth',2)

plot(t1,y1,'ko')

grid on

title('y vs t')

xlabel('t')
ylabel('y')

legend('Etapa 1','Etapa 2')

%% =====================
%% Trayectoria plana
%% =====================

figure

plot(xt1,yt1,'b','linewidth',2)
hold on

plot(xt2,yt2,'r','linewidth',2)

plot([0 2 6 3 0],[0 4 6 2 0],'ko')

grid on
axis equal

title('Trayectoria del robot')

xlabel('x')
ylabel('y')

legend('Etapa 1','Etapa 2')
