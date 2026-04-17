A= [1 -2 3 0;3 -6 9 3; 2 1 4 1; 1 -2 2 -2];

[Af,r] = doolittle_p(A);
% Af(r,:) = matriz factorizada reordenada = sirve para sacar L y U
PAf= Af(r,:);

[L,U]= extraer_LU(PAf);

% A(r,:) = matriz original permutada = PA
PA= A(r,:);

disp("P*A:");
disp(PA);

disp("L*U:");
disp(L*U);

