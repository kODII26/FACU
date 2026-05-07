function p= potencia(sen)
  N=length(sen);
  # p=(señal*señal)/N; #señal * señal sería 1x51 * 1x51
  # eso no se puede, porque las dimensiones no coinciden
  p = sum(sen.^2) / N;
endfunction

