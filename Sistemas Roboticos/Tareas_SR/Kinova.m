% clear all
% close all
% clc
% 
% N = 200;
% k = 0.1;
% Rd = diag([1 -1 1]);
% td = [0.3 0.3 0.30]';
% mu_plot = [];
% t_plot = [];
% 
% q = [0 -pi/4 pi/4 0 -pi/4 0]';
% for t = 1:N
%     % DH 
%     T01 = DH(0,pi/2,(0.1283+0.115),q(1));
%     T12 = DH(0.280,pi,0.030,q(2) + pi/2);
%     T23 = DH(0,pi/2,0.020,q(3) + pi/2);
%     T34 = DH(0,pi/2,(0.140+0.105),q(4) + pi/2);
%     T45 = DH(0,pi/2,(0.0285+0.0285),q(5) + pi);
%     T56 = DH(0,pi/3,(0.105+0.130),q(6) + pi/2);
% 
%     T02 = T01*T12; 
%     T03 = T02*T23;
%     T04 = T03*T34;
%     T05 = T04*T45;
%     T06 = T05*T56;
% 
%     t0 = [0 0 0]'; 
%     t1 = T01(1:3,4); 
%     t2 = T02(1:3,4); 
%     t3 = T03(1:3,4); 
%     t4 = T04(1:3,4); 
%     t5 = T05(1:3,4); 
%     t6 = T06(1:3,4);
% 
%     Z0 = [0 0 1]'; 
%     Z1 = T01(1:3,3); 
%     Z2 = T02(1:3,3); 
%     Z3 = T03(1:3,3); 
%     Z4 = T04(1:3,3); 
%     Z5 = T05(1:3,3); 
% 
%     Jv1 = cross(Z0,(t6 - t0)); 
%     Jv2 = cross(Z1,(t6 - t1)); 
%     Jv3 = cross(Z2,(t6 - t2)); 
%     Jv4 = cross(Z3,(t6 - t3)); 
%     Jv5 = cross(Z4,(t6 - t4)); 
%     Jv6 = cross(Z4,(t6 - t5));
% 
%     Jw1 = Z0; Jw2 = Z1; Jw3 = Z2; Jw4 = Z3; Jw5 = Z4; Jw6 = Z5;
% 
%     J = [Jv1 Jv2 Jv3 Jv4 Jv5 Jv6;Jw1 Jw2 Jw3 Jw4 Jw5 Jw6];
%     Jv = J(1:3,:);
%     ti = T06(1:3,4);
%     Ri = T06(1:3,1:3);
% 
%     v = td-ti;
%     w = 0.5*(cross(Ri(:,1),Rd(:,1))+cross(Ri(:,2),Rd(:,2))+cross(Ri(:,3),Rd(:,3)));
%     e = [v; w];
%     Ji = pinv(J);
%     %Ji = Jv' * inv(Jv * Jv');
% 
%     q = q+k*Ji*e;
% 
%     mu= sqrt(det(J*J'));
%     cla
%     Dibujar_Manipulador({T01,T12,T23,T34,T45,T56},{'RRRRRR'},0.03);
%     %axis([-0.8 0.8 -0.8 0.8 -0.2 0.8]);
%     axis auto
%     drawnow;
% 
%     mu_plot = [mu_plot mu];
%     t_plot = [t_plot t];
% 
% 
% end
% 
% figure
% hold on
% grid on
% plot(t_plot, mu_plot', 'LineWidth', 2)
% %legend('\theta_1', '\theta_2', '\theta_3', '\theta_4', '\theta_5')
% xlabel('segundos')
% ylabel('rad/s')
% %title('Velocidades articulares')
% 
% %%
% function T = DH(a,alpha,d,theta)
% T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) a*cos(theta); ...
% sin(theta) cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
% 0 sin(alpha) cos(alpha) d; 0 0 0 1];
% end

A= [2 -2 1 4;-1 6 0 -2;4 1 3 1;3 2 -2 1]

det(A)

adjoint(A)

B=magic(4)