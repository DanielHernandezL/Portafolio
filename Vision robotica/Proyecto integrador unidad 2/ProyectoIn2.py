import cv2
import numpy as np 
import matplotlib.pyplot as plt
#Sirve para guardar la imagen en una variable
im = cv2.imread('Imsobre.PNG')
ig = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
[M,N]= ig.shape[0:2]

#sirve para hacer el histograma
hist= cv2.calcHist([ig],[0],None,[5],[0,256]).flatten()/(M*N)

#Determina si la imagen esta sobre, sub o exposición normal
melements= np.argmax(hist)
if melements == 4 and hist[4] > 0.3:
    print('Sobreexpuesta')
elif melements == 0 and hist[0] > 0.3:
    print('Subexpuesta')
else:
    melements == 2
    print('Exposición normal')
    
#Si la imagen es    ta sobreexpuesta o subexpuesta la ecualiza
if melements ==(0 or 4):
    ig_equalized = cv2.equalizeHist(ig)

    #Agrega un texto en la imagen
    cv2.putText(ig_equalized,'DAHL',(34,160), cv2.FONT_HERSHEY_DUPLEX, 2, (0,0,255),2)
    plt.imshow(cv2.cvtColor(ig_equalized, cv2.COLOR_BGR2RGB))
    plt.title('Imagen Ecualizada')
    plt.axis('off')

    #sirve para mostrar la imagen
    cv2.imshow('Imagen',ig)

    #Sirve para mostrar el histograma
    fig = plt.figure()
    plt.bar(range(len(hist)),hist)
    plt.show()

else:
    #Agrega un texto en la imagen
    cv2.putText(ig,'DAHL',(500,200), cv2.FONT_HERSHEY_DUPLEX, 2, (0,0,255),2)

    #sirve para mostrar la imagen
    cv2.imshow('Imagen',ig)

    #Sirve para mostrar el histograma
    fig = plt.figure()
    plt.bar(range(len(hist)),hist)
    plt.show()
