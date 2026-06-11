
f = @(t,x) [x(2); (t.^3.*log(t) + 2*t.*x(2) - 2*x(1))./(t.^2)];

yexacta = @(t) (7/4).*t + (1/2).*t.^3.*log(t) - (3/4).*t.^3;

hvec = [0.2 0.1 0.05];

fprintf('      h          Error maximo\n');

for k=1:length(hvec)

    h = hvec(k);

    L = round((2-1)/h);

    [t,y] = adams_rashford(f,[1 2],[1;0],L);

    yex = yexacta(t);

    errmax = max(abs(y(:,1)-yex));

    fprintf('%8.3f     %12.6e\n',h,errmax);

end
