from pong import Pong
import numpy as np
import cv2
import random


def datos(Im, player, score, powerCount):
    
    Im2 = cv2. cvtColor(Im, cv2.COLOR_BGR2HSV)
    pel= cv2.inRange(Im2, (130,5,0),(160,255,255))
    
    if player == 0:
        pyr= cv2.inRange(Im2, (150,5,5),(190,255,255))

    else:
        pyr= cv2.inRange(Im2, (75,5,0),(100,255,255))

    pel+=pyr

    contours, hierarchy = cv2.findContours(pel, cv2.RETR_EXTERNAL , cv2.CHAIN_APPROX_SIMPLE)
    rc= max(contours, key=cv2.contourArea)
    rx,ry,rw,rh = cv2.boundingRect(rc)

    pel= min(contours, key=cv2.contourArea)
    px,py,pw,ph = cv2.boundingRect(pel)

    if (ry + rh < py + ph):
        cmd = 1
    elif (py == ry + ph):
        cmd = 0
    else:
        cmd = -1

    power= random.choice([0,1])

    return cmd, power

svh = Pong(datos, 'Equipo 7')
svh.start()    