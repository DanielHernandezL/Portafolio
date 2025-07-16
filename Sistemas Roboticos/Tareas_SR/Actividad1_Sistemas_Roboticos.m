%HernándezLópez Daniel Alejandro
clear all
clc

%Matriz antisimétrica
J = @(u) [0 -u(3) u(2); u(3) 0 -u(1); -u(2) u(1) 0];

w = [0 1 0]';
theta = -pi/4;
I = eye(3,3);
U0= cos(theta/2);
u= sin(theta/2)*w;

%Matriz de rotación utilizando la fórmula de Rodrigues
R_Rodrigues = I+sin(theta)*J(w)+(1-cos(theta))*(J(w)^2);

%Matriz de rotación relacionada con el cuaternión
R_cuaternion = (U0^2-u'*u)*I+2*U0*J(u)+2*(u*u');

%Matriz de rotación en y
R =roty(-45)

%Cuaternión unitario
cuaternion_unitario = U0^2+(u'*u);


aTb =[R [0 0 0]'; 0 0 0 1];
cla;
Dibujar_Sistema_Referencia_3D (aTb,'R');
%Graficar los ejes en 3D
function Dibujar_Sistema_Referencia_3D (aTb,s)
    hold on
    grid on
    axis([-1.5 1.5 -1.5 1.5 -1.5 1.5])
    xlabel('x')
    ylabel('y')
    zlabel('z')

    apx = aTb*[0.5 0 0 1]';
    apy = aTb*[0 0.5 0 1]';
    apz = aTb*[0 0 0.5 1]';
    
    atb = aTb(1:3,4);
    
    line([atb(1) apx(1)],[atb(2) apx(2)],[atb(3) apx(3)],'color',[1 0 0],'LineWidth',3)
    line([atb(1) apy(1)],[atb(2) apy(2)],[atb(3) apy(3)],'color',[0 1 0],'LineWidth',3)
    line([atb(1) apz(1)],[atb(2) apz(2)],[atb(3) apz(3)],'color',[0 0 1],'LineWidth',3)
    
    plot3(atb(1),atb(2),atb(3),'k.','MarkerSize',25)
    text(atb(1),atb(2),atb(3)-0.1,s,'Color','blue','FontSize',15)
    view([-45,30])

end