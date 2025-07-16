import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Puerta.jpg')

#Sirve para cambiar la imagen de BGR a escala de grises
ig = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
#Sirve para cambiar la imagen de escala de grises a blanco y negro
(T, ibn) = cv2.threshold(ig, 100, 255, cv2.THRESH_BINARY)

#Calcula el negativo
ibn= 255 - ibn

#Sirve para mostrar las imagenes
cv2.imshow('Imagen 1',im)
cv2.imshow('Imagen 2',ibn)
cv2.waitKey()