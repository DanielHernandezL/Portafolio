import cv2
import numpy as np
from time import sleep

#Valores del objeto a seguir
val_min= (25, 150, 200)
val_max= (35, 250, 255)


#Guarda el video en una variable
cap= cv2.VideoCapture('Video1.mp4')

#Encueentra el objeto con el color deseado
def find_object(im, mas, color):
    cnts, hierarchy = cv2.findContours(mas, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    c= max(cnts, key= cv2.contourArea)
    x,y,w,h= cv2.boundingRect(c)
    cv2.rectangle(im, (x,y), (x+w,y+h), color, 5)

    return(round(x+w/2), round(y+h/2))

#Sirve para reproducir el video
while (cap.isOpened()):
    ret, im= cap.read() 
    if ret == False:
        break
    #convierte el video de BGR a HSV
    hsv= cv2.cvtColor(im, cv2.COLOR_BGR2HSV)

    #Crea una mascara para reconocer el color
    mask= cv2.inRange(hsv, val_min, val_max)
    pd= find_object(im, mask, (0,0,0))
    
    #Muestra el video
    cv2.imshow('imagen', im)
    
    
    if cv2.waitKey(1) & 0xFF== 27:
        break
    
    #Sirve para que el video se reproduzca a una velocidad de 1/64
    sleep(1/64)