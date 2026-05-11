clc;
format long;
addpath("J:/Mi unidad/$Cursado actual/Calculo numerico/Scripts octave")

pkg load symbolic;
g = 9.8;
c = 15;
t = 5;
v = 35;
syms m;
f = @(m) c.*v-g.*m.*(1-exp(-c.*t./m));
f_sym = c.*v-sym('9.8').*m.*(1-exp(-c.*t./m));
df_sym = diff(f_sym);
df = matlabFunction(df_sym);
x = linspace(1,1000,1000);
figure(1)
cero = @(x) x*0;
hold on;
plot(x,cero(x),'y-');
plot(x,f(x),'r-');
plot(x,df(x),'b-');
hold off

[x,h,it] = Newton(f,df,100,10000,0.5e-5);
x
it


i = linspace(1,100,100);
r = @(c) c.*v-g.*110.*(1-exp(-c.*t./110));
syms c;
r_sym = c.*v-sym('9.8').*110.*(1-exp(-c.*t./110));
dr_sym = diff(r_sym);
dr = matlabFunction(dr_sym);

figure(2)
cero = @(x) x*0;

plot(i,cero(i),'y-');
hold on;
plot(i,r(i),'r-');
plot(i,dr(i),'b-');
[x,h,it] = Newton(r,dr,15,10000,0.5e-5);
x
it


