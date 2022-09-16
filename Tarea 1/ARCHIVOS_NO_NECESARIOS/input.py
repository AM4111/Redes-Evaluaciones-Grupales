#Parte 1
from multiprocessing import Process
from matplotlib.widgets import Button
import multiprocessing
import time
from os import remove
import gc
import wave
import pyaudio

#Parte 2
import numpy as np
import scipy.fft
from scipy.fftpack import fft
import scipy.io.wavfile as waves
import matplotlib.pyplot as plt


#Para lograr ejecutar el programa necesita los siguientes módulos 
# pyaudio 0.2.12
# wave 0.0.2
# scipy 1.9.1
# matplotlib 3.5.3
# numpy 1.22.3

#El programa utiliza multi procesos ya que el modulo matplotlib no permite el uso de hilos 

#Grabar2
# Proceso 1
# En este método inicia la grabación del audio por medio del micrófono, este proceso depende
# del proceso 2 que cada 3 segundo envía la señal a la cola para que se guarden los frames 
# en un archivo y elimine sus datos para ahorrar memoria.
# Por último el método vuelve a leer el archivo con todos los frames guardados para así
# crear el archivo de audio.

def grabar2(q1,q2,q3,q4):
   #Crea el archivo donde se van a guardar los frames del audio en el dominio del tiempo.
   f = open ('dominio_tiempo.txt','wb')
   f.close()

   #Este fragmento de código fue obtenido de Thepythoncode: 
   #https://www.thepythoncode.com/article/play-and-record-audio-sound-in-python
   ##the file name output you want to record into
   filename = "recorded.wav"
   ## set the chunk size of 1024 samples
   chunk = 1024
   ## sample format
   FORMAT = pyaudio.paInt16
   ## mono, change to 2 if you want stereo
   channels = 2
   ## 44100 samples per second
   sample_rate = 44100
   record_seconds = 5
   ## initialize PyAudio object
   p = pyaudio.PyAudio()
   ## open stream object as input & output
   stream = p.open(format=FORMAT,
                  channels=channels,
                  rate=sample_rate,
                  input=True,
                  output=True,
                  frames_per_buffer=chunk)
   frames = []

   estado = "Grabar"
   while True:
      if q2.empty()==False:
               break
      if q4.empty()==False:
         estado=q4.get()
         
      if estado== "Grabar":
         frames.append(stream.read(chunk))
         
         if q3.empty()==False and q4.empty():
            f = open ('dominio_tiempo.txt','ab')
            f.write(b"".join(frames))
            f.close()
            del f, frames
            gc.collect()
            frames = []
            if q1.empty()==False:
               q1.get()
            q1.put("Entrada")
            salida=q3.get()
   
   ## stop and close stream
   stream.stop_stream()
   stream.close()
   ## terminate pyaudio object
   p.terminate() 


   if len(frames)>1:
    f = open ('dominio_tiempo.txt','ab')
    f.write(b"".join(frames))
    f.close()
   del f, frames
   gc.collect()

   f = open('dominio_tiempo.txt', 'rb')
   frames = f.read()
   f.close()

   #Este fragmento de código fue obtenido de Thepythoncode: 
   ## save audio file
   ## open the file in 'write bytes' mode
   wf = wave.open(filename, "wb")
   ## set the channels
   wf.setnchannels(channels)
   ## set the sample format
   wf.setsampwidth(p.get_sample_size(FORMAT))
   ## set the sample rate
   wf.setframerate(sample_rate)
   ## write the frames as bytes
   wf.writeframes(frames)
   ## close the file
   wf.close()

   while True:
      if q1.empty()==False:
         q1.get()
         break
   
    
    

def contar_samples(q2,q3):
    while True:
        if q2.empty()==False:
            break
        else:
            time.sleep(3)
            q3.put("Verificado")
    
    while True:
        if q2.empty()==False:
            q2.get()
            break
    
  
# To plot a graph for y = x
def plot1(event,q2):
    q2.put("Terminar")
    plt.close()

def plot2(event,q4):
   q4.put("Pausar")
   time.sleep(2)
  
def plot3(event,q4):
    q4.put("Grabar")
    



