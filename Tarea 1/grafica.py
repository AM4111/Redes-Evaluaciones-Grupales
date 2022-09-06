#https://es.acervolima.com/crea-una-grabadora-de-voz-usando-python/
#http://blog.espol.edu.ec/telg1001/audio-en-formato-wav/
import numpy as np
import scipy.fft
from scipy.fftpack import fft

import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

def grafica_dominio_frecuencia():
    archivo = 'recording0.wav'
    fsonido, sonido = waves.read(archivo)

    x = np.array(sonido)  
    y = fft(x) 

    N = 500
    T = 1.0 / 600.0
    x = np.linspace(0.0, N*T, N)
    y = np.sin(60.0 * 2.0*np.pi*x) + 0.5*np.sin(90.0 * 2.0*np.pi*x)
    y_f = scipy.fft.fft(y)
    x_f = np.linspace(0.0, 1.0/(2.0*T), N//2)

    plt.plot(x_f, 2.0/N * np.abs(y_f[:N//2]))
    plt.show()

def graficar_dominio_del_tiempo():
    # INGRESO
    archivo = 'recording0.wav'
    fsonido, sonido = waves.read(archivo)
    print(sonido)

    izquierdo = sonido[:,0].copy()
    
    # SALIDA gráfica
    plt.plot(sonido)
    plt.show()


##def crearaudio():
    # PROCEDIMIENTO
    # Arreglos para datos con k muestras
    ##sonidofinal = np.zeros((len(izquierdo),2), dtype='int16')

    # SALIDA
    ##archivo = 'audiofinal.wav'
    ##waves.write(archivo, int(fsonido),sonidofinal)


#grafica_dominio_frecuencia()
graficar_dominio_del_tiempo()