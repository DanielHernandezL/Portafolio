import numpy as np
import matplotlib.pyplot as plt
import cv2

#a) Construye una imagen de 8x15, en escala de grises y dibuja 3 pixels de diferente color
im= np.zeros((8,15), dtype= np.uint8)
im[4:7,3] = 255

#b) Construye una imagen de 12x6, en escala de grises y dibuja 2 rectángulos
im2= np.zeros((12,6), dtype= np.uint8)
im2[2:8,2:4]= 255 
im2[9:11,1:6]= 100 

#c) Construye una imagen de 9x8, RGB y dibuja 3 pixels de diferente color
im3= np.zeros((9,8,3), dtype= np.uint8)
im3[2,3,0]=255
im3[3,4,1]=255
im3[4,5,2]=255
rgb= cv2.cvtColor(im, cv2.COLOR_BGR2RGB)

#d) Construye una imagen RGB del 15x10 y dibuja 3 rectángulos de diferente color
im4= np.zeros((15,10,3), dtype= np.uint8)
im4[1:3,5:9,2]=255
im4[4:6,1:6,0]=255
im4[9:12,4:10,1]=255

plt.imshow(im, cmap='gray')
plt.show()
plt.imshow(im2, cmap='gray')
plt.show()
plt.imshow(im3)
plt.show()
plt.imshow(im4)
plt.show()