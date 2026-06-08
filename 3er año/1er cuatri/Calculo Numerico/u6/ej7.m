
x = [0 200 400 600 800 1000 1200];

rho = [4 3.95 3.89 3.80 3.60 3.41 3.30];

Ac = [100 103 106 110 120 133 149.6];

%masa total integrando
y = rho .* Ac;

% Masa por trapecio compuesto
m_trap = trapcomp(x,y);

% Masa por Simpson compuesto
%se puede aplicar simpson ya que los x esta equiespaciado
% y tiene numero de subintervalos par
m_simp = simpsoncomp(x,y);

fprintf('Masa (Trapecio) = %.6f g\n',m_trap);
fprintf('Masa (Simpson)  = %.6f g\n',m_simp);

err_Rel= abs(m_simp-m_trap)/abs(m_simp);
fprintf('Error relativo = %.6e\n',err_Rel);
