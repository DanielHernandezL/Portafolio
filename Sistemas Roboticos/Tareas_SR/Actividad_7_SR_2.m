close all
clear all
clc

syms theta1 theta2 d theta4 real
%a_1 a_2 d_1 d_3 d_4
a_1 = 0.15;
a_2 = 0.4;
% Distancia maxima en a es 0.55
d_1 = 0.8;
d_3 = 0.3;
d_4 = 0.2;
% Distancia maxima en d es 0.9

% Parámetros del manipulador
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

% % Parámetros del manipulador
% T01 = @(theta) DH(0.15, 0, 0.8, theta);
% T12 = @(theta) DH(0.4, pi, 0, theta);
% T23 = @(d) DH(0, 0, d + 0.3, 0);
% T34 = @(theta) DH(0.0, 0, 0.2, theta);

% Control de ganancias
%K = diag([3.5; 3.5; 3.5; 3.5; 3.5; 3.5]); 
K = diag([2 2 2]);
alpha = 0;
Rd = [cos(alpha) sin(alpha) 0; sin(alpha) -cos(alpha) 0; 0 0 -1];
dt = 0.05;
S = 10;
% Posición inicial de las articulaciones
q = [pi/4; -pi/4; 0.1; pi/4]; 
z0 = [0 0 1]';
rho = [1, 1, 0, 1]; % 1 es rotacional, 0 prismática 

% Parámetros para la trayectoria circular
xc = 0.5; 
yc = 0.5;
r = 0.25;
k = 1; % Frecuencia de la trayectoria circular

% Variables de almacenamiento
q_plot = [];
qp_plot = [];
t_plot = [];
x_plot = [];
xd_plot = [];

% Recorra cada paso de tiempo para seguir la trayectoria
for t = dt:dt:S
    % Calcular posición y velocidad deseadas para trayectoria circular
    xd = xc + r * cos(k * t);
    yd = yc + r * sin(k * t);
    xdp = -k * r * sin(k * t);
    ydp = k * r * cos(k * t);
    
    td = [xd yd 0]'; % Z fijo en 0.4 como ejemplo
    td_dot = [xdp ydp 0]';

    % Cinemática directa para manipulador SCARA.
    T1 = T01(q(1));
    T2 = T1 * T12(q(2));
    T3 = T2 * T23(q(3));
    T4 = T3 * T34(q(4));
    t0 = [0 0 0]';
    t1 = T1(1:3,4); 
    t2 = T2(1:3,4);
    t3 = T3(1:3,4); 
    ti = T4(1:3,4); % Posición del efector final

    % Calculo jacobiano
    J = Jacob(q);
    Jv = J(1:3,:);

    % Error de posición y orientación.
    %v = td - ti; % Error de posicion
    Ri = T4(1:3,1:3);
    %w = 0.5 * (cross(Ri(:,1), Rd(:,1)) + cross(Ri(:,2), Rd(:,2))); % Error de orientación

    % Ley de control para calcular velocidades conjuntas.
    
    
    %e = [v w]'; % Use only positional error
    Ji = pinv(Jv); % Pseudoinverso del jacobiano
    qp = Ji * K*(td - ti);
    %qp = Ji * (td_dot + K * v); % Velocidades articulares deseadas, usando solo error de posición

    % Actualizar posiciones conjuntas
    q = q + qp * dt;

    % Almacenar datos para trazar
    q_plot = [q_plot, q]; % Posiciones conjuntas
    qp_plot = [qp_plot, qp]; % Velocidades conjuntas
    t_plot = [t_plot, t]; % Tiempo
    x_plot = [x_plot, ti]; % Posición real del efector final
    xd_plot = [xd_plot, td]; % Posición deseada del efector final

    % Manipulador de trazado en cada paso.
    cla
    hold on
    Dibujar_Manipulador({T01(q(1)), T12(q(2)), T23(q(3)), T34(q(4))}, {'RRPR'}, 0.05);
    plot3(td(1), td(2), td(3), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
    pause(0.01)
end

% Gráficas de resultados
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

%% Funciones auxiliares
function    A = Calcular_Coeficientes(td_init, td_final, s)
    % Genera coeficientes para la interpolación cúbica
    T = [1 0 -(3/tf^2) 2/tf^3; 0 1 -(2/tf) 1/tf^2; 0 0 3/tf^2 -(2/tf^3); 0 0 -(1/tf) 1/tf^2];
    A = [td_init; 0; td_final; 0]' * T;
end

function pos = Evaluar_Polinomio(A, t)
    pos = A * [1; t; t^2; t^3];
end

function vel = Evaluar_Polinomio_Derivada(A, t)
    vel = A * [0; 1; 2 * t; 3 * t^2];
end

% %% Función para transformación DH
% function T = DH(a, alpha, d, theta)
%     T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); 
%          sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); 
%          0 sin(alpha) cos(alpha) d; 0 0 0 1];
% end

function J = Jacob(q)
    % Parameters of the manipulator links
    a1 = 0.15; % Link 1 length
    a2 = 0.4;  % Link 2 length
    d3_offset = 0.3; % Offset for the prismatic joint

    % Jacobian matrix for RRPR manipulator with current configuration
    J = [-a2 * sin(q(1) + q(2)) - a1 * sin(q(1)), -a2 * sin(q(1) + q(2)), 0, 0;
          a2 * cos(q(1) + q(2)) + a1 * cos(q(1)),  a2 * cos(q(1) + q(2)), 0, 0;
          0,                                     0,                     1, 0;
          0,                                     0,                     0, 1];
end