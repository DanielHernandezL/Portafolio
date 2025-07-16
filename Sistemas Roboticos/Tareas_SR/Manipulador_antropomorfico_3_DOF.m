clear all
%close all
clc

% Punto deseado 
Tx = -0.10;
Ty = 0.30;
Tz = 0.40;

% Articulaciones
d1 = 0.35;
a2 = 0.30;
a3 = 0.25;

%Cinematica inversa
Theta_1 = atan2(Ty,Tx);
Theta_3 = -acos((Tx^2+Ty^2+(Tz-d1)^2-a2^2-a3^2)/(2*a2*a3));
Theta_2 = atan((Tz-d1)/sqrt(Tx^2+Ty^2))-asin((a3*sin(Theta_3))/sqrt(Tx^2+Ty^2+(Tz-d1)^2));

% Vector de coordenadas generalizadas
q = [Theta_1 Theta_2 Theta_3]'

% T = DH (a,alpha,d,theta)
T01 = DH( 0.0,pi/2,0.35, q(1));
T12 = DH(0.30, 0.0, 0.0, q(2));
T23 = DH(0.25, 0.0, 0.0, q(3));

T02=T01*T12*T23

cla
Dibujar_Manipulador({T01 T12 T23},{'RRR'},0.04);

% Agregar punto en la coordenada (Tx, Ty, Tz)
hold on
plot3(Tx, Ty, Tz, 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
hold off

%Limites inferiores y superiores al graficar
xlim([-0.1 0.5]);
ylim([-0.1 0.5]);
zlim([-0.1 0.95]);
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
