import cv2
import numpy as np 
import matplotlib.pyplot as plt
#Sirve para guardar la imagen en una variable
ig = cv2.imread('images.jpg',0)

[M,N]= ig.shape[0:2]

#sirve para hacer el histograma
hist= cv2.calcHist([ig],[0],None,[100],[0,256]).flatten()/(M*N)

#sirve para mostrar la imagen
cv2.imshow('Imagen',ig)

#Sirve para mostrar el histograma
fig = plt.figure()
plt.bar(range(len(hist)),hist)
plt.show()

