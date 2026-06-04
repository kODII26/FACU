clc;
clear all;
format long;
##%PREGUNTA 3-----------------------
##m=10;
##c=0.2;
##g=9.81;
##z0=[0;30;40;0];
##
##inter=[0,2.5]; %para ver en que t toca el piso
##
##f=@(t,z) [z(3);z(4); -(0.2/10).*z(3) ; -(9.81) - (0.2/10).*z(4)];
##
##h=0.05;
##L=(2.5-0)/h;
##
##[t1,y1]=rk4(f, inter, z0, L);
##%y1 = [posx posy velx vely]
##posx=y1(:,1);
##posy=y1(:,2);
##
##figure(1)
##plot(posx,posy);
##title("Trayectoria del tiro parabolico")
##xlabel("coord x")
##ylabel("coord y")
##grid on
##grid minor
##
##%%calculo del tiempo para el punto A
##poli=polyfit(t1',posy,2); %genero los valores para un polinomio de grado 2
##g = @(t) poli(3)+(poli(2).*t)+(poli(1).*(t.^2));
##[piso, rh, it, t] = biseccion(g, 0,3 , 300, 0.00000001);
##disp("El proyectil toca el piso a los")
##piso
##
##%como ahora sabemos a los cuantos segundos toca el piso, usamos esa t para otro rk4
##inter2=[0,piso];
##[t2,y2]=rk4(f, inter2, z0, L);
##disp("El proyectil toca el piso a una distancia de")
##pos=length(t2); %ya que es el ultimo valor de t2 el correspondiente a donde toca el piso
##valorx_piso=y2(pos)
##
##%buscamos la posicion i
##for i=1:length(t2)
##  if(t2(i)==piso)
##    pos2=i
##    break;
##  end
##  end
##pos2
##y2(pos)
##disp("-----------------INCISO B------------------");
##
##%buscamos la posicion para la cual t=2seg
##
##for i=1:length(t1)
##  if(t1(i)==2)
##    pos2=i
##    break;
##  end
##  end
##pos2
##
##%armamos un spline para x e y y hacemos la integral
##
##
### Calcular la distancia recorrida por el proyectil en los 2
### primeros segundos. 5 digitos exactos
##a = 0;
##b = 2;
##L = 500;
##[tRK, wRK] = rk4(f,inter,z0,L);
##
##vx = wRK(:,3)';
##pvx = polyfit(tRK',vx,2);
##dSx = @(t) pvx(3) + pvx(2).*t + pvx(1).*t.^2;
##
##vy = wRK(:,3)';
##pvy = polyfit(tRK',vy,2);
##dSy = @(t) pvy(3) + pvy(2).*t + pvy(1).*t.^2;
##
##f = @(t) sqrt(dSx(t).^2 + dSy(t).^2);
##
##dist=SimpsonCompuesto(f,0,2,L);
##disp("La distancia recorrida a los 2 segundos es:")
##dist
##
###Qref = quad(f,a,b,[1e-5;1e-5]);
##L = 10;
##n = 2;
##format long;
##for i=1:5
##  Q = cuad_gauss_c(f,a,b,L,n);
##  L *= 2;
##endfor
##
### La distancia recorrida los primeros 2 segundos fue 81.51906 m
##
##compTray=sqrt ( (t2.*y2(:,2)).^2 + (t2.*y2(:,1)-t2.*y2(:,2)).^2);
##Tray=SimpsonCompuestoDatos(t2(1:pos2),compTray(1:pos2)); %pos2 es el valor para el cual t= 2seg q es donde pide
##disp("La distancia recorrida a los 2 segundos es:")
##Tray
##


##%PREGUNTA 4 -------------------------
##disp("-----------------Pregunta 4---------------")
##f=@(x) log(x^2+1)-exp(x/2)*cos(pi*x);
##x=linspace(-5,6,9);  %intervalo de -5 a 6 en 9 puntos
##xx=linspace(-5,6,201);
##%evaluamos en f para armar la tabla de los valores
##%y=[f(x(1)),f(x(2)),f(x(3)),f(x(4)),f(x(5)),f(x(6)),f(x(7)),f(x(8)),f(x(9))];
##y=arrayfun(f,x);
##disp("Tabla x e y")
##tabla=[x ; y]'
##
##[Sx,dSx]=funcion_spline(x,y,0,0);
##figure(1)
##plot(xx,Sx(xx),'r')
##hold on;
##plot(xx,dSx(xx),'b')
##grid on;
##hold on;
##legend('Sx','dSx')
##%plot(xx,f(xx))
##
##%Evaluar el spline cúbico sujeto en x=4.2
##disp("El error es:")
##error=min(max(abs(y-Sx(4.2))))/2
##disp("--------------------------------------------")
##
##%PARA ENCONTRAR EL MAXIMO
##valor_max=-100000;
##for i=0:0.01:6
##  nuevo_max=Sx(i);
##  if(nuevo_max>valor_max)
##    xmax=i;
##    valor_max=nuevo_max;
##  end
##end
##format long;
##disp("El valor donde alcanza el maximo es")
##xmax
##disp("El maximo es:")
##valor_max
##
##
##[p, rh, it, t] = biseccion(dSx, 3, 5,10000,1e-5);
##disp("El valor donde alcanza el maximo es")
##p
##disp("Y su maximo es ")
##Sx(p)

