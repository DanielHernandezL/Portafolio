clear all
close all
clc

 syms theta_1 d_2 d_3 real

% Definir las longitudes de los enlaces del robot
d_1 = 0.35;
 

%Tablas de transformación homogenea del manipulador cilíndrico
T01 = [cos(theta_1) -sin(theta_1) 0 0;sin(theta_1) cos(theta_1) 0 0;0 0 1 d_1;0 0 0 1];
T12 = [1 0 0 0;0 0 -1 0;0 1 0 d_2;0 0 0 1];
T23 = [1 0 0 0;0 1 0 0;0 0 1 d_3;0 0 0 1];


% Multiplicamos las matrices de transformación para obtener las transformaciones completas
T02 = simplify(T01*T12);
T03 = simplify(T02*T23);

x = T03(1,4);
y = T03(2,4);
z = T03(3,4);

% Calcular el Jacobiano lineal (Jv) usando las derivadas parciales de x, y, z respecto a theta_1, d_2 y d_3
Jv = [diff(x,theta_1) diff(x,d_2) diff(x,d_3); diff(y,theta_1) diff(y,d_2) diff(y,d_3); diff(z,theta_1) diff(z,d_2) diff(z,d_3)];

Z0 = [0 0 1]';
Z1 = T01(1:3,3);
Z2 = T02(1:3,3);

t0 = [0 0 0]';
t3 = T03(1:3,4);

rho_1 = 1; % Rotacional
rho_2 = 0; % Prismatico
rho_3 = 0; % Prismatico

% Calcular el Jacobiano angular (Jw)
Jw = [rho_1*Z0 rho_2*Z1 rho_3*Z2];

% Construir el Jacobiano clásico concatenando el Jacobiano lineal y angular
Jc = simplify([Jv; Jw])

Jv = [cross(Z0,t3-t0) Z1 Z2];
Jw = [Z0 zeros(3,1) zeros(3,1)];

% Simplificar el Jacobiano geométrico
Jg = simplify([Jv; Jw])
