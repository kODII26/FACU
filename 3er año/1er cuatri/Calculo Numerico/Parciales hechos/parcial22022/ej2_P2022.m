T=[0.2 0.3 0.4 0.5 0.6 0.7 0.8];

I=[3.16 2.38 1.75 1.34 1.00 0.74 0.56];

Y=log(I);

p=polyfit(T,Y,1);

ord=p(2);
pend=p(1);

I0=exp(ord)
alpha=-pend

