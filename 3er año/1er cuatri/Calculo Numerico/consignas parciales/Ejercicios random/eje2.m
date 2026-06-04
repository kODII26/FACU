clear all; clc;
format long;
addpath("G:/Mi unidad/$Cursado actual/Calculo numerico/Scripts octave")
A = [1 2 -2 -1 0; -1 3 -1 -1 -2; 0 -2 3 2 0; -1 0 -1 2 -1; 2 0 -2 -1 3];
b = [1 -2 5 5 -1]';
[A,x]=gauss1(A,b);
x
x1 = 3.000
x2 = 0.400
x3 = -0.200
x4 = 3.200
x5 = -1.400