##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 5--------------------------")
##
##u0=[0;0];
##f = @(x,w) [w(2);-100*x*(1-x)+5*w(1)];
##
##inter=linspace(0,1,41);


##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 6--------------------------")
##m=20;
##k=20;
##c=10;
##
##
##f=@(t,z) ([ z(2); (((-c*z(2))/m) -((k*z(1))/m))]);
##y0=[1,0];   %y0=[posicion ; velocidad]
##inter=[0,10];
##h=0.05;
##L=(10-0)/h;
##
##[t,y] = rk4(f,inter, y0, L);
##
##plot(t,y(:,1),'r');
##hold on;grid on;grid minor;
##plot(t,y(:,2),'b');
##legend('posicion y(:,1)','velocidad y(:,2)');
##
##for i=1:length(t)
##  if(t(i)==10)
##    pos=i
##end
##end
##y(pos,1)
##
##posy1=y(:,1);
##posy2=y(:,2);
##
##vel_max=0;
##tiempo=0;
##for i=1:length(t)
##  if(abs(y(i,2))>abs(vel_max))
##    vel_max=(y(i,2));
##    tiempo=t(i);
##end
##end
##
##disp("La velocidad maxima es:")
##vel_max
##disp("A un tiempo de : ")
##tiempo


##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 7--------------------------")
##x=[1 1.2 1.4 1.6 1.8 2.0 2.2 2.4];
##y=[0.678 0.512 0.387 0.293 0.221 0.167 0.126 0.096];
##ly=log(y); %para linealizar la funcion
##
##%la funcion es f(x)=a*e^b*x asi q es grado 1
##[coef,A,b] = minimoscuadrados(x,ly,1);
##
##f=@(x) exp(coef(2))*(exp(coef(1)*x));
##df=@(x) exp(coef(2)+coef(1)*x)*coef(1);
##valory=f(1.9)
##
##%[S,dS,a,b,c,d]=funcion_spline(x,y,0,0);
##%valory=S(1.9)
##
##%xx=linspace(0, 3, 201);
##%figure(1)
##%plot(xx,f(xx),'r')
##%hold on;
##%plot(xx,S(xx),'b')
##%legend('polinomio r2','polinomio spline')
##
##
##F = @(x) 2*pi*f(x).*sqrt(1+df(x).^2);
##
##[S]= SimpsonCompuesto(F,1,2.4,100);
##S

##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 8--------------------------")
##f=@(x) 1+x+cos(x);
##df=@(x) -sin(x)+1;
##F = @(x) 2*pi*f(x).*sqrt(1+df(x).^2);
##%inter=[0,4];
##a=0;
##b=4;
##n=3;
##L=10;
##Q=cuad_gauss_c(F,a,b,L,n);
##Q
##disp("=======================================================================================================")

##%[S]= SimpsonCompuesto(F,a,b,L);
##%S
##%q = quad(F,a,b);
##%q
##
##%para ver la cantidad de cifras exactas aumentamos la L o n?
##Q=cuad_gauss_c(F,a,b,L,6);
##Q
##Q=cuad_gauss_c(F,a,b,L,12);
##Q
##Q=cuad_gauss_c(F,a,b,L,16);
##Q
##Q=cuad_gauss_c(F,a,b,L,100);
##Q
##disp("Vemos que con L=10 tiene igual a los demas hasta 90.5942, por tanto 6 cifras exactas");

##%PREGUNTA 9
##a = 0;
##b = 20;
##inter=[0,20];
##h = 0.01
##L = (b-a)/h;
##
###Calculo el angulo donde comienza el amortiguamiento
##tita_0 = acos(h/L);
##
##%defino el pvi
##y0=[pi/2 ; 0];
##%primero pi/2 y despues 0 ya que es % y0=[posicion; velocidad]
##f = @(t, v) [v(2); (-0.8.*(abs(v(1))<tita_0).*v(2)-sin(v(1)))]
##
###Calculo PVI mediante RK4
##[t,y] = rk4(f,inter, y0, L);
##plot(t,y(:,1),'r');
##hold on;grid on;grid minor;
##plot(t,y(:,2),'b');
##t
##for i=1:length(t)
##  if(t(i)==5)
##    pos=i
##end
##end
##
##disp("la posicion del pendulo a t=5 es:")
##y(pos,1);

%PREGUNTA 10
##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 10--------------------------")
##
##f=@(x) 5/x;
##
##
##x1=linspace(1,2,10);
##y1=arrayfun(f,x1);
##
##x2=linspace(2,3,10);
##y2=arrayfun(f,x2);
##
##[S,dS,a1,b1,c1,d1]=funcion_spline_natural(x1,y1);
##
##[a1' b1' c1' d1']
##
##[S2,dS,a2,b2,c2,d2]=funcion_spline_natural(x2,y2);
##
##[a2' b2' c2' d2']


