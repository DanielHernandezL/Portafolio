import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Puerta.jpg')

ig = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

(T, ibn) = cv2.threshold(ig, 100, 255, cv2.THRESH_BINARY)

cv2.imshow('Imagen 1',im)
cv2.imshow('Imagen 2',ibn)
cv2.waitKey()