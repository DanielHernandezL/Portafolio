clear all
close all
clc

% Conecta en el SCARA (Coppelia)
bot = Bot_Scara();

% Verificar si tanto el rectángulo como la referencia son alcanzables antes de mover
if Validar_Posiciones(bot)
    % Mover el SCARA para tomar el objeto en la posición del rectángulo
    Mover_Al_Rectangulo(bot);

    % Mover el objeto tomado a la posición de referencia
    Mover_referencia(bot);

    % Regresar el manipulador a la posición original
    q = [0 0 0 0]';
    bot.Set_Joint_Position(q);
    pause(1);
end

% Parar la simulación
bot.Stop_Simulation();

%% Función para mover el SCARA al rectángulo y tomar el objeto
function Mover_Al_Rectangulo(bot)
    % Obtener la pose de referencia (por ejemplo, la posición del objeto)
    Td = bot.Rectangle_Pose();

    % Calcular las coordenadas articulares usando las ecuaciones inversas
    [theta_1,theta_2,d3,theta_4] = Vector_coordenadas(bot, Td);

    % Mover el SCARA sobre la posición del objeto sin bajar aún la articulación prismática
    qf = [theta_1,theta_2,0,theta_4]';  % No bajamos la articulación prismática
    Movimiento_Articular(bot,qf,3.85);
    pause(0.5);

    % Bajar la articulación prismática para alcanzar el objeto
    qf = [theta_1,theta_2,d3,theta_4]';  % Ahora bajamos la articulación prismática
    Movimiento_Articular(bot,qf,2.85);
    pause(0.5);

    % Cerrar el gripper para tomar el objeto
    bot.Gripper_Command(0);  % 1 = cerrar el gripper
    pause(1);  % Darle un tiempo al gripper para agarrar el objeto

    % Elevar la articulación prismática de nuevo con el objeto agarrado
    qf = [theta_1,theta_2,0,theta_4]';  % Volver a levantar la articulación prismática
    Movimiento_Articular(bot,qf,2.85);
    pause(0.5);
end

%% Función para mover el SCARA al eje de referencia y soltar el objeto
function Mover_referencia(bot)
    % Obtener la pose de referencia
    Tdr = bot.ReferenceFrame_Pose();

    % Calcular las coordenadas articulares usando las ecuaciones inversas
    [theta_1,theta_2,d3,theta_4] = Vector_coordenadas(bot, Tdr);

    % Mover el SCARA a la posición de referencia sin bajar la articulación prismática
    qf = [theta_1,theta_2,0,theta_4]';  % No bajamos la articulación prismática
    Movimiento_Articular(bot,qf,3.85);
    pause(0.5);

    % Bajar la articulación prismática para dejar el objeto en la referencia
    qf = [theta_1,theta_2,d3,theta_4]';  % Bajamos la articulación prismática
    Movimiento_Articular(bot,qf,2.85);
    pause(0.5);

    % Abrir el gripper para soltar el objeto
    bot.Gripper_Command(1);  % 0 = abrir el gripper
    pause(1);  % Darle un tiempo al gripper para soltar el objeto

    % Elevar la articulación prismática de nuevo con el gripper abierto
    qf = [theta_1,theta_2,0,theta_4]';  % Volver a levantar la articulación prismática
    Movimiento_Articular(bot,qf,2.85);
    pause(0.5);
end

%% Función para validar si ambas posiciones son alcanzables antes de mover
function Alcanzable = Validar_Posiciones(bot)
    Td_rectangulo = bot.Rectangle_Pose();
    Td_referencia = bot.ReferenceFrame_Pose();
    
    % Inicializamos las banderas de alcanzabilidad
    rectangulo_alcanzable = Validar_Alcanzabilidad(Td_rectangulo);
    referencia_alcanzable = Validar_Alcanzabilidad(Td_referencia);

    % Validamos cada posición individualmente
    if ~rectangulo_alcanzable && ~referencia_alcanzable
        disp('Ambas posiciones (rectángulo y referencia) están fuera del alcance del SCARA. Tarea abortada.');
        Alcanzable = false;
    elseif ~rectangulo_alcanzable
        disp('La posición del rectángulo está fuera del alcance del SCARA. Tarea abortada.');
        Alcanzable = false;
    elseif ~referencia_alcanzable
        disp('La posición de referencia está fuera del alcance del SCARA. Tarea abortada.');
        Alcanzable = false;
    else
        Alcanzable = true;  % Solo se permite mover si ambas posiciones son alcanzables
    end
end

%% Funciones auxiliares
function Movimiento_Articular(bot,qf,tf)
    qi = bot.Get_Joint_Position();
    T = [1 0 -(3/tf^2) 2/tf^3; 
         0 1 -(2/tf) 1/tf^2; 
         0 0 3/tf^2 -(2/tf^3);
         0 0 -(1/tf) 1/tf^2];

    C = [qi zeros(4,1) qf zeros(4,1)] * T;
    tic;
    while toc <= tf
        t = toc;
        VC = C * [1 t t^2 t^3]';
        bot.Set_Joint_Position(VC);
    end
end 

%% Cinemática inversa 
function [theta_1,theta_2,d3,theta_4] = Vector_coordenadas(bot, Td)
    a1 = 0.4670;
    a2 = 0.4005;
    d1 = 0.4;
    d4 = 0.127;
    
    vtx = Td(1,4);
    vty = Td(2,4); 
    vtz = Td(3,4); 
    r11 = Td(1,1); 
    r21 = Td(2,1);

    % Cálculo de las variables articulares
    theta_2 = acos((vtx^2 + vty^2 - (a1)^2 - (a2)^2) / (2 * a1 * a2)); 
    theta_1 = atan2(vty, vtx) - asin((a2 * sin(theta_2)) / sqrt(vtx^2 + vty^2));
    d3 = d1 - vtz - d4; 
    theta_4 = theta_1 + theta_2 - atan2(r21, r11);
end

%% Validar alcanzabilidad
function Inalcanzable = Validar_Alcanzabilidad(T)
    % Parámetros del robot SCARA
    a1 = 0.4670;
    a2 = 0.4005;
    
    % Distancia máxima alcanzable por el robot en el plano XY
    dis_max = a1 + a2;
    
    % Posición en el plano XY
    vtx = T(1,4);
    vty = T(2,4);
    
    % Distancia radial desde el origen (base del SCARA) hasta el objetivo
    distancia_radial = sqrt(vtx^2 + vty^2);
    
    % Verificar si la distancia está dentro del alcance del SCARA
    if distancia_radial > dis_max
        Inalcanzable = false;
    else
        Inalcanzable = true;
    end
end