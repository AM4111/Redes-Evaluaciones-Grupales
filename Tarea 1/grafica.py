#https://es.acervolima.com/crea-una-grabadora-de-voz-usando-python/
#http://blog.espol.edu.ec/telg1001/audio-en-formato-wav/
import numpy as np
import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

# INGRESO
archivo = 'recorded.wav'
fsonido, sonido = waves.read(archivo)

izquierdo = sonido[:,0].copy()

# SALIDA gráfica
plt.plot(izquierdo)
plt.show()