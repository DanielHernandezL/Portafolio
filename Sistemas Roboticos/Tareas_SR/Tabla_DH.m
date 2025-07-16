clear all
% close all
clc


q = [0 0 0];

% (a,alpha,d,theta)
T01 = DH(0.0,0,0,q(1));
T12 = DH(0.0,0,0.0,q(2));
T23 = DH(0.0,0,0.0,q(3));


% T01 = [cos(q(1)) -sin(q(1)) 0 0.3*cos(q(1)); ...
%        sin(q(1)) cos(q(1)) 0 0.3*sin(q(1)); ... 
%        0 0 1 0; 0 0 0 1];
% 
% T12 = [cos(q(2)) -sin(q(2)) 0 0.3*cos(q(2)); ...
%        sin(q(2)) cos(q(2)) 0 0.3*sin(q(2)); ... 
%        0 0 1 0; 0 0 0 1];
% 
% T23 = [cos(q(3)) -sin(q(3)) 0 0.2*cos(q(3)); ...
%        sin(q(3)) cos(q(3)) 0 0.2*sin(q(3)); ... 
%        0 0 1 0; 0 0 0 1];



% T02 = T01*T12;
% T03 = T02*T23;
% 
% % T03 = T01*T12*T23;
% 
% cla
% Dibujar_Sistema_Referencia_3D(eye(4,4),'0')
% Dibujar_Sistema_Referencia_3D(T01,'1')
% Dibujar_Sistema_Referencia_3D(T02,'2')
% Dibujar_Sistema_Referencia_3D(T03,'3')
% 
% plot3(0,0,0,'ok','MarkerSize',12,'LineWidth',2)
% plot3(T01(1,4),T01(2,4),T01(3,4),'ok','MarkerSize',12,'LineWidth',2)
% plot3(T02(1,4),T02(2,4),T02(3,4),'ok','MarkerSize',12,'LineWidth',2)
% 
% line([0 T01(1,4)],[0 T01(2,4)],[0 T01(3,4)],'LineWidth',4,'color',[0 0 0])
% line([T01(1,4) T02(1,4)],[T01(2,4) T02(2,4)],[T01(3,4) T02(3,4)],'LineWidth',4,'color',[0 0 0])
% line([T02(1,4) T03(1,4)],[T02(2,4) T03(2,4)],[T02(3,4) T03(3,4)],'LineWidth',4,'color',[0 0 0])
% 

function T = DH (a,alpha,d,theta)
    T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
         sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
         0 sin(alpha) cos(alpha) d; 0 0 0 1];
end