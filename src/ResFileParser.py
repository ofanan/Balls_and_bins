import os, numpy as np
import pylab, matplotlib, seaborn, matplotlib.pyplot as plt
numBalls = 10**6
lgLg = np.log(np.log (numBalls))
print (f'u.a.r={np.log (numBalls)/lgLg}, P of 2={lgLg}')