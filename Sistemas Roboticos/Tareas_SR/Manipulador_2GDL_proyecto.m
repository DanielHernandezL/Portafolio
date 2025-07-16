clear all
close all
clc

%% Robot planar 2DOf proyecto
%% Inicializar servos
a = arduino('COM6','Uno','Libraries','Servo');

s1 = servo(a,'D6');
s2 = servo(a,'D5');
%% Para hacerlo funcionar
q_dh = [0 0]';

q_arduino = (q_dh + pi/2) / pi;
writePosition(s1,q_arduino(1))
writePosition(s2,q_arduino(2))
%% Variables globales
a1 = 0.10;
a2 = 0.115;
td = [0.05 -0.015 0]';
tx = td(1);
ty = td(2);
tf = 10;
%q = readPosition(s)
%% Cinematica directa
% q_1 = readPosition(s1);
% q_2 = readPosition(s2);
% q = [q_1 q_2 0]';
q = home(s1,s2);
qf = [pi/4 -pi/4 0]';
S = tf;
tic
while toc <= S
    %T01 = DH(a1,0,0,q(1));
    T01 = [cos(q(1)) -sin(q(1))*cos(0) sin(q(1))*sin(0)  a1*cos(q(1));
           sin(q(1))  cos(q(1))*cos(0) -cos(q(1))*sin(0) a1*sin(q(1));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];
    %T12 = DH(a2,0,0,q(2));
    T12 = [cos(q(2)) -sin(q(2))*cos(0) sin(q(2))*sin(0)  a2*cos(q(2));
           sin(q(2))  cos(q(2))*cos(0) -cos(q(2))*sin(0) a2*sin(q(2));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];   
    
    T02 = T01*T12;
    ti = T02(1:3,4);
    t = toc;
    T = [1 0 -(3/tf^2) 2/tf^3;0 1 -(2/tf) 1/tf^2;0 0 3/tf^2 -(2/tf^3);0 0 -(1/tf) 1/tf^2];
    A = [q zeros(3,1) qf zeros(3,1)]*T;
    q = A*[1;t;t^2;t^3];
    if ((qf(1) > pi/2) || (qf(1) < -pi/2)) && ((qf(2) > pi/2) || (qf(2) < -pi/2))
        disp('Punto inalcanzable');
        break;
    else
    q_arduino = (q + pi/2) / pi;
    writePosition(s1,q_arduino(1))
    writePosition(s2,q_arduino(2))

    cla
    Dibujar_Manipulador({T01,T12},{'RR'},0.02);
    axis([-0.25 0.25 -0.25 0.25 -0.08 0.25])
    view([90 90])
    drawnow

    end
end
%% Cinematica inversa
% q_1 = readPosition(s1);
% q_2 = readPosition(s2);
% q = [q_1 q_2 0]';
q = home(s1,s2);
if (tx < 0) && (ty < 0)
    theta2 = -acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
elseif (tx < 0) && (ty > 0)
    theta2 = acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
else
    eleccion = randi(2);
    if eleccion == 1
       theta2 = acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
    elseif eleccion == 2
        theta2 = -acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
    end
end
theta1 = atan2(ty,tx)-asin((a2*sin(theta2))/(sqrt((tx)^2 + (ty)^2)));

if (theta1 >= pi/2)
    theta2 = acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
elseif (theta1 <= -pi/2)
    theta2 = -acos(((tx)^2 + (ty)^2 - (a1)^2 - (a2)^2)/(2*a1*a2));
end
qf = [theta1 theta2 0]';
S  = tf;
tic
while toc <= S
    if ((qf(1) > pi/2) || (qf(1) < -pi/2)) && ((qf(2) > pi/2) || (qf(2) < -pi/2))
        disp('Punto inalcanzable');
        break;
    else
    t = toc;
    %T01 = DH(a1,0,0,q(1));
    T01 = [cos(q(1)) -sin(q(1))*cos(0) sin(q(1))*sin(0)  a1*cos(q(1));
           sin(q(1))  cos(q(1))*cos(0) -cos(q(1))*sin(0) a1*sin(q(1));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];
    %T12 = DH(a2,0,0,q(2));
    T12 = [cos(q(2)) -sin(q(2))*cos(0) sin(q(2))*sin(0)  a2*cos(q(2));
           sin(q(2))  cos(q(2))*cos(0) -cos(q(2))*sin(0) a2*sin(q(2));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];   
    
    T02 = T01*T12;
    ti = T02(1:3,4);

    T = [1 0 -(3/tf^2) 2/tf^3;0 1 -(2/tf) 1/tf^2;0 0 3/tf^2 -(2/tf^3);0 0 -(1/tf) 1/tf^2];
    A = [q zeros(3,1) qf zeros(3,1)]*T;
    q = A*[1;t;t^2;t^3];
    
    disp(['time =' num2str(t)]);

    q_arduino = (q + pi/2) / pi;
    writePosition(s1,q_arduino(1))
    writePosition(s2,q_arduino(2))

    cla
    Dibujar_Manipulador({T01,T12},{'RR'},0.02);
    axis([-0.25 0.25 -0.25 0.25 -0.08 0.25])
    view([90 90])
    drawnow
    end
