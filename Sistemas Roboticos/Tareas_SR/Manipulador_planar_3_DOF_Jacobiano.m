clear all
close all
clc

 syms theta_1 theta_2 theta_3 a1 a2 real

% Definir las longitudes de los enlaces del robot
%a1 = 0.35;
%a2 = 0.35;
%a_3 = 0.25; 

%Tablas de transformación homogenea del manipulador planar 
% T01 = [cos(theta_1) -sin(theta_1) 0 a_1*cos(theta_1);sin(theta_1) cos(theta_1) 0 a_1*sin(theta_1);0 0 1 0;0 0 0 1];
% T12 = [cos(theta_2) -sin(theta_2) 0 a_2*cos(theta_2);sin(theta_2) cos(theta_2) 0 a_2*sin(theta_2);0 0 1 0;0 0 0 1];
% T23 = [cos(theta_3) -sin(theta_3) 0 a_3*cos(theta_3);sin(theta_3) cos(theta_3) 0 a_3*sin(theta_3);0 0 1 0;0 0 0 1];
T01= [cos(theta_1) -sin(theta_1)*cos(0)  sin(theta_1)*sin(0) a1*cos(theta_1);
      sin(theta_1)  cos(theta_1)*cos(0) -cos(theta_1)*sin(0) a1*sin(theta_1);
              0            sin(0)            cos(0)            0;
              0                0                  0            1];
T12= [cos(theta_2) -sin(theta_2)*cos(0)  sin(theta_2)*sin(0) a2*cos(theta_2);
      sin(theta_2)  cos(theta_2)*cos(0) -cos(theta_2)*sin(0) a2*sin(theta_2);
              0            sin(0)            cos(0)            0;
              0                0                  0            1];
T02 = T01 * T12;

% Multiplicamos las matrices de transformación para obtener las transformaciones completas
T02 = simplify(T01*T12);
%T03 = simplify(T02*T23);

x = T02(1,4);
y = T02(2,4);
z = T02(3,4);

% Calcular el Jacobiano lineal (Jv) usando las derivadas parciales de x, y, z respecto a theta_1, theta_2 y theta_3
%Jv = [diff(x,theta_1) diff(x,theta_2) diff(x,theta_3); diff(y,theta_1) diff(y,theta_2) diff(y,theta_3); diff(z,theta_1) diff(z,theta_2) diff(z,theta_3)];
Jv = [diff(x,theta_1) diff(x,theta_2); diff(y,theta_1) diff(y,theta_2); diff(z,theta_1) diff(z,theta_2)];

Z0 = [0 0 1]';
Z1 = T01(1:3,3);
%Z2 = T02(1:3,3);

t0 = [0 0 0]';
t1 = T01(1:3,4);
t2 = T02(1:3,4);
%t3 = T03(1:3,4);

rho_1 = 1; % Rotacional
rho_2 = 1; % Rotacional
%rho_3 = 1; % Rotacional

% Calcular el Jacobiano angular (Jw)
Jw = [rho_1*Z0 rho_2*Z1];

% Construir el Jacobiano clásico concatenando el Jacobiano lineal y angular
Jc = simplify([Jv; Jw]);

Jv = [cross(Z0,t2-t0) cross(Z1,t2-t1)];
Jw = [Z0 Z1];

% Simplificar el Jacobiano geométrico
Jg = simplify([Jv; Jw]);
