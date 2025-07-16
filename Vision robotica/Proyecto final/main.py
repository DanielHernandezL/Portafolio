from pong import Pong
import numpy as np
import cv2
import random

# Definir el factor de escala para aumentar la velocidad de la raqueta
scale_factor = 2  # Puedes ajustar este valor según la velocidad deseada

# Im -> Imagen del juego
# player -> 0 = Jugador lado Izquierdo, 1 = Jugador lado derecho
# score -> lista con dos elementos de la puntuación
# powerCount -> cuantos tiros de poder le quedan a tu jugador
def datos(Im, player, score, powerCount):
    
    # Convertir la imagen de BGR a HSV y guardarla en Im2
    Im2 = cv2.cvtColor(Im, cv2.COLOR_BGR2HSV)
    # Crear una máscara para la pelota
    pel = cv2.inRange(Im2, (130,5,0), (160,255,255))
    
    # Si el jugador es del lado izquierdo, crear una máscara para el lado izquierdo
    if player == 0:
        pyr = cv2.inRange(Im2, (150,5,5), (190,255,255))
    
    # Si el jugador no es del lado izquierdo, crear una máscara para el lado derecho
    else:
        pyr = cv2.inRange(Im2, (75,5,0), (100,255,255))

    # Sumar la máscara de la pelota y del jugador para crear una máscara para los dos
    pel += pyr

    # Encontrar los contornos en la máscara anterior 
    contours, hierarchy = cv2.findContours(pel, cv2.RETR_EXTERNAL , cv2.CHAIN_APPROX_SIMPLE)
    # Encontrar y dibujar los contornos detectados de la figura más grande
    rc = max(contours, key=cv2.contourArea)
    # Hallar las coordenadas de los contornos detectados y guardarlas en rx, ry, rw, rh
    (rx, ry, rw, rh) = cv2.boundingRect(rc)

    # Encontrar y dibujar los contornos detectados de la figura más pequeña
    pel = min(contours, key=cv2.contourArea)
    # Hallar las coordenadas de los contornos detectados y guardarlas en px, py, pw, ph
    px, py, pw, ph = cv2.boundingRect(pel)

    # cmd -> comando para mover la raqueta puede tener valores:
    # 1 : arriba
    # 0 : no se mueve
    # -1 : abajo
    if (py < ry + ph):
        cmd = -1 * scale_factor  # Mover hacia abajo multiplicado por el factor de escala
    elif (py > ry + ph):
        cmd = 1 * scale_factor  # Mover hacia arriba multiplicado por el factor de escala
    else:
        cmd = 0
    # Hacer un tiro de poder o tiro normal aleatoriamente
    power = random.choice([0,1])

    # Regresar tanto el tiro de movimiento como el tiro de poder
    return cmd, power

svh = Pong(datos, 'Equipo 7')
svh.start()
