##Parte 1
import time
from glob import glob
import threading
import wave
import pyaudio
#import sounddevice as sd 
#from scipy.io.wavfile import write 
#import wavio as wv 

##Parte 2
import numpy as np
import scipy.fft
from scipy.fftpack import fft
import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

global estado,verificacion1, verificacion2
verificacion1 = False
estado = True 

def grabar():
    global estado
    #the file name output you want to record into
    filename = "recorded.wav"
    # set the chunk size of 1024 samples
    chunk = 1024
    # sample format
    FORMAT = pyaudio.paInt16
    # mono, change to 2 if you want stereo
    channels = 2
    # 44100 samples per second
    sample_rate = 44100
    record_seconds = 5
    # initialize PyAudio object
    p = pyaudio.PyAudio()
    # open stream object as input & output
    stream = p.open(format=FORMAT,
                    channels=channels,
                    rate=sample_rate,
                    input=True,
                    output=True,
                    frames_per_buffer=chunk)
    frames = []
    print("Grabando...")
    while estado:
        data = stream.read(chunk)
        # if you want to hear your voice while recording
        # stream.write(data)
        frames.append(data)
        record_seconds = 5
    
    print("Grabación terminada")
    print("Su grabación se encuentra en el archivo: recorded.wav")

    # stop and close stream
    stream.stop_stream()
    stream.close()
    # terminate pyaudio object
    p.terminate()
    # save audio file
    # open the file in 'write bytes' mode
    wf = wave.open(filename, "wb")
    # set the channels
    wf.setnchannels(channels)
    # set the sample format
    wf.setsampwidth(p.get_sample_size(FORMAT))
    # set the sample rate
    wf.setframerate(sample_rate)
    # write the frames as bytes
    wf.writeframes(b"".join(frames))
    # close the file
    wf.close()

def detener_grabacion():
    global estado
    print("Escriba cualquier letra + Enter, para terminar de grabar.")
    x=input()
    estado = False

def graficas():
    global verificacion1
    # INGRESO
    archivo = 'recorded.wav'
    fsonido, sonido = waves.read(archivo)
    #print(sonido)

    izquierdo = sonido[:,0].copy()
    
    # SALIDA gráfica
    plt.subplot(211)
    plt.plot(sonido)
    plt.ylabel('Magnitud'); plt.title('1- Dominio del tiempo || 2- FFT total');
    
   #-------------------------------------------------
    sonido = sonido / (2.**15)
    n = len(sonido) 
    AudioFreq = fft(sonido) # Calcular la transformada de Fourier
    # La salida de la FFT es un array de numeros complejos
    # los numeros complejos se representan en Magnitud y fase
    MagFreq = np.abs(AudioFreq) # Valor absoluto para obtener la magnitud

    # Escalar por el numero de puntos para evitar que los valores de magnitud
    # dependan del tamaño de la señal o de su frecuencia de muestreo
    MagFreq = MagFreq / float(n)
    plt.subplot(212)
    plt.plot(MagFreq) #Espectro de magnitud
    #plt.ylabel('Magnitud'); plt.title('FFT total');
    plt.show()
    

def main_grabar():
    # Creación del hilo grabar
    Thread1 = threading.Thread(target=grabar)

    # Creación del hilo para detener la grabación
    Thread2 = threading.Thread(target=detener_grabacion)

    # Inicia los hilos
    Thread1.start()
    Thread2.start()

    # Espera que la grabación termine
    Thread2.join()
    Thread1.join()


graficas()


