#https://www.geeksforgeeks.org/how-to-update-a-plot-on-same-figure-during-the-loop/
from math import pi
import matplotlib.pyplot as plt
import numpy as np
import time
import scipy.io.wavfile as waves
# generating random data values
archivo = 'recording0.wav'
fsonido, sonido = waves.read(archivo)

x = sonido[:,0].copy()
y = sonido[:,1].copy()
print(len(x))
# enable interactive mode
plt.ion()


#'numpy.float32'> class 'numpy.ndarray'
# creating subplot and figure
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(x[:1000])


# looping
n=1000
while (n+1000 < len(x)):
	ax.cla()
	ax.plot(x[n:n+1000])
	n+=1000
	fig.canvas.draw()
	fig.canvas.flush_events()
	time.sleep(0.1)
    	