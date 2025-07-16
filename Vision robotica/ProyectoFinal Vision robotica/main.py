from pong import Pong
import numpy as np
import cv2
import random

def datos(Im, player, score, powerCount):

    Im= cv2.cvtColor(Im, cv2.COLOR_BGR2HSV)
    if player == 0:
        Jugador = cv2.inRange(Im,(0,100,100),(15,255,255)) + cv2.inRange(Im,(165,100,100),(180,255,255))
    else:
        Jugador = cv2.inRange(Im,(75,100,100),(135,255,255))
    Jugador += cv2.inRange(Im,(140,100,100),(165,255,255))

    contornos_jugador, jerarquia = cv2.findContours(Jugador, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    c = max(contornos_jugador, key= cv2.contourArea)
    x,y,w,h = cv2.boundingRect(c)
    d = min(contornos_jugador, key= cv2.contourArea)
    xp,yp,wp,hp = cv2.boundingRect(d)

    if (2*yp+hp)//2 > (2*y+h)//2:
        cmd = 1
    elif (2*yp+hp)//2 < (2*y+h)//2:
        cmd = -1
    else:
        cmd = 0

    power= random.randint(0,1)
    return cmd, power

svh = Pong(datos, 'Equipo 1')
svh.start()    