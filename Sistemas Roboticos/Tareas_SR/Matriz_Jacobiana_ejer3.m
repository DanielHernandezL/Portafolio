close all
clear all
clc

a_1 = 0.35;
a_2 = 0.35;
a_3 = 0.25;

Jacob = @(q) [-a_2*sin(q(1) + q(2)) - a_1*sin(q(1)) - a_3*sin(q(1) + q(2) + q(3)), - a_2*sin(q(1) + q(2)) - a_3*sin(q(1) + q(2) + q(3)), -a_3*sin(q(1) + q(2) + q(3)); ...
a_2*cos(q(1) + q(2)) + a_1*cos(q(1)) + a_3*cos(q(1) + q(2) + q(3)), a_2*cos(q(1) + q(2)) + a_3*cos(q(1) + q(2) + q(3)), a_3*cos(q(1) + q(2) + q(3)); ...
0, 0, 0; 0, 0, 0; 0, 0, 0; 1, 1, 1];

T01 = @(theta_1) DH(a_1,0,0,theta_1);
T12 = @(theta_2) DH(a_2,0,0,theta_2);
T23 = @(theta_3) DH(a_3,0,0,theta_3);

dt = 0.05;
S = 2;

q = [-pi/4 pi/4 pi/4]';

% T03 = T01(q(1))*T12(q(2))*T23(q(3));

for t=dt:dt:S
xp = [0.2 0.0 0.0]';

J = Jacob(q);
Jv = J(1:3,:);

qp = pinv(Jv)*xp;

q = q + qp*dt;

cla
Dibujar_Manipulador({T01(q(1)) T12(q(2)) T23(q(3))},{'RRR'},0.05);
view([-90 90])
xlabel('x')
ylabel('y')
axis([-1 1 -1 1 -0.2 0.8])
drawnow
end

%%
function T = DH (a,alpha,d,theta)
T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
0 sin(alpha) cos(alpha) d; 0 0 0 1];
end