function [x,y] = polarCart (r,t)
  # Conversion de polares a cartesianas
  x= r*cos(t)
  y= r*sin(t)
endfunction

