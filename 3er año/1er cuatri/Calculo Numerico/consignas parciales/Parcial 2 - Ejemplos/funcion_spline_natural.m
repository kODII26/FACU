function [S,dS,a,b,c,d]=funcion_spline_natural(x1,y1)

[a, b, c, d] = Spline_Cubico_Natural(x1, y1);

S=@(x) a(1)*(x==x1(1));

M=[d' c' b' a']; % Aca Corregi!!!!!! Aca va Transpuesto, por eso no anda
dM=[];
dS= @(x) 0;
for i=1:length(x1)-1
  dM=[dM;polyder(M(i,:))];
  S=@(x) S(x) +...
  polyval(M(i,:),x-x1(i)).*(x>x1(i)).*(x<=x1(i+1));
  dS=@(x) dS(x) +...
  polyval(dM(i,:),x-x1(i)).*(x>x1(i)).*(x<=x1(i+1));
endfor
