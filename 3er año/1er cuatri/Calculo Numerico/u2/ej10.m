A=[60 30 20;30 20 15; 20 15 12]

L=cholesky(A);

disp("L es: ");
disp(L);

disp(" L por L'");
disp(L*L');
