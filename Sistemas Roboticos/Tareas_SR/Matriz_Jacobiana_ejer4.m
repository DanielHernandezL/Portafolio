clear all
close all
clc

% Parámetros DH del manipulador antropomórfico
a_1 = 0.35;
a_2 = 0.35;
a_3 = 0.25;

% Definir las variables simbólicas
syms theta_1 theta_2 theta_3 real

% Definir las matrices de transformación homogénea según la tabla DH
T01 = [cos(theta_1), -sin(theta_1), 0, a_1*cos(theta_1);
       sin(theta_1),  cos(theta_1), 0, a_1*sin(theta_1);
       0,                 0,        1,      0;
       0,                 0,        0,      1];
   
T12 = [cos(theta_2), -sin(theta_2), 0, a_2*cos(theta_2);
       sin(theta_2),  cos(theta_2), 0, a_2*sin(theta_2);
       0,                 0,        1,      0;
       0,                 0,        0,      1];

T23 = [cos(theta_3), -sin(theta_3), 0, a_3*cos(theta_3);
       sin(theta_3),  cos(theta_3), 0, a_3*sin(theta_3);
       0,                 0,        1,      0;
       0,                 0,        0,      1];

% Transformaciones compuestas
T02 = simplify(T01 * T12);
T03 = simplify(T02 * T23);

% Extraer la posición del efector final
x = T03(1,4);
y = T03(2,4);
z = T03(3,4);

% Velocidad lineal
Jv = [diff(x, theta_1), diff(x, theta_2), diff(x, theta_3);
      diff(y, theta_1), diff(y, theta_2), diff(y, theta_3);
      diff(z, theta_1), diff(z, theta_2), diff(z, theta_3)];

% Puntos de interés para el Jacobiano geométrico
Z0 = [0; 0; 1];
Z1 = T01(1:3, 3);
Z2 = T02(1:3, 3);

t0 = [0; 0; 0];
t1 = T01(1:3, 4);
t2 = T02(1:3, 4);
t3 = T03(1:3, 4);

rho_1 = 1;  %rotacional
rho_2 = 1;  %rotacional
rho_3 = 1;  %rotacional

Jw = [rho_1*Z0 rho_2*Z1 rho_3*Z2]
% Matriz clásica
Jc = simplify([Jv; Jw])
Jv_geom = [cross(Z0, t3 - t0), cross(Z1, t3 - t1), cross(Z2, t3 - t2)];
Jw = [Z0, Z1, Z2];
% Matriz Jacobiana completa
Jg = simplify([Jv_geom; Jw])


