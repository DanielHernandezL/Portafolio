import numpy as np
import cv2

im = cv2.imread('Capturapong.PNG')

im= cv2.cvtColor(im, cv2.COLOR_BGR2HSV)
#Pelota
maskp= cv2.inRange(im, (130,5,0),(160,255,255))

#Lado azul
maskp1= cv2.inRange(im, (75,5,0),(100,255,255))

#Lado rojo
maskp2= cv2.inRange(im, (150,5,5),(190,255,255)) 



mask1=cv2.inRange(im,(0,5,0),(15,255,255))+cv2.inRange(im,(150,5,0),(190,255,255))

#mask1=cv2.inRange(im,(75,5,0),(100,255,255))

#cv2.imshow('Imagen',maskp)
#cv2.imshow('Imagen',maskp1)
#cv2.imshow('Imagen',maskp2)
cv2.imshow('Imagen',mask1)

cv2.waitKey(0)

