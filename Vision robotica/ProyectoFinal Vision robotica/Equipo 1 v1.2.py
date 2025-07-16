# -*- coding: utf-8 -*-
"""
Created on Tue Nov 28 09:46:54 2023

@author: satos
"""
from pong import Pong
import numpy as np
import cv2
import random

def datos(Im, player, score, powerCount):
    power=0
    cmd=0   
    imAn=cv2.cvtColor(Im, cv2.COLOR_BGR2HSV)
    mask=cv2.inRange(imAn,(130,5,0),(160,255,255))
    if(player==1):
        if(score[0]>score[player]):
            power=1
        mask1=cv2.inRange(imAn,(75,5,0),(100,255,255))
  
    else:
        if(score[1]>score[player]):
            power=1
        mask1=cv2.inRange(imAn,(0,5,0),(15,255,255))+cv2.inRange(imAn,(150,5,0),(190,255,255))
        '''mask2=cv.inRange(imAn,(150,5,0),(190,255,255))
        mask=cv.add(mask, mask2)
    
    mask=cv.add(mask, mask1)
    '''
    mask+=mask1    
    
    cont,wea=cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    raq=max(cont, key= cv2.contourArea)
    rx,ry,rw,rh = cv2.boundingRect(raq)
    
    pel=min(cont, key= cv2.contourArea)
    px,py,pw,ph = cv2.boundingRect(pel)
    
    if(py < ry+ph*3):
        cmd=-1
        
    if(py > ry+ph*3):
        cmd=1

    return cmd, power

svh = Pong(datos, 'Equipo A')
svh.start()    