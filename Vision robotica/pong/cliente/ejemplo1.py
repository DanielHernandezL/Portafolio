from pong import Pong
import numpy as np
import cv2
import random


def datos(Im, player, score, powerCount):

    cmd = random.choice([-1,0,1])
    power= 0

    return cmd, power

svh = Pong(datos, 'Parsival123456')
svh.start()    