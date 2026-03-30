x=linspace(-pi,pi,100)
f= cos(x)


# a
g1=ones(size(x))
figure()
plot(x,f,x,g1)
legend('cos','g(x)=1')
title('inciso a')
xlabel('x')
ylabel('y')
grid on


# b
g2= 1-(x.^2/factorial(2))
figure()
plot(x,f,x,g2)


# c
g3= 1-(x.^2/factorial(2))+(x.^4/factorial(4))
figure()
plot(x,f,x,g3)

# d
g4= 1-(x.^2/factorial(2))+(x.^4/factorial(4))-(x.^6/factorial(6))
figure()
plot(x,f,x,g4)



