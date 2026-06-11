addpath('Funciones');

%x|y|z|vx|vy|vz -> con cambio de variable u1=x,u2=y,u3=z,u4=vx,...
f= @(t,y) [y(4) ; y(5) ; y(6) ; y(5)*sin(50*t) ; -y(4)*sin(50*t); 0];

%  x0|y0|z0|v0x|v0y|v0z
y0=[1 0 0 0 1 0];
inter=[0 2];
h=0.02;
L=(2-0)/h;


[t_rk,y_rk]=rk4(f, inter, y0, L);

x_final=y_rk(end,1); %miro el ultimo instante de tiempo analizado ya que esa es la pos final
y_final=y_rk(end,2);
z_final=y_rk(end,3);
%% con h=0.02
%1.040 - 210288889821
%1.999 - 414244987628
%0
%Para h=0.02/2 = 0.01 :
%1.040 - 196717882686
%1.999 - 397473276363
% 4 cifras
printf("x = %.4f\n",x_final);
printf("y = %.4f\n",y_final);
printf("z = %.4f\n",z_final);

%item b en t=2s con 5 cifras significativas
v_y=y_rk(end,5);
v_x=y_rk(end,4);
v_z=y_rk(end,6);
a_x=v_y*sin(50*2);
a_y=-v_x*sin(50*2);
printf("ax = %.5g\n",a_x);
printf("ay = %.5g\n",a_y);

%item c

vel=sqrt(y_rk(:,4).^2+y_rk(:,5).^2+y_rk(:,6).^2);

Q = trapcomp(t_rk,vel)

