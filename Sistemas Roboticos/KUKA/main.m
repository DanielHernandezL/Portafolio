clear all
close all
clc
% Parámetros del KUKA
d1 = 0.2555; a1 = 0.033; a2 = 0.155; a3 = 0.1348; d5 = 0.1936;

bot = Bot_youBot();

dt = 0.05;
S = 20;
K = diag([1 1 1]); % Ganancías

qp_plot = [];
q_plot = [];
x_plot = [];
xd_plot = [];
t_plot = [];

for t = dt:dt:S

    Td = bot.ReferenceFrame_Pose();
    q = bot.Get_Joint_Position();

    %% Matrices de transformación homogénea
    T01 = [cos(q(1)), 0,  sin(q(1)), (33*cos(q(1)))/1000;
           sin(q(1)), 0, -cos(q(1)), (33*sin(q(1)))/1000;
                   0, 1,         0,           511/2000;
                   0, 0,         0,                  1];

    T12 = [cos(q(2) + pi/2), -sin(q(2) + pi/2), 0, (31*cos(q(2) + pi/2))/200;
           sin(q(2) + pi/2),  cos(q(2) + pi/2), 0, (31*sin(q(2) + pi/2))/200;
                           0,                0, 1,                        0;
                           0,                0, 0,                        1];

    T23 = [cos(q(3)), -sin(q(3)), 0, (337*cos(q(3)))/2500;
           sin(q(3)),  cos(q(3)), 0, (337*sin(q(3)))/2500;
                   0,         0, 1,                   0;
                   0,         0, 0,                   1];

    T34 = [cos(q(4) - pi/2),  0, -sin(q(4) - pi/2), 0;
           sin(q(4) - pi/2),  0,  cos(q(4) - pi/2), 0;
                          0, -1,                 0, 0;
                          0,  0,                 0, 1];

    T45 = [cos(q(5)), -sin(q(5)), 0,       0;
           sin(q(5)),  cos(q(5)), 0,       0;
                   0,         0,  1, 121/625;
                   0,         0,  0,       1];

    %% Cinemática directa
    T02 = T01 * T12;
    T03 = T02 * T23;
    T04 = T03 * T34;
    T05 = T04 * T45;
    xi = T05(1:3,4);
    x_plot = [x_plot; xi'];  % Almacena la posición en cada iteración
    xf = Td(1:3,4);
    xd_plot = [xd_plot; xf'];  % Almacena la posición deseada en cada iteración

    %% Jacobiano
    t0 = [0 0 0]';
    t1 = T01(1:3,4);
    t2 = T02(1:3,4);
    t3 = T03(1:3,4);
    t4 = T04(1:3,4);
    t5 = T05(1:3,4);

    Z0 = [0 0 1]';
    Z1 = T01(1:3,3);
    Z2 = T02(1:3,3);
    Z3 = T03(1:3,3);
    Z4 = T04(1:3,3);
    Z5 = T05(1:3,3);

    Jv1 = cross(Z0, (t5 - t0));
    Jv2 = cross(Z1, (t5 - t1));
    Jv3 = cross(Z2, (t5 - t2));
    Jv4 = cross(Z3, (t5 - t3));
    Jv5 = cross(Z4, (t5 - t4));

    Jw1 = Z0;
    Jw2 = Z1;
    Jw3 = Z2;
    Jw4 = Z3;
    Jw5 = Z4;

    J = [Jv1 Jv2 Jv3 Jv4 Jv5; Jw1 Jw2 Jw3 Jw4 Jw5];

    %% Planificación de trayectoria
    tf = S;
    T = [1 0 -(3/tf^2) 2/tf^3; 0 1 -(2/tf) 1/tf^2; 0 0 3/tf^2 -(2/tf^3); 0 0 -(1/tf) 1/tf^2];
    A = [xi zeros(3,1) xf zeros(3,1)] * T;
    TX_d = A * [1 0; t 1; t^2 2*t; t^3 3*t^2];
    tdp = TX_d(:,2);

    %% Controlador
    Jv = J(1:3,:);
    e = xf - xi;
    Jinv = Jv' * inv(Jv * Jv');
    qp = Jinv * (tdp + K * e);
    q = q + qp * dt;

    bot.Set_Joint_Velocity(qp);
    bot.Simulation_Step();

    qp_plot = [qp_plot qp];
    t_plot = [t_plot t];
    q_plot = [q_plot q];

end

%% Detiene la simulación
bot.Stop_Simulation();

% Gráfica de las velocidades articulares
figure
hold on
grid on
plot(t_plot, qp_plot', 'LineWidth', 2)
legend('\theta_1', '\theta_2', '\theta_3', '\theta_4', '\theta_5')
xlabel('segundos')
ylabel('rad/s')
title('Velocidades articulares')

% Gráfica de la posición del efector final
figure
hold on
grid on
plot(t_plot, q_plot', 'LineWidth', 2)
legend('\theta_1', '\theta_2', '\theta_3', '\theta_4', '\theta_5')
xlabel('segundos')
ylabel('Posición (m)')
title('Posición del efector final en función del tiempo')

% Gráfica de posición actual vs. posición deseada
figure
hold on
grid on
plot(t_plot, x_plot(:,1), 'r', 'LineWidth', 2)
plot(t_plot, xd_plot(:,1), '--k', 'LineWidth', 2)
plot(t_plot, x_plot(:,2), 'g', 'LineWidth', 2)
plot(t_plot, xd_plot(:,2), '--y', 'LineWidth', 2)
legend('Posición actual y', 'Posición deseada y')
plot(t_plot, x_plot(:,3), 'b', 'LineWidth', 2)
plot(t_plot, xd_plot(:,3), '--c', 'LineWidth', 2)
legend('x', 'xd','y', 'yd','z', 'zd')
xlabel('segundos')
ylabel('Posición Z (m)')
title('Posición actual vs. posición deseada')
