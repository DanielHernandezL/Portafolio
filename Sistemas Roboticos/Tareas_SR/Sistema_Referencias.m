clear all
close all
clc

%% Ejemplo
Rz = @(theta) [cos(theta) -sin(theta) 0; sin(theta) cos(theta) 0;  0 0 1];
Rx = @(theta) [1 0 0; 0 cos(theta) -sin(theta); 0 sin(theta) cos(theta)];
Tinv = @(T) [[T(1:3,1:3)' -T(1:3,1:3)'*T(1:3,4)]; 0 0 0 1];

Rab = Rz(pi/2);
tab = [0.2 0.5 0.3]';
Tab = [[Rab tab]; 0 0 0 1];

Rac = Rx(-pi/2);
tac = [0.4 -0.3 0.5]';
Tac = [[Rac tac]; 0 0 0 1];

Rcd = eye(3);
tcd = [-0.8 0.0 -0.2]';
Tcd = [[Rcd tcd]; 0 0 0 1];

pb = [0.0 0.4 -0.1 1.0]';
pa = Tab * pb;

Tbc = inv(Tab)*Tac;

Tad = Tab*Tbc*Tcd;

Tdb = inv(Tcd)*inv(Tac)*Tab;
Tbd = Tbc*Tcd;
%Tdb = inv(Tbd)

pc = inv(Tac)*pa;
pd = Tdb*pb;

% inv(Tad)
% Tinv(Tad)

% pa = [0.3 0.2 0.5 1.0]';
% pb = inv(Tab) * pa

figure
Dibujar_Sistema_Referencia_3D(eye(4,4),'a')
Dibujar_Sistema_Referencia_3D(Tab,'b')
Dibujar_Sistema_Referencia_3D(Tac,'c')
Dibujar_Sistema_Referencia_3D(Tad,'d')
Dibujar_Punto_3D(pa)