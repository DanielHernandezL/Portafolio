close all
clear all
clc

%% Cinematica Directa Scara
%T = DH(a,alpha,d,theta)
T01 = @(theta_1) [cos(theta_1), -sin(theta_1), 0, a_1*cos(theta_1);
       sin(theta_1),  cos(theta_1), 0, a_1*sin(theta_1);
                  0,             0, 1,              d_1;
                  0,             0, 0,                1];

T12 = @(theta_2) [cos(theta_2),  sin(theta_2),  0, a_2*cos(theta_2);
       sin(theta_2), -cos(theta_2),  0, a_2*sin(theta_2);
                  0,             0, -1,                0;
                  0,             0,  0,                1];

T23 = @(d3) [1, 0, 0, 0;
       0, 1, 0,        0;
       0, 0, 1, d3 + d_3;
       0, 0, 0,        1];

T34 = @(theta_4) [cos(theta_4), -sin(theta_4), 0,   0;
       sin(theta_4),  cos(theta_4), 0,   0;
                  0,             0, 1, d_4;
                  0,             0, 0,   1];
q = [pi/2 pi/4 0.1 pi/4]';
%% Jacobiano
K = diag([1 1 1]); %% Ganancias
% Ciclo
dt = 0.1;
S = 10;
px = 0.4;
py = -0.2;
pz = 0.01;
td = [px py pz]'; % puede cambiar mas adelante

%
q_plot = [];
qp_plot = [];
t_plot = [];
x_plot = [];
xd_plot = [];

for t = dt:dt:S
    T01 = DH(0.4, 0 , 0.5 , q(1));
    T12 = DH(0.5 , pi , 0 , q(2));
    T23 = DH(0, 0 , q(3) + 0.4 , 0);
    T34 = DH(0 , 0 , 0.1 , q(4));

    T04 = T01*T12*T23*T34;
    
    %PLANIFICACION DE TRAYECTORIAS 
    ti = T04(1:3,4);
    xf = td;
    tf = S;
    T = [1 0 -(3/tf^2) 2/tf^3;0 1 -(2/tf) 1/tf^2;0 0 3/tf^2 -(2/tf^3);0 0 -(1/tf) 1/tf^2];
    A = [ti zeros(3,1) xf zeros(3,1)]*T;
    TXD = A*[1 0;t 1;t^2 2*t;t^3 3*t^2];
    tdp = TXD(:,2);

    J = Jacobiano(q);
    Jv = J(1:3,:); 
    e = td-ti;
    qp = pinv(Jv)*(tdp + K*e);
    q = q+qp*dt;

    q_plot = [q_plot, q]; % Posiciones conjuntas
    qp_plot = [qp_plot, qp]; % Velocidades conjuntas
    t_plot = [t_plot, t]; % Tiempo
    x_plot = [x_plot, ti]; % Posición real del efector final
    xd_plot = [xd_plot, td]; % Posición deseada del efector final

    cla
    Dibujar_Manipulador({T01,T12,T23,T34},{'RRPR'},0.05);
    plot3(px,py,pz, 'o-', 'Color', 'r', 'LineWidth', 0.8, 'MarkerSize', 6);
    xlabel('x')
    ylabel('y')
    axis([-0.8 0.8 -0.8 0.8 -0.2 0.8])
    drawnow
end

figure;
plot(t_plot, q_plot(1,:), 'r', t_plot, q_plot(2,:), 'g', t_plot, q_plot(3,:), 'b', t_plot, q_plot(4,:), 'm');
title('Posición articular vs tiempo');
xlabel('Tiempo');
ylabel('Posición');
legend('q1', 'q2', 'q3', 'q4');

figure;
plot(t_plot, qp_plot(1,:), 'r', t_plot, qp_plot(2,:), 'g', t_plot, qp_plot(3,:), 'b', t_plot, qp_plot(4,:), 'm');
title('Velocidad articular vs tiempo');
xlabel('Tiempo');
ylabel('Velocidad');
legend('qp1', 'qp2', 'qp3', 'qp4');

figure;
hold on;
grid on;
plot(t_plot, x_plot(1,:), 'r', t_plot, x_plot(2,:), 'g', t_plot, x_plot(3,:), 'b', ...
     t_plot, xd_plot(1,:), 'r--', t_plot, xd_plot(2,:), 'g--', t_plot, xd_plot(3,:), 'b--');
xlabel('Tiempo');
ylabel('Posición del efector final');
legend('Actual x', 'Actual y', 'Actual z', 'X deseada', 'Y deseada', 'Z deseada');

%%
function T = DH(a,alpha,d,theta)
T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
0 sin(alpha) cos(alpha) d; 0 0 0 1];
end
%% Calculamos el Jacobiano del scara de forma simbolica y definimos una funcion
syms a1 d1 a2 d3 d4 theta1 theta2 theta4 alpha2
%T = DH(a,alpha,d,theta)
q = [0 0 0 0]';
T01 = DH(a1, 0 , d1 , theta1);
T12 = DH(a2 , alpha2 , 0 , theta2);
T23 = DH(0, 0 , d3 , 0);
T34 = DH(0 , 0 , d4 , theta4);

T02 = T01*T12;
T03 = T02*T23;
T04 = T03*T34;

Z0 = [0 0 1]';
Z1 = T01(1:3,3);
Z2 = T02(1:3,3);
Z3 = T03(1:3,3);

t0 = [0 0 0]';
t1 = T01(1:3,4);
t2 = T02(1:3,4);
t3 = T03(1:3,4);
t4 = T04(1:3,4);

Jv1 = cross(Z0,(t4-t0));
Jv2 = cross(Z1,(t4-t1));
Jv3 = Z2;
Jv4 = cross(Z3,(t4-t3));

Jw1 = Z0;
Jw2 = Z1;
Jw3 = [0 0 0]';
Jw4 = Z3;

JS = simplify([Jv1 Jv2 Jv3 Jv4;Jw1 Jw2 Jw3 Jw4]);

JSubs = subs(JS,[a1 d1 a2 d4 alpha2],[0.4 0.5 0.5 0.1 pi]) %% Cambiar valores si se modifica arriba

function  J = Jacobiano(q)
theta1 = q(1);
theta2 = q(2);
J = [- sin(theta1 + theta2)/2 - (2*sin(theta1))/5, -sin(theta1 + theta2)/2,  0,  0;
       cos(theta1 + theta2)/2 + (2*cos(theta1))/5,  cos(theta1 + theta2)/2,  0,  0;
                                                0,                       0, -1,  0;
                                                0,                       0,  0,  0;
                                                0,                       0,  0,  0;
                                                1,                       1,  0, -1];

end