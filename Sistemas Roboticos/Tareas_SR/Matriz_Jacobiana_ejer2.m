clear all
close all
clc

% Parámetros DH del manipulador antropomórfico
d_1 = 0.35; % Valor de d_1 según la tabla

% Definir las variables simbólicas
syms theta_1 d_2 d_3 real

% Definir las matrices de transformación homogénea según la tabla DH

T01 = [cos(theta_1), -sin(theta_1),  0,  0;
       sin(theta_1),  cos(theta_1),  0,  0;
       0,             0,            1, d_1;
       0,             0,            0,  1];
   
T12 = [1,  0,            0,            0;
       0,  0,           -1,            0;
       0,  1,            0,           d_2;
       0,  0,            0,            1];

T23 = [1,  0,            0,            0;
       0,  1,            0,            0;
       0,  0,            1,           d_3;
       0,  0,            0,            1];

% Transformaciones compuestas
T02 = simplify(T01 * T12);
T03 = simplify(T02 * T23);

% Extraer la posición del efector final
x = T03(1,4);
y = T03(2,4);
z = T03(3,4);

% Velocidad lineal
Jv = [diff(x, theta_1), diff(x, d_2), diff(x, d_3);
      diff(y, theta_1), diff(y, d_2), diff(y, d_3);
      diff(z, theta_1), diff(z, d_2), diff(z, d_3)];

% Puntos de interés para el Jacobiano geométrico
Z0 = [0; 0; 1];
Z1 = T01(1:3, 3);
Z2 = T02(1:3, 3);

t0 = [0; 0; 0];
t3 = T03(1:3, 4);

rho_1 = 1; %rotacional
rho_2 = 0; %prismatica
rho_3 = 0; %prismatica

% Jacobiano angular
Jw = [rho_1*Z0, rho_2*Z1, rho_3*Z2]

% Matriz clásica Jacobiana
Jc = simplify([Jv; Jw])

% Parte geométrica del Jacobiano
Jv_geom = [cross(Z0, t3 - t0), Z1, Z2];
Jw_geom = [Z0, zeros(3,1), zeros(3,1)];

% Matriz Jacobiana completa
Jg = simplify([Jv_geom; Jw_geom])
