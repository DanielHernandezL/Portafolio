clear all
close all
clc

% Parámetros DH del manipulador antropomórfico

% Definir las variables simbólicas
 syms theta_1 theta_2 theta_3 real

% Definir las matrices de transformación homogénea según la tabla DH
T01 = [cos(theta_1),  0, sin(theta_1), 0;
       sin(theta_1),  0, -cos(theta_1), 0;
       0,             1,        0,     d_1;
       0,             0,        0,      1];

T12 = [cos(theta_2), -sin(theta_2), 0, a_2*cos(theta_2);
       sin(theta_2), cos(theta_2),  0, a_2*sin(theta_2);
       0,            0,             1, 0;
       0,            0,             0, 1];

T23 = [cos(theta_3), -sin(theta_3), 0, a_3*cos(theta_3);
       sin(theta_3), cos(theta_3),  0, a_3*sin(theta_3);
       0,            0,             1, 0;
       0,            0,             0, 1];

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


% Vector de coordenadas generalizadas
%q = [theta_1 theta_2 theta_3]'
%
% % T = DH (a,alpha,d,theta)
% T01 = DH(0.0 ,pi/2,0.35,q(1));
% T12 = DH(0.30,0.0,0.0 ,q(2));
% T23 = DH(0.25,0.0,0.0 ,q(3));
% 
% 
% %% Función DH
% function T = DH (a,alpha,d,theta)
%     T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
%          sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
%          0 sin(alpha) cos(alpha) d; 0 0 0 1];
% end