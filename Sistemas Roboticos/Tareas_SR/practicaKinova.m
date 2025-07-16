%% Conexión
Simulink.importExternalCTypes(which('kortex_wrapper_data.h'));
gen3Kinova = kortex();
gen3Kinova.ip_address = '192.168.2.10';
gen3Kinova.user = 'admin';
gen3Kinova.password = 'admin';
gen3Kinova.nbrJointActuators = 6;

% Verificar la conexión
isOk = gen3Kinova.CreateRobotApisWrapper();
if isOk
   disp('You are connected to the robot!'); 
else
   error('Failed to establish a valid connection!'); 
end

% Obtener sensores
[isOk,baseFb, actuatorFb, interconnectFb] = gen3Kinova.SendRefreshFeedback();
if isOk
    disp('Base feedback');
    disp(baseFb);
    disp('Actuator feedback');
    disp(actuatorFb);
    disp('Gripper feedback');
    disp(interconnectFb);
else
    error('Failed to acquire sensor data.'); 
end

%% Posición
[isOk,baseFb, actuatorFb, interconnectFb] = gen3Kinova.SendRefreshFeedback();

q_kinova = actuatorFb.position(1:6)';
td = [0.2602 0.4530 0.2421]';

[q_kinova,e] = ik_position (td,q_kinova);

%% Posición y orientación
[isOk,baseFb, actuatorFb, interconnectFb] = gen3Kinova.SendRefreshFeedback();

q_kinova = actuatorFb.position(1:6)';
td = [0.2602 0.4530 0.0421]';
Rd = [0,-1,0; 0,0,1; -1,0,0];
% Rd = rotx(-90)*rotz(90);
% Rd = roty(-180)*rotz(-180);
Td = [[Rd td]; 0 0 0 1];

[q_kinova,e] = ik_pose (Td,q_kinova);

%% Mandar q
jointCmd = [q_kinova 0];
constraintType = int32(0);
speed = 0;
duration = 0;

isOk = gen3Kinova.SendJointAngles(jointCmd, constraintType, speed, duration);
if isOk
    disp('Command sent to the robot. Wait for the robot to stop moving.');
else
    disp('Command error.');
end
return
%% Control de gripper 
% Cerrar gripper
toolCommand = int32(3);    % position mode
toolDuration = 0;
toolCmd = 0;             % 0=abierto  1=cerrado
isOk = gen3Kinova.SendToolCommand(toolCommand, toolDuration, toolCmd);
if isOk
    disp('Command sent to the gripper. Wait for the gripper to stop moving.')
else
    error('Command Error.');
end
return

