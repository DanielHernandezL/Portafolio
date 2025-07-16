clear all
%close all
clc

% Punto deseado 
Tx = 0.4;
Ty = 0.4;

% Articulaciones
a1 = 0.35;
a2 = 0.25;

%Cinematica inversa
Theta_2 = -acos((Tx^2+Ty^2-a1^2-a2^2)/(2*a1*a2));
Theta_1 = atan2(Ty,Tx)-asin((a2*sin(Theta_2)/(sqrt(Tx^2+Ty^2))));

% Vector de coordenadas generalizadas
q = [Theta_1 Theta_2]'

% T = DH (a,alpha,d,theta)
T01 = DH(0.35,0.0,0.0,q(1));
T12 = DH(0.25,0.0,0.0,q(2));


T02=T01*T12

cla
Dibujar_Manipulador({T01 T12},{'RR'},0.04);

% Agregar punto en la coordenada (Tx, Ty)
hold on
plot(Tx, Ty, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
hold off

%Limites inferiores y superiores al graficar
xlim([-0.5 0.5]);
ylim([-0.1 0.5]);
zlim([-0.2 0.2]);
xlabel('x')
ylabel('y')
zlabel('z')
view([0 90])

%% Función DH
function T = DH (a,alpha,d,theta)
    T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
         sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
         0 sin(alpha) cos(alpha) d; 0 0 0 1];
end