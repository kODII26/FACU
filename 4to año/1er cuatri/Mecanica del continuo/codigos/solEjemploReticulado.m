#Como es simbolico podemos usar la funcion inversa, cuando es numerico nunca uses la funcion inversa

syms Fa Fb Fc Fd Fe Ff Fg Fh Fi RAx RAy RB
syms W

nDim=12;

#raiz2=sym(sqrt(2)/2); Asi anda en matlab pero no en cotave ya que calcula primero sqrt2 antes que sym lo agarre
raiz2 = sqrt(sym(2))/2;

# 0,0,0,0,0,0,0,0,0,0,0,0;
m_K=[raiz2,1,0,0,0,0,0,0,0,1,0,0;
    raiz2,0,0,0,0,0,0,0,0,0,1,0;
    0,0,0,0,0,0,-1,0,-raiz2,0,0,0;
    0,0,0,0,0,0,0,0,raiz2,0,0,1;
    0,-1,-raiz2,0,0,raiz2,1,0,0,0,0,0;
    0,0,raiz2,0,1,raiz2,0,0,0,0,0,0;
    -raiz2,0,raiz2,raiz2,0,0,0,0,0,0,0,0;
    -raiz2,0,-raiz2,raiz2,0,0,0,0,0,0,0,0;
    0,0,0,0,0,-raiz2,0,-raiz2,raiz2,0,0,0;
    0,0,0,0,0,-raiz2,0,raiz2,-raiz2,0,0,0;
    0,0,0,-raiz2,0,0,0,raiz2,0,0,0,0;
    0,0,0,-raiz2,-1,0,0,-raiz2,0,0,0,0];

m_T=sym(zeros(nDim,1));
m_T(10)=-W/2;
m_T(12)=W;

m_SolF=simplify(m_K\m_T);

#Paso la solucion a numerico
WNum=1;
m_KNum=double(m_K);
m_TNum=double(subs(m_T,W,WNum));
m_SolFNum= m_KNum\m_TNum















