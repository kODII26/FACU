%a
[x,y] = meshgrid(-3:0.2:3,-3:0.2:3);

r2 = x.^2 + y.^2;

u = x./(2*pi*r2);
v = y./(2*pi*r2);

quiver(x,y,u,v)
axis equal
grid on

%b
figure
[x,y] = meshgrid(-3:0.2:3,-3:0.2:3);

u = ones(size(x));
v = zeros(size(x));

quiver(x,y,u,v)
axis equal
grid on

%c
A=1;
n=2;
figure
[x,y] = meshgrid(-3:0.2:3,-3:0.2:3);

r = sqrt(x.^2+y.^2);
theta = atan2(y,x);

ur = A*n*r.^(n-1).*cos(n*theta);
ut = -A*n*r.^(n-1).*sin(n*theta);

u = ur.*cos(theta) - ut.*sin(theta);
v = ur.*sin(theta) + ut.*cos(theta);

quiver(x,y,u,v)
axis equal
grid on

%d
figure
[x,y] = meshgrid(-3:0.2:3,-3:0.2:3);

r2 = x.^2+y.^2;

u = (y.^2 - x.^2)./(r2.^2);
v = (-2*x.*y)./(r2.^2);

quiver(x,y,u,v)
axis equal
grid on
