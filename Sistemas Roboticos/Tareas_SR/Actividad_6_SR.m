clear all
close all
clc

 syms theta_1 theta_2 theta_3 real

% Definir las longitudes de los enlaces del robot
a_1 = 0;
a_2 = 0.30;
a_3 = 0.25;
d_1 = 0.35;
 

%Tablas de transformación homogenea del manipulador antropomorfico 
T01 = [cos(theta_1) 0 sin(theta_1) a_1*cos(theta_1); sin(theta_1) 0 -cos(theta_1) a_1*sin(theta_1); 0 1 0 d_1; 0 0 0 1];
T12 = [cos(theta_2) -sin(theta_2) 0 a_2*cos(theta_2); sin(theta_2) cos(theta_2) 0 a_2*sin(theta_2); 0 0 1 0; 0 0 0 1];
T23 = [cos(theta_3) -sin(theta_3) 0 a_3*cos(theta_3); sin(theta_3) cos(theta_3) 0 a_3*sin(theta_3); 0 0 1 0; 0 0 0 1];

% Multiplicamos las matrices de transformación para obtener las transformaciones completas
T02 = simplify(T01 * T12);
T03 = simplify(T02 * T23);

x = T03(1,4);
y = T03(2,4);
z = T03(3,4);

% Calcular el Jacobiano lineal (Jv) usando las derivadas parciales de x, y, z respecto a theta_1, theta_2 y theta_3
Jv = [diff(x,theta_1) diff(x,theta_2) diff(x,theta_3); diff(y,theta_1) diff(y,theta_2) diff(y,theta_3); diff(z,theta_1) diff(z,theta_2) diff(z,theta_3)];

Z0 = [0 0 1]';
Z1 = T01(1:3,3);
Z2 = T02(1:3,3);

t0 = [0 0 0]';
t1 = T01(1:3,4);
t2 = T02(1:3,4);
t3 = T03(1:3,4);

rho_1 = 1;
rho_2 = 1;
rho_3 = 1;

% Calcular el Jacobiano angular (Jw)
Jw = [rho_1*Z0 rho_2*Z1 rho_3*Z2];

% Construir el Jacobiano clásico concatenando el Jacobiano lineal y angular
Jc = simplify([Jv; Jw])

Jv = [cross(Z0,t3-t0) cross(Z1,t3-t1) cross(Z2,t3-t2)];
Jw = [Z0 Z1 Z2];

% Simplificar el Jacobiano geométrico
Jg = simplify([Jv; Jw])
