import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Puerta.jpg')


#Sirve para cambiar la imagen de BGR a escala de grises
ig = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
ig2 = 255 - ig
#Sirve para mostrar la imagen
cv2.imshow('imagen1',im)
cv2.imshow('imagen2',ig2)
cv2.waitKey()