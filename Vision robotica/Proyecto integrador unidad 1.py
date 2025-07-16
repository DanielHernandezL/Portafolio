# -*- coding: utf-8 -*-
"""
Created on Wed Feb 14 20:15:15 2024

@author: pc
"""
import cv2
import numpy as np
import matplotlib.pyplot as plt

im = cv2.imread(r'C:\chica1.jpg')
ig = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
M, N = im.shape[0:2]
hist = cv2.calcHist([ig], [0], None, [5], [0, 256]).flatten() / (M * N)
maxElement = np.argmax(hist)
exposure_type = ''
if maxElement == 4 and hist[4] > 0.3:
    exposure_type = 'sobreexpuesta'
elif maxElement == 0 and hist[0] > 0.3:
    exposure_type = 'subexpuesta'
else:
    exposure_type = 'buena exposicion'
cv2.putText(im, exposure_type, (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5)

if exposure_type in ['subexpuesta', 'sobreexpuesta']:
    ig_equalized = cv2.equalizeHist(ig)
    cv2.putText(ig_equalized, 'SARL', (50, 150), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 5)
    plt.imshow(cv2.cvtColor(ig_equalized, cv2.COLOR_BGR2RGB))
    plt.title('Imagen Ecualizada')
    plt.axis('off')
    plt.show()
else:

    cv2.putText(im, 'SARL', (50, 150), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 0), 5)
    plt.imshow(cv2.cvtColor(im, cv2.COLOR_BGR2RGB))
    plt.title('Imagen Original')
    plt.axis('off')
    plt.show()