end
%%
function T = DH(a,alpha,d,theta)
T = [cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha)  a*cos(theta); ...
     sin(theta)  cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta); ...
     0           sin(alpha)             cos(alpha)                       d; 
     0                 0                        0                       1];
end

%% HOME
function qfinal = home(s1,s2,tf)
a1 = 0.10;
a2 = 0.115;
td = [0.5 -0.2 0]';
tx = td(1);
ty = td(2);
tf = 7;
q_1 = readPosition(s1);
q_2 = readPosition(s2);
q = [q_1 q_2 0]';
qf = [0 pi/4 0]';
S = tf;
tic
while toc <= S
    %T01 = DH(a1,0,0,q(1));
    T01 = [cos(q(1)) -sin(q(1))*cos(0) sin(q(1))*sin(0)  a1*cos(q(1));
           sin(q(1))  cos(q(1))*cos(0) -cos(q(1))*sin(0) a1*sin(q(1));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];
    %T12 = DH(a2,0,0,q(2));
    T12 = [cos(q(2)) -sin(q(2))*cos(0) sin(q(2))*sin(0)  a2*cos(q(2));
           sin(q(2))  cos(q(2))*cos(0) -cos(q(2))*sin(0) a2*sin(q(2));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];   
    
    T02 = T01*T12;
    ti = T02(1:3,4);
    t = toc;
    T = [1 0 -(3/tf^2) 2/tf^3;0 1 -(2/tf) 1/tf^2;0 0 3/tf^2 -(2/tf^3);0 0 -(1/tf) 1/tf^2];
    A = [q zeros(3,1) qf zeros(3,1)]*T;
    q = A*[1;t;t^2;t^3];
    if ((qf(1) > pi/2) || (qf(1) < -pi/2)) && ((qf(2) > pi/2) || (qf(2) < -pi/2))
        disp('Punto inalcanzable');
        break;
    else
    q_arduino = (q + pi/2) / pi;
    writePosition(s1,q_arduino(1))
    writePosition(s2,q_arduino(2))

    end
end
qfinal = q;
end

%% Jacobiano geometrico
% q_1 = readPosition(s1);
% q_2 = readPosition(s2);
% q = [q_1 q_2 0]';
q = home(s1,s2);
k = 0.1;
%q = [0 -pi/2 0]';
qf = [pi/4 -pi/4 0]';
S = tf;
tic
while toc <= S
    %T01 = DH(a1,0,0,q(1));
    T01 = [cos(q(1)) -sin(q(1))*cos(0) sin(q(1))*sin(0)  a1*cos(q(1));
           sin(q(1))  cos(q(1))*cos(0) -cos(q(1))*sin(0) a1*sin(q(1));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];
    %T12 = DH(a2,0,0,q(2));
    T12 = [cos(q(2)) -sin(q(2))*cos(0) sin(q(2))*sin(0)  a2*cos(q(2));
           sin(q(2))  cos(q(2))*cos(0) -cos(q(2))*sin(0) a2*sin(q(2));
              0           sin(0)             cos(0)                 0; 
              0             0                  0                    1];   
    %Cinematica directa
    T02 = T01*T12;

    % Jacobiano geometrico
    t0 = [0 0 0]'; 
    t1 = T01(1:3,4); 
    t2 = T02(1:3,4); 
    ti = T02(1:3,4);

    Z0 = [0 0 1]'; 
    Z1 = T01(1:3,3); 

    Jv1 = cross(Z0,(t2 - t0)); 
    Jv2 = cross(Z1,(t2 - t1));

    J = [cross(Z0, t2 - t0), cross(Z1, t2 - t1)];
    %Jw = [Z0, Z1];
    % Matriz Jacobiana completa
    %J =([Jv_g; Jw]);

    Jv = J(1:3,:);
    ti = T02(1:3,4);
    Ri = T02(1:3,1:3);
    v = td-ti;
    Ji = inv(Jv'*Jv)*Jv';
    %Ji = pinv(J);
    
    q = q(1:2,:)+k*Ji*v;
    q = [q;0]

    mu= sqrt(det(J*J'));

     t = toc;
    % T = [1 0 -(3/tf^2) 2/tf^3;0 1 -(2/tf) 1/tf^2;0 0 3/tf^2 -(2/tf^3);0 0 -(1/tf) 1/tf^2];
    % A = [q zeros(3,1) qf zeros(3,1)]*T;
    % q = A*[1;t;t^2;t^3];
    if ((qf(1) > pi/2) || (qf(1) < -pi/2)) && ((qf(2) > pi/2) || (qf(2) < -pi/2))
        disp('Punto inalcanzable');
        break;
    else
    q_arduino = (q + pi/2) / pi;
    writePosition(s1,q_arduino(1))
    writePosition(s2,q_arduino(2))

    cla
    Dibujar_Manipulador({T01,T12},{'RR'},0.05);
    axis([-0.8 0.8 -0.8 0.8 -0.2 0.8])
    view([90 90])
    drawnow

    end
end
