from pong import Pong
import numpy as np
import cv2
import random


def datos(Im, player, score, powerCount):


    cmd = 0
    power= 0

    cv2.imshow('pong 23b', Im)
    cv2.waitKey(1)

    return cmd, power

svh = Pong(datos, 'Parsival123456')
svh.start()    