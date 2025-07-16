import cv2
import numpy as np
from pong import Pong

# Velocidad máxima de movimiento de la raqueta
paddle_speed = 24

def datos(Im, player, score, powerCount, prev_paddle_y=[0]):
    # Convertir la imagen a HSV
    hsv = cv2.cvtColor(Im, cv2.COLOR_BGR2HSV)

    # Definir el rango de colores para la pelota violeta en HSV
    lower_violet = np.array([140, 50, 50])
    upper_violet = np.array([170, 255, 255])

    # Crear una máscara para el rango de colores de la pelota violeta
    mask = cv2.inRange(hsv, lower_violet, upper_violet)

    # Encontrar contornos de la pelota en la máscara
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Inicializar la posición vertical de la raqueta
    paddle_y = prev_paddle_y[0]

    # Si se encuentran contornos
    if contours:
        # Encontrar el contorno más grande (la pelota)
        largest_contour = max(contours, key=cv2.contourArea)
        
        # Obtener las coordenadas del centro de la pelota
        M = cv2.moments(largest_contour)
        if M['m00'] != 0:
            cx = int(M['m10'] / M['m00'])
            cy = int(M['m01'] / M['m00'])
        
            # Obtener la posición vertical de la pelota
            ball_y = cy
            
            # Comparar la posición vertical de la pelota con la de la raqueta y mover la raqueta hacia la pelota
            if ball_y < paddle_y:
                paddle_y -= paddle_speed
            elif ball_y > paddle_y:
                paddle_y += paddle_speed

    # Limitar la posición de la raqueta dentro de los límites de la pantalla
    paddle_y = min(max(paddle_y, 0), Im.shape[0] - 1)

    # Calcular el movimiento de la raqueta
    cmd = paddle_y - prev_paddle_y[0]

    # Actualizar la posición previa de la raqueta
    prev_paddle_y[0] = paddle_y

    # Configurar el tiro de poder como normal
    power = 0

    return cmd, power

svh = Pong(datos, 'fenrir')
svh.start()
