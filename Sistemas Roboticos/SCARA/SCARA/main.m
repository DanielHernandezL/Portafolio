clear all
close all
clc

% Función para conectar MATLAB con CoppeliaSim
bot = Bot_Scara();

% Función para obtener qf para el rectángulo
[Theta_1R,Theta_2R,d3R,Theta_4R,TxR,TyR,TzR,a1,a2,d1,d4] = calcular_angulos_Rectangulo(bot);

% Función para obtener qf para la referencia
[Theta_1D,Theta_2D,d3D,Theta_4D,TxD,TyD,TzD] = Calcular_angulos_Referencia(bot);

% Evalua si el rectángulo es alcanzable
if (TxR^2+TyR^2-a1^2-a2^2) > (2*a1*a2) || TzR > d1-d4
    % Imprime el siguiente mensaje en la consola
    fprintf('\nEl rectángulo es inalcanzable\n');

    % Regresa a ceros para que no ocurra un bug
    qin = [0 0 0 0]';
    bot.Set_Joint_Position(qin);
    pause(0.5);

    % Función para detener la simulación
    bot.Stop_Simulation();
else
    % Evalua si la referencia es alcanzable
    if(TxD^2+TyD^2-a1^2-a2^2) > (2*a1*a2) || TzD > d1-d4
        % Imprime el siguiente mensaje en la consola
        fprintf('\nLa referencia es inalcanzable\n');

        % Regresa a ceros para que no ocurra un bug
        qin = [0 0 0 0]';
        bot.Set_Joint_Position(qin);
        pause(0.5);

    % Función para detener la simulación
        bot.Stop_Simulation();
    else
%Evalua si el rectángulo y la referencia no se encuentran en la misma posición y orientación
        if TxR ~= TxD && TyR ~= TxD
            %% Funciones para mover el manipulador
            qf = [Theta_1R, Theta_2R, 0, Theta_4R]';
            mover_art(bot, qf, 2.8);

            qf = [Theta_1R, Theta_2R, d3R, Theta_4R]';
            mover_art(bot, qf, 2);
            pause(0.5)

            % Cierra el gripper
            bot.Gripper_Command(0);
            pause(0.25)

            qf = [Theta_1R, Theta_2R, 0, Theta_4R]';
            mover_art(bot, qf, 2.5);
            pause(0.25)

            % Calcular la distancia entre el rectángulo y la referencia
            distancia = sqrt((TxD - TxR)^2 + (TyD - TyR)^2);

            % Si el rectángulo y la referencia están a más de 0.75 de distancia
            if distancia > 0.75
                % Si están lejos
                qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
                mover_art(bot, qf, 5.8);
                pause(0.25)
            else
                % Si están cerca pero ambas se encuentran en el semiplano izquierdo
                if TxR < 0 && TxD < 0 && TyR <= 0 && TyD >= 0 || TyR >= 0 && TyD <= 0
                    % Si están lejos
                    qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
                    mover_art(bot, qf, 7.6);
                    pause(0.25)
                else
                    if distancia > 0.3 && distancia <= 0.63 && ((TxR > 0 && TxD > 0) || (TxR < 0 && TxD < 0))
                        % Si están mayor a 0.3 y menor o igual a 0.6
                        qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
                        mover_art(bot, qf, 3.7);
                        pause(0.25)
                    else
                        if distancia <= 0.3
                            % Si están cerca pero menor o igual a una distancia de 0.3
                            qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
                            mover_art(bot, qf, 2);
                            pause(0.25)
                        else
                            % Si están cerca pero mayor a una distancia de 0.3
                            qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
                            mover_art(bot, qf, 5);
                            pause(0.25)
                        end
                    end
                end
            end

            qf = [Theta_1D, Theta_2D, d3D, Theta_4D]';
            mover_art(bot, qf, 2.5);
            pause(0.25)

            % Abre el gripper
            bot.Gripper_Command(1);
            pause(0.25)

            qf = [Theta_1D, Theta_2D, 0, Theta_4D]';
            mover_art(bot, qf, 1.5);
            pause(1.2)

            % Regresa a ceros para que no ocurra un bug
            qf = [0 0 0 0]';
            mover_art(bot, qf, 3);
            pause(1)

            % Función para detener la simulación
            bot.Stop_Simulation();
        else
            % Imprime el siguiente mensaje en la consola
            fprintf('\nEl rectángulo ya se encuentra en la referencia\n');

            % Regresa a ceros para que no ocurra un bug
            qin = [0 0 0 0]';
            bot.Set_Joint_Position(qin);
            pause(1)

            % Función para detener la simulación
            bot.Stop_Simulation();
        end
    end
