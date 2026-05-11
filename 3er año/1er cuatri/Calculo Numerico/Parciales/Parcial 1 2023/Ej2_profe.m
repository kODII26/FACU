clear all; close all; clc;

t = 0.02;
z = @(a) 0.04.*sqrt(a+t).*(1-t)-t.*sqrt(3.*a)-t;

a = [0:0.01:50];
figure(1)
plot(a,z(a));


[p1, rh, it, t] = biseccion2(z,19,20,10000,1e-6);
disp(p1)

%%%%%%%%%%%%%%

a=p1;
z2=@(t) 0.04.*sqrt(a+t).*(1-t)-t.*sqrt(3.*a);

t=[-5;0.01;5];
figure(2)
plot(t,z2(t))

[p2, rh, it, t] = biseccion2(z2, -0.5, 0.5, 1000, 1e-6);
disp(p2)
