function y = conv_lineal(x, h)
  % La salida de la conv lineal tiene longitud: 4+4-1=7
  long_salida=length(x)+length(h)-1;
  y=zeros(1,long_salida);
  for n=1:long_salida
    y(n)=0; %La convolucion es una sumatoria, la idea
            %es para cada n ir acumulando terminos, no reemplazarlos
    for k=1:length(x)
      j=n-k+1; % Se corre ya que los indicecs en octave empiezan en 1 no en 0
     if (j >= 1 && j<= length(x)) % y entre [1,N], si no , no se considera ese termino en la sumatoria
        y(n)+=x(k)*h(j);
      endif
    endfor
  endfor

endfunction
