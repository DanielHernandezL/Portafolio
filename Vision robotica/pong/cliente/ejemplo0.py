from pong import Pong
import numpy as np
import cv2
import random

#Im -> Imagen del juego
#player -> 0 = Jugador lado Izquierdo, 1 = Jugador lado derecho
#score -> lista con dos elementos de la puntuación
#powerCount -> cuantos tiros de poder le quedan a tu jugador

def datos(Im, player, score, powerCount):


    #cmd -> comando para mover la raqueta puede tener valores:
    # 1 : arriba
    # 0 : no se mueve
    # -1 : abajo
    cmd = 0

    #power: tiro de poder: 
    # 0 : tiro normal
    # 1 : tiro de poder
    power= 0

    return cmd, power

svh = Pong(datos, 'Parsival123456')
svh.start()    