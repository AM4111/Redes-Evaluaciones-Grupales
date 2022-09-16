#http://blog.espol.edu.ec/telg1001/audio-en-formato-wav/ #obtener datos de un audio 
#https://joserzapata.github.io/courses/mineria-audio/representacion_audio/ #Representación en Frecuencia
#https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.html #graficar normal
#https://www.geeksforgeeks.org/how-to-update-a-plot-on-same-figure-during-the-loop/ #graficar en loop
#https://code.tutsplus.com/es/tutorials/compressing-and-extracting-files-in-python--cms-26816 #comprimir archivos
#https://www.thepythoncode.com/article/play-and-record-audio-sound-in-python  #Grabar y guardar
import numpy as np
import scipy.fft
from scipy.fftpack import fft

import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

#from re import T
#Parte 1
#import sounddevice as sd 
#from scipy.io.wavfile import write 
#import wavio as wv 

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
    archivo = 'recorded.wav'
    fsonido, sonido = waves.read(archivo)

    

    izquierdo = sonido[:,0].copy()
    
    print((izquierdo))
    # SALIDA gráfica
    #plt.plot(izquierdo)
    #plt.show()

def graficas():
    global verificacion1
    # INGRESO
    #archivo = 'recorded.wav'
    #fsonido, sonido = waves.read(archivo)
    #print(sonido)
    
    f = open('dominio_tiempo.txt', 'rb')
    frames = f.read()
    f.close()
    sonido= np.frombuffer(frames, dtype=np.int16)

    #print(sonido)
    #izquierdo = sonido[:,1].copy()
    #sonido = izquierdo
    #print(len(sonido), "",len(izquierdo))
    # SALIDA gráfica
    plt.rcParams['figure.figsize'] = (15, 5)
    plt.subplot(211)
    plt.plot(sonido)
    plt.ylabel('Magnitud'); plt.title('1- Dominio del tiempo || 2- FFT total');
    
   #-------------------------------------------------
    f = open('dominio_frecuencia.txt', 'rb')
    frames = f.read()
    f.close()
    
    MagFreq= np.frombuffer(frames, dtype=np.float64)
    #print(MagFreq)

    #sonido = sonido / (2.**15)
    #n = len(sonido) 
    #AudioFreq = fft(sonido) # Calcular la transformada de Fourier
    # La salida de la FFT es un array de numeros complejos
    # los numeros complejos se representan en Magnitud y fase
    #MagFreq = np.abs(AudioFreq) # Valor absoluto para obtener la magnitud

    # Escalar por el numero de puntos para evitar que los valores de magnitud
    # dependan del tamaño de la señal o de su frecuencia de muestreo
    #MagFreq = MagFreq / float(n)
    plt.subplot(212)
    plt.plot(MagFreq) #Espectro de magnitud
    #plt.ylabel('Magnitud'); plt.title('FFT total');

    
    plt.show()


##def crearaudio():
    # PROCEDIMIENTO
    # Arreglos para datos con k muestras
    ##sonidofinal = np.zeros((len(izquierdo),2), dtype='int16')

    # SALIDA
    ##archivo = 'audiofinal.wav'
    ##waves.write(archivo, int(fsonido),sonidofinal)


#grafica_dominio_frecuencia()
graficas()