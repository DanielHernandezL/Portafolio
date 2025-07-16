import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Puerta.jpg')

#Sirve para rotar la imagen 90° en el sentido de las manecillas del reloj
im2 = cv2.rotate(im, cv2.ROTATE_90_CLOCKWISE)

#Sirve para cambiar la imagen de BGR a escala de grises
ig = cv2.cvtColor(im2, cv2.COLOR_BGR2GRAY)

#Calcula el negativo
ig = 255 - ig

#Sirve para mostrar las imagenes
cv2.imshow('Imagen 1',im)
cv2.imshow('Imagen 2',ig)
cv2.waitKey()