import cv2
import numpy as np


# Sirve para poder abrir el video
cap = cv2.VideoCapture('Video.mp4')

# Aplicar el primer filtro a blanco y negro
def Gr(frame):
    return cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Sirve para que en el filtro una sección se vea la imagen original y el resto a blanco y negro
def GrM(frame):
    w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    gray = cv2.cvtColor(frame[:, :w//2], cv2.COLOR_BGR2GRAY)
    result = np.zeros_like(frame)
    result[:, :w//2] = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
    result[:, w//2:] = frame[:, w//2:]
    return result

# Aplica un filtro suavizador
def Des(frame):
    return cv2.GaussianBlur(frame, (15, 15), 0)

# Aplica el filtro de detección de bordes 
def Bor(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 100, 200)
    return cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)


# Verifica si el video se abrió correctamente
if not cap.isOpened():
    print("Error al abrir el video")
    exit()

# Bucle para reproducir el video
while cap.isOpened:
    ret, frame = cap.read()

    #Cierra el video cuando termine
    if ret  == False:
        break

    # Obtiene el tiempo actual del video en segundos
    tiempo = cap.get(cv2.CAP_PROP_POS_MSEC) / 1000 
    # Aplica los filtros según el tiempo
    if tiempo < 1:
        frame
    elif tiempo < 3:
        frame = Gr(frame)
    elif tiempo < 5:
        frame = GrM(frame)
    elif tiempo < 7:
        frame = Des(frame)
    else:
        frame = Bor(frame)

    # Muestra el video con los filtros
    cv2.imshow('Video con los filtros', frame)

    # Verifica si se presionó la tecla 'q' para cerrar el video
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break

# Libera los recursos
cap.release()
cv2.destroyAllWindows()