##%PREGUNTA 11
##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 11--------------------------")
##
##inter=[0,5];
##y0=[1;0;-1];
##h=0.05;
##L=(15-0)/0.05;
##
##f=@(t,y) [y(2);y(3);-4*sin(t)-2*cos(t)-4*y(3)-5*y(2)-2*y(1)];
##
##
##[t,y]=rk4(f, inter, y0, L);
##%[t,y] = RungeKuttaMulti(f,0,15,y0,L);
##figure(1)
##plot(t,y(:,1),'r');
##hold on;
##grid on;
##grid minor;
##plot(t,y(:,2),'b');
##plot(t,y(:,3),'g');
##legend('funcion 1','funcion 2','funcion 3');
##
##%para ver los puntos de inflexion necesitamos igualar a 0 la segunda derivada
##%por tanto seria la columna 3 por el inciso y como esta declarada y0
##
##poli=polyfit(t,y(:,3),2);
##g=@(t) poli(3) + (poli(2).*t)+(poli(1).*(t.^2));
##[p1, rhbis, itbis, tbis] = biseccion(g, 0, 2, 300, 1e-5); %fijando en la grafica elegimos el intervalo que contenga a la primer raiz
##[p2, rh, it, t] = biseccion(g,3,5, 300, 1e-5); %fijando en la grafica elegimos el intervalo que contenga a la segunda raiz
##p1
##p2
##
##figure(2)
##tt=linspace(0,15,201);
##plot(tt,g(tt))


%PREGUNTA 13
##disp("==================================================================================================================================")
##disp("------------------------PREGUNTA 13--------------------------")
##f=@(x) 2+cos(x)-sin(3*x);
##df=@(x) -sin(x)-3*cos(3*x);
##F = @(x) 2*pi*f(x).*sqrt(1+df(x).^2);
##%inter=[0,3];
##a=0;
##b=3;
##n=3;
##L=30;
##Q=cuad_gauss_c(F,a,b,L,n);
##Q
##%[S]= SimpsonCompuesto(F,a,b,L);
##%S
##%q = quad(F,a,b);
##%q
##
##%para ver la cantidad de cifras exactas aumentamos la L
##Q=cuad_gauss_c(F,a,b,40,n);
##Q
##%Q=cuad_gauss_c(F,a,b,80,n);
##%Q
##%Q=cuad_gauss_c(F,a,b,160,n);
##%Q
##%Q=cuad_gauss_c(F,a,b,320,n);
##%Q
##disp("Vemos que con L=30 tiene igual a los demas hasta 77.52682, por tanto 7 cifras exactas");

%PREGUNTA 14
##%DATOS:
##x1 = [0,2,6];
##y1 = [0,4,6];
##t1 = [0,1,2];
##x2 = [6,3,0];
##y2 = [6,2,0];
##t2 = [2,3,4];
##
##tiempo=[5,6]
##
##
##% TRAYECTORIA EN X:
##[Sx,dSx,ax,bx,cx,dx]=funcion_spline(t1,x1,0,0);
##[Sx2,dSx2,ax2,bx2,cx2,dx2]=funcion_spline(tiempo,x2,0,0);
##
##% TRAYECTORIA EN Y
##[Sy,dSy,ay,by,cy,dy]=funcion_spline(t1,y1,0,0);
##[Sy2,dSy2,ay2,by2,cy2,dy2]=funcion_spline(tiempo,y2,0,0);
##
##%Pregunta por velocidad a t=5.5 por tanto usamos dSx2 y dSy2
##velocidad_x=dSx2(5.5)
##velocidad_y=dSy2(5.5)

%PREGUNTA 15
##f=@(x) 1/(4*x);
##x=linspace(1,3,3);
##y=arrayfun(f,x);
##[P, L] = Lagrange(x,y);
##
##
##%4 derivadas pq son n+1 derivadas y n=3 puntos
##df = @(x) -1 ./(4 .* x.^2);
##ddf = @(x) 1 ./(2 .* x.^3);
##dddf = @(x) -3 ./(2 .*x.^4);
##ddddf = @(x) 6 ./x.^5;
##
##%formula  [(x - x₀)(x - x₁)...(x - xₙ)] / (n + 1)!  * el max de la derivada n+1 evaluada en xx=1.7
##Emax = abs((1.7-1)*(1.7-2)*(1.7-3) / factorial(4)) * max(ddddf(x))
##Ereal=polyval(P,1.7) - abs(f(1.7))

##
##%PREGUNTA 16
##
##g=9.81;
##l=2; %inciso dice q l=2metros
##
##h=0.05;
##L=(20-0)/h;
##
##inter=[0,10];
##
##f=@(t,z) [z(2);-(g/l)*sin(z(1))];
##
##
## % condicion inicial, segun los diferentes puntos del ejercicio
##               % y0=[posicion; velocidad]
##
##%indique posicion a los 10 seg si parte del equilibrio con velocidad 1
##
##z0=[0;1];
##[t,y]=rk4(f, inter, z0, L);
##
##for i=1:length(t)
##  if (t(i)==10)
##    posi=i;
##    pos=y(i,1);
##  endif
##end
##  pos
##  resul=y(end,1)


