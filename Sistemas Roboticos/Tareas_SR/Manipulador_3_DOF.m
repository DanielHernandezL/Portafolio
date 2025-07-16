clear all
%close all
clc

% Punto deseado 
Tx = 0.50;
Ty = 0.25;
Tz = 0.50;

% Articulaciones
d1 = 0.35;
d2 = 0.0;
d3 = 0.35;

Theta_1 = atan2(Ty,Tx);
Theta_2 = atan2((Tz-d1), sqrt(Tx^2+Ty^2));
d_3 = sqrt(Tx^2+Ty^2+(Tz-d1)^2)-d3;

% Vector de coordenadas generalizadas
q = [Theta_1 Theta_2 d_3]'

% T = DH (a,alpha,d,theta)
T01 = DH(0.0, pi/2,     0.35,q(1));
T12 = DH(0.0,-pi/2,      0.0,q(2)-pi/2);
T23 = DH(0.0,  0.0,q(3)+0.35, 0.0);

T02=T01*T12*T23

cla
Dibujar_Manipulador({T01 T12 T23},{'RRP'},0.04);

% Agregar punto en la coordenada (Tx, Ty, Tz)
hold on
plot3(Tx, Ty, Tz, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
hold off

%Limites inferiores y superiores al graficar
xlim([-0.1 0.5]);
ylim([-0.1 0.5]);
zlim([-0.1 0.9]);
xlabel('x')
ylabel('y')
zlabel('z')
view([45 10])

%% Función DH
function T = DH (a,alpha,d,theta)
    T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
         sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
         0 sin(alpha) cos(alpha) d; 0 0 0 1];
end
