import cv2
import numpy as np
#Sirve para abrir la imagen
im = cv2.imread('Robot.jpg')

R= im[:,:,1]
G= im[:,:,2]
B= im[:,:,0]

ig1 =R*0.33 + G*0.33 + B*0.33 
ig2 =R*0.299 + G*0.587 + B*0.114 
ig3 =R*0.2126 + G*0.7152 + B*0.0722 

ig = np.hstack((ig1,ig2,ig3))
ig = ig.astype(np.uint8)

#Sirve para cambiar de RGB a gris
igcv= cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

#Sirve para mostrar la imagen
cv2.imshow('image',im)
cv2.imshow('image',ig)
cv2.imshow('imagen',igcv)
cv2.waitKey(0)
