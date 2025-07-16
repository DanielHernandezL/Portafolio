# -*- coding: utf-8 -*-
"""
Created on Tue Nov 28 09:46:54 2023

@author: satos
"""

from pong import Pong
import numpy as np
import cv2 as cv
import random




def datos(Im, player, score, powerCount):
    cmd=0   
    if(player==1):
        
        imAn=cv.cvtColor(Im, cv.COLOR_BGR2HSV)
        mask=cv.inRange(imAn,(130,5,0),(160,255,255))
        mask1=cv.inRange(imAn,(75,5,0),(100,255,255))
        mask=cv.add(mask,mask1)
        
        cont,wea=cv.findContours(mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE) 
        raq=max(cont, key= cv.contourArea)
        rx,ry,rw,rh = cv.boundingRect(raq)
        
        pel=min(cont, key= cv.contourArea)
        px,py,pw,ph = cv.boundingRect(pel)
        '''
        cv.rectangle(Im,(px,py), (px+pw, py+ph), (255,255,255), 2)
        cv.rectangle(Im,(rx,ry), (rx+rw, ry+rh), (255,50,50), 2)
        
        cv.imshow('wea', Im)
        cv.waitKey(1)
        '''
        if(py < ry+ph*3):
            cmd=-1
            
        if(py > ry+ph*3):
            cmd=1
            
            
    if(player==0):
        
        imAn=cv.cvtColor(Im, cv.COLOR_BGR2HSV)
        mask=cv.inRange(imAn,(130,5,5),(160,255,255))
        mask1=cv.inRange(imAn,(0,5,5),(15,255,255))
        mask2=cv.inRange(imAn,(150,5,5),(190,255,255))
        
        mask=cv.add(mask, mask1)
        mask=cv.add(mask, mask2)
        
        cont,wea=cv.findContours(mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
        raq=max(cont, key= cv.contourArea)
        rx,ry,rw,rh = cv.boundingRect(raq)
        
        pel=min(cont, key= cv.contourArea)
        px,py,pw,ph = cv.boundingRect(pel)
        '''
        cv.rectangle(Im,(px,py), (px+pw, py+ph), (255,255,255), 2)
        cv.rectangle(Im,(rx,ry), (rx+rw, ry+rh), (255,55,55), 2)
        
        cv.imshow('wea 2', Im)
        cv.waitKey(1)
        '''
        if(ry+ph*3 < py):
            cmd=1
            
        if(ry+ph*3 > py):
            cmd=-1
            
    power=random.randint(0,1)
    
    return cmd, power

svh = Pong(datos, 'Equipo 1')
svh.start()    