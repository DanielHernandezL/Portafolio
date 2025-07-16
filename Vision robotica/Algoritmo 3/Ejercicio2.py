import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Puerta.jpg')

#Calcula el negativo
im2 = 255 - im

#Muestra las imagenes
cv2.imshow('imagen 1',im)
cv2.imshow('imagen 2',im2)
cv2.waitKey()