close all
clear all
clc
%% Inicializar servos
a = arduino('COM5','Uno','Libraries','Servo');

s1 = servo(a,'D6');
s2 = servo(a,'D5');
%% Para hacerlo funcionar
q_dh = [0 0]';

q_arduino = (q_dh + pi/2) / pi;
writePosition(s1,q_arduino(1))
writePosition(s2,q_arduino(2))
%% Variables globales
a1 = 0.10;
a2 = 0.1050;
% td = [0.165 0.06 0]';
% tx = td(1);
% ty = td(2);
tf = 10;
%q = readPosition(s)
% Cinematica directa
% q_1 = readPosition(s1);
% q_2 = readPosition(s2);
% q = [q_1 q_2 0]';
q = home(s1,s2);
%qf = [pi/10 -pi/10 0]';
qf = [1000 pi/4 0]';
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
    if((q(1) >= pi/2) || (q(1) <= -pi/2)) || ((q(2) >= pi/2) || (q(2) <= -pi/2)) 
        if ((q(1) >= pi/2) || (q(1) <= -pi/2)) && ((q(2) >= pi/2) || (q(2) <= -pi/2)) 
            disp('Punto inalcanzable las cordenadas exeden rangos');
        elseif (q(1) >= pi/2) || (q(1) <= -pi/2)
            disp('Punto inalcanzable cordenadas coordenadas de la articulacion 1 excedida');
        elseif (q(2) >= pi/2) || (q(2) <= -pi/2)
            disp('Punto inalcanzable cordenadas coordenadas de la articulacion 2 excedida');
        end
        break;
    elseif abs(tx^2 + ty^2 - a2^2 - a1^2) >= abs(2*a1*a2)
          disp('Punto inalcanzable posicion deseada fuera del limite');
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
%% HOME
function qfinal = home(s1,s2)
a1 = 0.127;
a2 = 0.122;
td = [0.05 -0.02 0]';
tx = td(1);
ty = td(2);
tf = 4;
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