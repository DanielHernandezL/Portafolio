clear all
close all
clc

pb = [0.0 -0.2 0.0 1]';

Rab = [0 1 0; -1 0 0; 0 0 1];
tab = [0.2 0.2 0.2]';
Tab = [[Rab tab]; 0 0 0 1];

Rbc = [1 0 0; 0 0 -1; 0 1 0];
tbc = [0.2 0.2 -0.1]';
Tbc = [[Rbc tbc]; 0 0 0 1];

Rad = [0 -1 0; 1 0 0; 0 0 1];
tad = [0.6 -0.6 0.3]';
Tad = [[Rad tad]; 0 0 0 1];
%Tad = Tab*Tbc*Tcd
Tac = Tab*Tbc;

Tcd = inv(Tac)*Tad;

pa = Tab*pb;
pc = inv(Tbc)*pb;
pd = inv(Tcd)*pc



figure
Dibujar_Sistema_Referencia_3D(eye(4,4),'a')
Dibujar_Sistema_Referencia_3D(Tab,'b')
Dibujar_Sistema_Referencia_3D(Tac,'c')
Dibujar_Sistema_Referencia_3D(Tad,'d')
Dibujar_Punto_3D(pa)
