import numpy as np
import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

# INGRESO
archivo = 'recording0.wav'
fsonido, sonido = waves.read(archivo)

izquierdo = sonido[:,0].copy()

# SALIDA gráfica
plt.plot(izquierdo)
plt.show()