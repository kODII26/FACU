function [wmin] = w_optimo(A,b)

x0=b;
#Obtener w
ws=[];
its=[];
wmin = 0;
itmin = 1000;
for w=0.1:0.01:2
  [x,rh,it,t]=sor(A,b,x0,1000,1e-8,w);
  if (it<itmin)
    wmin = w;
    itmin = it;
  endif
  ws = [ws w];
  its = [its it];
endfor

%plot(ws,its);

