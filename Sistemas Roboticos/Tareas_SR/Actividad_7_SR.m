close all
clear all
clc

% Parámetros de control y del manipulador
K = diag([0.6 0.6 0.6]);  % Ganancias
dt = 0.1;

% Tiempo total para completar la trayectoria
S = 8; 
px = -0.4; 
py = 0.3;
pz = 0.01;

% Posición deseada del efector final
td = [px; py; pz]; 
xc = 0.20;
yc = 0.20;
k = 0.4;
r = 0.15;

% Posición inicial de las articulaciones
q = [pi/4; pi/4; 0.1; pi/4]; 

q_plot = [];
qp_plot = [];
t_plot = [];
x_plot = [];
xd_plot = [];

% Bucle para la planificación de trayectoria y control
for t = dt:dt:S
    
    % Calculando la posición y velocidad deseada en la trayectoria circular
    xd = xc + r*cos(k*t);
    yd = yc + r*sin(k*t);
    zd = 0.1;
    td = [xd yd zd]';

    %Velocidad deseada
    xdp = -r*k*sin(k*t);
    ydp = r*k*cos(k*t);
    tdp = [xdp ydp 0]';
    
    % Tablas de transformaciones homogéneas basadas en los parámetros DH
     T01 = [cos(q(1)), -sin(q(1)), 0, 0.4*cos(q(1));
            sin(q(1)),  cos(q(1)), 0, 0.4*sin(q(1));
                    0,          0, 1,           0.5;
                    0,          0, 0,            1];
    T12 = [cos(q(2)),  sin(q(2)),  0, 0.5*cos(q(2));
           sin(q(2)), -cos(q(2)),  0, 0.5*sin(q(2));
                   0,          0, -1,             0;
                   0,          0,  0,            1];

    T23 = [1, 0, 0,        0;
           0, 1, 0,        0;
           0, 0, 1, q(3)+0.4;
           0, 0, 0,       1];

    T34 = [cos(q(4)), -sin(q(4)), 0,   0;
           sin(q(4)),  cos(q(4)), 0,   0;
                   0,          0, 1, 0.1;
                   0,          0, 0,   1];

    % Cinematica directa
    T04 = T01 * T12 * T23 * T34;
    
    % Planificación de trayectoria
    ti = T04(1:3,4);
    xf = td;
    tf = S;
    T = [1 0 -(3/tf^2) 2/tf^3; 0 1 -(2/tf) 1/tf^2; 0 0 3/tf^2 -(2/tf^3); 0 0 -(1/tf) 1/tf^2];
    A = [ti zeros(3,1) td zeros(3,1)] * T;
    TX_d = A * [1 0; t 1; t^2 2*t; t^3 3*t^2];
    tdp = TX_d(:,2);

    % Cálculo del Jacobiano y error
    J = Jacobiano(q);
    Jv = J(1:3,:); 
    e = td - ti;
    Ji = pinv(Jv);
    qp = Ji * (tdp + K * e);
    q = q + qp * dt;

    q_plot = [q_plot, q];
    qp_plot = [qp_plot, qp];
    t_plot = [t_plot, t];
    x_plot = [x_plot, ti];
    xd_plot = [xd_plot, td];

    % Dibujar el manipulador
    cla;
    Dibujar_Manipulador({T01, T12, T23, T34}, {'RRPR'}, 0.05);
    plot3(px, py, pz, 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
    plot3(ti(1), ti(2), ti(3), 'bo', 'MarkerSize', 3);
    plot3(x_plot(1,:), x_plot(2,:), x_plot(3,:), 'b-', 'LineWidth', 1.5);
    xlabel('x');
    ylabel('y');
    drawnow;
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
     t_plot, xd_plot(1,:), 'k--', t_plot, xd_plot(2,:), 'y--', t_plot, xd_plot(3,:), 'c--');
xlabel('Tiempo');
ylabel('Posición del efector final');
legend('Actual x', 'Actual y', 'Actual z', 'X deseada', 'Y deseada', 'Z deseada');

%% Jacobiano para el manipulador SCARA
function J = Jacobiano(q)
    theta1 = q(1);
    theta2 = q(2);
    J = [-sin(theta1 + theta2)/2 - (2*sin(theta1))/5, -sin(theta1 + theta2)/2,  0,  0;
          cos(theta1 + theta2)/2 + (2*cos(theta1))/5,  cos(theta1 + theta2)/2,  0,  0;
                                                   0,                       0, -1,  0;
                                                   0,                       0,  0,  0;
                                                   0,                       0,  0,  0;
                                                   1,                       1,  0, -1];
end