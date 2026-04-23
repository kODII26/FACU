function y = conv_circular(x, h)
  N = length(x);

  if length(h) ~= N
    error("x y h deben tener la misma longitud");
  endif

  y = zeros(1, N);

  for k = 1:N
    y(k) = 0;
    for l = 1:N
      indice_x = mod(N + k - l, N) + 1;
      y(k) = y(k) + h(l) * x(indice_x);
    endfor
  endfor
endfunction

