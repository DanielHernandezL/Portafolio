clear all
close all
clc

%tabla DH
L1 = Revolute('a',0.033,'alpha',pi/2,'d',0.2555,'offset',0);
L2 = Revolute('a',0.155,'alpha',0,'d',0,'offset',pi/2);
L3 = Revolute('a',0.1348,'alpha',0,'d',0,'offset',0);
L4 = Revolute('a',0,'alpha',pi/2,'d',0,'offset',pi/2);
L5 = Revolute('a',0,'alpha',0,'d',0.1936,'offset',0);

bot = SerialLink([L1 L2 L3 L4 L5],'name','KUKA');

%%
bot_s = Bot_youBot();

%% Home(Llevar a posición inicial)
qd = [0 0 pi/2 pi/4 pi/4]';

S = 5;
tic;
while toc<=S
    q = bot_s.Get_Joint_Position();
    
    qp = 0.5*(qd-q);
    
    bot_s.Set_Joint_Velocity(qp);
    pause(0.01)
end
%% Llevar a referencia

figure
q = bot_s.Get_Joint_Position();
bot.plot(q');
kp = diag([.5 .5 .5]);

Td = bot_s.ReferenceFrame_Pose();
td = Td(1:3,4);

S = 30;

%Defino mis vectores para graficar
xi_plot = zeros(1,S);
yi_plot = zeros(1,S);
zi_plot = zeros(1,S);
xd_plot = zeros(1,S);
yd_plot = zeros(1,S);
zd_plot = zeros(1,S);
qp_plot = zeros(5,S);
q_plot = zeros(5,S);
j = 1;
t = 0:0.01:S;

while toc<=S
    q = bot_s.Get_Joint_Position();
    Ti = bot.fkine(q);
    ti = Ti.t;
    v = td - ti;
    
    %Obtengo mis matrices de transformación
    T01 = bot.A(1:1,q);
    T02 = bot.A(1:2,q);
    T03 = bot.A(1:3,q);
    T04 = bot.A(1:4,q);
    T05 = bot.A(1:5,q);

    txyz = T05.t;
    
    %Obtengo tx, ty, y tz
    tx = txyz(1);
    ty = txyz(2);
    tz = txyz(3);
    
    r1 = T01.R;
    r2 = T02.R;
    r3 = T03.R;
    r4 = T04.R;

    %Obtengo z0, z1, z2, z3 y z4
    z0 = [0 0 1]';
    z1 = r1(1:3,3);
    z2 = r2(1:3,3);
    z3 = r3(1:3,3);
    z4 = r4(1:3,3);

    %Obtengo t1, t2, t3, t4 y t5
    t0 = [0 0 0]';
    t1 = T01.t;
    t2 = T02.t;
    t3 = T03.t;
    t4 = T04.t;
    t5 = T05.t;
    
    Jv1 = cross(z0,(t5-t0));
    Jv2 = cross(z1,(t5-t1));
    Jv3 = cross(z2,(t5-t2));
    Jv4 = cross(z3,(t5-t3));
    Jv5 = cross(z4,(t5-t4));

    Ji = [Jv1 Jv2 Jv3 Jv4 Jv5];


    %J = bot.jacob0(q);
    qp = pinv(Ji) * kp * v;
    

    %se guarda para graficar
    xi_plot(1,j) = ti(1);
    yi_plot(1,j) = ti(2);
    zi_plot(1,j) = ti(3);
    xd_plot(1,j) = td(1);
    yd_plot(1,j) = td(2);
    zd_plot(1,j) = td(3);
    qp_plot(:,j) = qp;
    q_plot(:,j) = q;
    j = j + 1;


    bot_s.Set_Joint_Velocity(qp);
    pause(0.01)
end


%% Para simulacion
bot_s.Stop_Simulation()


%% Se muestran las graficas
% figure
% hold on
% grid on
% plot(q_plot(1,:));
% plot(q_plot(2,:));
% plot(q_plot(3,:));
% plot(q_plot(4,:));
% plot(q_plot(5,:));
% xlabel('Tiempo (s)');
% ylabel('Posicion (rad)');
% title('Vector de Posicion (q)');
% legend({'theta_1','theta_2','theta_3','theta_4','theta_5'});
% 
% figure
% hold on
% grid on
% plot(qp_plot(1,:));
% plot(qp_plot(2,:));
% plot(qp_plot(3,:));
% plot(qp_plot(4,:));
% plot(qp_plot(5,:));
% xlabel('Tiempo (s)');
% ylabel('Velocidad (rad/s)');
% title('Vector de Velocidad (qp)');
% legend({'theta_1','theta_2','theta_3','theta_4','theta_5'});
% 
% figure
% hold on
% grid on
% plot(xd_plot,'g-','LineWidth', 2, 'MarkerSize', 4);
% plot(xi_plot,'k-','LineWidth', 2, 'MarkerSize', 4);
% xlabel('Tiempo (s)');
% ylabel('Posicion');
% title('Posicion en x');
% legend('xd','xi');
% 
% figure
% hold on
% grid on
% plot(yd_plot,'g-','LineWidth', 2, 'MarkerSize', 4);
% plot(yi_plot,'k-','LineWidth', 2, 'MarkerSize', 4);
% xlabel('Tiempo (s)');
% ylabel('Posicion (m)');
% title('Posicion en y');
% legend('yd','yi');
% figure
% hold on
% grid on
% plot(zd_plot,'g-','LineWidth', 2, 'MarkerSize', 4);
% plot(zi_plot,'k-','LineWidth', 2, 'MarkerSize', 4);
% xlabel('Tiempo (s)');
% ylabel('Posicion (m)');
% title('Posicion en z');
% legend('zd','z');