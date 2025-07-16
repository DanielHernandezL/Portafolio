clear all
close all
clc

bot = Bot_Scara();

%%
Td = bot.Rectangle_Pose();
Td

Td = bot.ReferenceFrame_Pose();
Td

%%

q'

pause(1)

q = [-pi/4 pi/4 0 0]';
bot.Set_Joint_Position(q);
q = bot.Get_Joint_Position();
q'

pause(1)

%%
S = 5;



q = [0 0 0 0]';
bot.Set_Joint_Position(q);
pause(2)

%%
bot.Stop_Simulation();
