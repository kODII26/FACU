% Leyes de kirchoff para armar el SEL
% Malla i1: 50(i1-i2)+30(i1-i3)=120-(-120) -> 80i1 - 50i2 - 30i3 =240
% Malla i2: 50(i2-i1)+15i2+25(i2-i4)+10(i2-i3)=0 -> 100i2 - 50i1 - 25i4 - 10i3 =0
% Malla i3: 10(i3-i2)+30(i3-i1)+5i3+20(i3-i4)=0 -> 65i3 - 10i2 - 30i1 - 20i4= 0
% Malla i4: 30i4+10i4+15i4+25(i4-i2)+20(i4-i3)=0 -> 100i4 - 25i2 -20i3 =0

% Armo la matriz

M= [80 -50 -30 0; -50 100 -10 -25; -30 -10 65 -20; 0 -25 -20 100]
b= [240,0,0,0]';

x=zeros(length(b));
x=gauss1(M,b);
x