end

%% Función para calcular los ángulos para el rectángulo
function [Theta_1R,Theta_2R,d3R,Theta_4R,TxR,TyR,TzR,a1,a2,d1,d4] = calcular_angulos_Rectangulo(bot)
    % Obtener las poses del Rectangulo
    TR = bot.Rectangle_Pose();
    R21R = TR(2,1);
    R11R = TR(1,1);
    TxR = TR(1,4);
    TyR = TR(2,4);
    TzR = TR(3,4);

    % Parámetros del robot
    d1 = 0.4;
    a1 = 0.4670;
    a2 = 0.4005;
    d4 = 0.127;

    %Escoge al azar un 0 o un 1
    r = randi([0, 1]);

    % Cálculo de los ángulos y desplazamientos
    if r == 0
        % Primera solución
        Theta_2R= +acos((TxR^2+TyR^2-a1^2-a2^2)/(2*a1*a2));
    else
        % Segunda solucón
        Theta_2R= -acos((TxR^2+TyR^2-a1^2-a2^2)/(2*a1*a2));
    end
    Theta_1R= atan2(TyR,TxR)-asin((a2*sin(Theta_2R))/sqrt(TxR^2+TyR^2));
    d3R= d1-TzR-d4;
    Theta_4R= Theta_1R+Theta_2R-atan2(R21R,R11R);
end

%% Función para calcular los ángulos para la referencia
function [Theta_1D, Theta_2D, d3D, Theta_4D, TxD, TyD, TzD] = Calcular_angulos_Referencia(bot)
    % Obtener las poses de la referencia
    TD = bot.ReferenceFrame_Pose();
    R21D = TD(2,1);
    R11D = TD(1,1);
    TxD = TD(1,4);
    TyD = TD(2,4);
    TzD = TD(3,4);

    % Parámetros del robot
    d1 = 0.4;
    a1 = 0.4670;
    a2 = 0.4005;
    d4 = 0.127;

    % Escoge al azar un 0 o un 1
    r2 = randi([0, 1]);

    % Cálculo de los ángulos y desplazamientos
    if r2 == 0
        % Primera solución
        Theta_2D= +acos((TxD^2+TyD^2-a1^2-a2^2)/(2*a1*a2));
    else
        % Segunda solución
        Theta_2D= -acos((TxD^2+TyD^2-a1^2-a2^2)/(2*a1*a2));
    end
    Theta_1D= atan2(TyD,TxD)-asin((a2*sin(Theta_2D))/sqrt(TxD^2+TyD^2));
    d3D= d1-TzD-d4;
    Theta_4D= Theta_1D+Theta_2D-atan2(R21D, R11D);
end

%% Función para mover las articulaciones
function mover_art(bot, qf, tf)
    qi = bot.Get_Joint_Position();

    T = [1 0 -(3/tf^2) 2/tf^3; 0 1 -(2/tf) 1/tf^2; 0 0 3/tf^2 -(2/tf^3); 0 0 -(1/tf) 1/tf^2];
    A = [qi zeros(4,1) qf zeros(4,1)]*T;

    tic
    while toc <= tf
        t = toc;
        %disp(['time=' num2str(t)])
        q = A*[1 t t^2 t^3]';
        bot.Set_Joint_Position(q);
    end
end