def principal(q1,q2,q3,q4):
    ## enable interactive mode
    plt.ion()
    ## creating subplot and figure
    plt.rcParams['figure.figsize'] = (10, 5)
    fig = plt.figure()
    ax = fig.add_subplot(211)
    ab = fig.add_subplot(212)

    axButn1 = plt.axes([0.1, 0.9, 0.1, 0.1])
    btn1 = Button(axButn1, label="Guardar", color='pink', hovercolor='tomato')
    btn1.on_clicked(lambda event: plot1(event,q2))

    #axButn2 = plt.axes([0.3, 0.9, 0.1, 0.1])
    #btn2 = Button(axButn2, label="Pausar", color='pink', hovercolor='tomato')
    #btn2.on_clicked(lambda event: plot2(event,q4))

    #axButn3 = plt.axes([0.5, 0.9, 0.1, 0.1])
    #btn3 = Button(axButn3, label="Grabar", color='pink', hovercolor='tomato')
    #btn3.on_clicked(lambda event: plot3(event,q4))

    ciclo=  True
    while ciclo:
        if q2.empty()==False:
                break
        if (q1.empty())== False:
            q1.get()

            f = open('dominio_tiempo.txt', 'rb')
            frames = f.read()
            f.close()
            sonido= np.frombuffer(frames, dtype=np.int16)

            ax.cla()
            ax.plot(sonido)

            n = len(sonido) 
            sonido = sonido / (2.**15)
            
            AudioFreq = fft(sonido) ## Calcular la transformada de Fourier
            ## La salida de la FFT es un array de numeros complejos
            ## los numeros complejos se representan en Magnitud y fase
            MagFreq = np.abs(AudioFreq) ## Valor absoluto para obtener la magnitud
            ## Escalar por el numero de puntos para evitar que los valores de magnitud
            ## dependan del tamaño de la señal o de su frecuencia de muestreo
            MagFreq = MagFreq / float(n)
            ab.cla()
            ab.plot(MagFreq[:len(MagFreq)//2]) ##Espectro de magnitud

            frecuencias = MagFreq.tobytes()
            f = open ('dominio_frecuencia.txt','wb')
            f.write(frecuencias)
            f.close()

            
            del sonido,frames, AudioFreq, f,MagFreq,frecuencias
            gc.collect()
            
        fig.canvas.draw()
        fig.canvas.flush_events()
    
    


    
    print("Guardando archivos y Limpiando colas")
    time.sleep(5)
    while q1.empty()==False:
        q1.get()

    while q2.empty()==False:
        q2.get()

    while q3.empty()==False:
        q3.get()

    while q4.empty()==False:
        q4.get()
    
    q2.put("X")
    time.sleep(0.2)
    q1.put("X")
    time.sleep(0.2)

def audio_bash():
    while True:

        audio = input("Escriba el nombre del audio sin la extension:  ")
        if (audio.find('.wav'))!=-1:
            print ("No puede tener la extension")
            pass

        elif (audio.find('.mp3'))!=-1:
            print ("Solo debe ser archivo wav")
            pass

        else:
            break
    try:
        archivo = audio + '.wav'
        fsonido, sonido = waves.read(archivo)
        
        izquierdo = sonido[:,0].copy()
        
        # SALIDA gráfica
        plt.rcParams['figure.figsize'] = (15, 5)
        plt.subplot(211)
        plt.plot(izquierdo)
        #plt.ylabel('Magnitud'); plt.title('1- Dominio del tiempo || 2- FFT total');
        
    #-------------------------------------------------
        

        izquierdo = izquierdo / (2.**15)
        n = len(izquierdo) 
        AudioFreq = fft(izquierdo) ## Calcular la transformada de Fourier
        ## La salida de la FFT es un array de numeros complejos
        ## los numeros complejos se representan en Magnitud y fase
        MagFreq = np.abs(AudioFreq) # Valor absoluto para obtener la magnitud
        ## Escalar por el numero de puntos para evitar que los valores de magnitud
        ## dependan del tamaño de la señal o de su frecuencia de muestreo
        MagFreq = MagFreq / float(n)
        plt.subplot(212)
        plt.plot(MagFreq) #Espectro de magnitud
        #plt.ylabel('Magnitud'); plt.title('FFT total');
        plt.show()

        frames = sonido[:,0].copy().tobytes()
        f = open ('dominio_tiempo.txt','wb')
        f.write(frames)
        f.close()


        frecuencias = MagFreq.tobytes()
        f = open ('dominio_frecuencia.txt','wb')
        f.write(frecuencias)
        f.close()
    except:
        print("Ocurrió un error al abrir el archivo")



def grabar():
    multiprocessing.freeze_support()
    q1 = multiprocessing.Queue()
    q2 = multiprocessing.Queue()
    q3 = multiprocessing.Queue()
    q4 = multiprocessing.Queue()
    procesos =[]
    colas=[q1,q2,q3,q4]

    p = Process(target=contar_samples, args=(q2,q3,))
    procesos.append(p)
    
    p = Process(target=grabar2, args=(q1,q2,q3,q4,))
    procesos.append(p)

    p = Process(target=principal, args=(q1,q2,q3,q4,))
    procesos.append(p)

    for i in procesos:
        i.start()

    for i in procesos:
        i.join()

    
    for i in colas:
        i.close()


    for i in procesos:
        i.close()

    


if __name__ == '__main__':
   while True:
      print("\n ")
      print("1. Para grabar inserte 1")
      print("2. Para usar un archivo ya creado inserte 2")
      print("3. Para ver el archivo Autrum reciente mente guardado inserte 3")
      print("4. Para salir inserte 4")
      x= input("Inserte la opción que desee: ")
      if x == "1":
         print("\n ")
         grabar()
         try:
            #remove("dominio_frecuencia.txt")
            #remove("dominio_tiempo.txt")
            #remove("recorded.wav")
            print("Se ha grabado con éxito")
         except:
            print("Hubo errores al crear los archivos")
            
      
      elif x== "2":
         print("\n ")
         audio_bash()
      
      elif x== "4":
         break

      else:
         print("\n ")
         print("Debe escribir la una opción valida ")

    
    