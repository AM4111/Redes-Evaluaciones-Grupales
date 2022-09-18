#http://blog.espol.edu.ec/telg1001/audio-en-formato-wav/ #obtener datos de un audio 
#https://joserzapata.github.io/courses/mineria-audio/representacion_audio/ #Representación en Frecuencia
#https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.html #graficar normal
#https://www.geeksforgeeks.org/how-to-update-a-plot-on-same-figure-during-the-loop/ #graficar en loop
#https://code.tutsplus.com/es/tutorials/compressing-and-extracting-files-in-python--cms-26816 #comprimir archivos
#https://www.thepythoncode.com/article/play-and-record-audio-sound-in-python  #Grabar y guardar

#Parte 1
#from curses import flash
from multiprocessing import Process
from turtle import onclick
from matplotlib.widgets import Button
from os import remove
import multiprocessing
import time
import wave
import gc
import pyaudio

##Parte 2
import numpy as np
import scipy.fft
from scipy.fftpack import fft
import scipy.io.wavfile as waves
import matplotlib.pyplot as plt

#Parte 4
import os
import zipfile
import pathlib

#Para lograr ejecutar el programa necesita los siguientes módulos 
# pyaudio 0.2.12
# wave 0.0.2
# scipy 1.9.1
# matplotlib 3.5.3
# numpy 1.22.3



###############################################################

#### PARTE 1 DEL PROGRAMA - GRABACIÓN Y GRÁFICAS  #############

###############################################################
#El programa utiliza multi procesos ya que el modulo matplotlib no permite el uso de hilos 

#Grabar2
# Proceso 1
# En este método inicia la grabación del audio por medio del micrófono, este proceso depende
# del proceso 2 que cada 3 segundo envía la señal a la cola para que se envíen los frames 
# a través de la cola
# Por último el método guarda todos los frames como un archivo de audio

def grabar2(q1,q2,q3,q4):
    #Este fragmento de código fue obtenido de Thepythoncode: 
    #https://www.thepythoncode.com/article/play-and-record-audio-sound-in-python
    #the file name output you want to record into
    filename = "recorded.wav"
    # set the chunk size of 1024 samples
    chunk = 1024
    # sample format
    FORMAT = pyaudio.paInt16
    # mono, change to 2 if you want stereo
    channels = 2
    # 44100 samples per second
    sample_rate = 4000
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

    #Esta parte fue modificada por Jocxan Sandi 
    #Se utilizan las colas como banderas para comunicar los 3 diferentes procesos
    estado = "Pausar"
    flag = False
    while True:
        if q2.empty()==False: #Esta es la cola de estado, en caso de que detecte una entrada es que
            #el estado cambió a terminar y terminan todos los procesos
                break
        if q4.empty()==False: #Esta cola es de mejo de la grabación, obtiene si hay que pausar 
            #o seguir grabando
            estado=q4.get()
            
        if estado== "Grabar": #Cuando el estado de grabación se grabar entra
            
            frames.append(stream.read(chunk)) #lee lo s datos de entrada del micrófono 
            #los guarda en los frames
            
            if q3.empty()==False: #Cuando el proceso 2 envía la señal entonces se envían los datos
                #de frames al proceso 3 para graficar estos
                flag = True
                sonido= np.frombuffer(b"".join(frames), dtype=np.int16) #une los frames y los convierte a un array de numpy de 16 bits
                if q1.empty()==False:
                    q1.get()
                q1.put(sonido)  #Envía el sonido para el proceso 3
                del sonido
                gc.collect()
                salida=q3.get() #Saca la confirmación de los 3 segundos de la cola

    if q1.empty()==False:
        time.sleep(2)
    
    if flag:
    #Guarda los frames del dominio del tiempo en un archivo
        f = open ('dominio_tiempo.txt','wb')
        f.write(b"".join(frames))
        f.close()

        #Este fragmento de código fue obtenido de Thepythoncode
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

    #Espera la confirmación para terminar el proceso
    #Esto porque necesitan terminar en el orden que iniciaron
    while True:
        if q1.empty()==False:
            q1.get()
            break
    
    
    
#Timer
#Proceso 2
#En este proceso se lleva la cuenta del tiempo a esperar para realizar cada gráfica
#Envía la señal para que el proceso 1 envíe la información al proceso 3
def timer(q2,q3):
    while True:
        if q2.empty()==False: #Cola de estado de finalización de todos los procesos 
            break
        else:
            time.sleep(3)
            q3.put("Verificado") #Pone la confirmación en la cola para el proceso 1
    
    #Espera la confirmación para terminar el proceso
    #Esto porque necesitan terminar en el orden que iniciaron
    while True:
        if q2.empty()==False:
            q2.get()
            break
    


   
  
#Parte de las funciones de los bonotes en las gráficas para el proceso 3 
def plot1(event,q2): #Termina la ejecución de los procesos
    q2.put("Terminar")
    plt.close()

def plot2(event,q4): #Pone en Pausa la grabación
    q4.put("Pausar")

  
def plot3(event,q4): #Pone en Play la grabación
    q4.put("Grabar")
    
    
#Grafica_tiempo_real 
#Proceso 3
#En este método se realizan las gráficas del sonido en el dominio del tiempo y 
# la Representación en Frecuencia

#Para esta parte se utilizaron dos fragmentos de código de diferentes fuentes
#La primera está basada en un código de Joser Zapata de:
#https://joserzapata.github.io/courses/mineria-audio/representacion_audio/
#La parte que se utiliza aquí es para realizar el análisis de Fourier al sonido

#La segunda parte está basada en un código de Geeksforgeeks y modificada por Jocxan Sandí:
#https://www.geeksforgeeks.org/how-to-update-a-plot-on-same-figure-during-the-loop/
#La parte que se utiliza aquí es para realizar la gráfica del dominio en el tiempo 
#y la frecuencia

def grafica_tiempo_real(q1,q2,q3,q4):
    
    #Este fragmento de código fue obtenido de Geeksforgeeks
    # enable interactive mode
    plt.ion()
    # creating subplot and figure
    plt.rcParams['figure.figsize'] = (10, 5)
    fig = plt.figure()
    ax = fig.add_subplot(211)
    ab = fig.add_subplot(212)

    #Se agregan unos botones para lograr Guardar, Pausar y Continuar Grabando
    axButn1 = plt.axes([0.1, 0.9, 0.1, 0.1])
    btn1 = Button(axButn1, label="Guardar", color='pink', hovercolor='tomato')
    btn1.on_clicked(lambda event: plot1(event,q2))

    axButn2 = plt.axes([0.3, 0.9, 0.1, 0.1])
    btn2 = Button(axButn2, label="Pausar", color='pink', hovercolor='tomato')
    btn2.on_clicked(lambda event: plot2(event,q4))

    axButn3 = plt.axes([0.5, 0.9, 0.1, 0.1])
    btn3 = Button(axButn3, label="Grabar", color='pink', hovercolor='tomato')
    btn3.on_clicked(lambda event: plot3(event,q4))
    flag = False


    

    while True:
        if q2.empty()==False: #Esta es la cola de estado, en caso de que detecte una entrada es que
            #el estado cambió a terminar y terminan todos los procesos
                break
        if (q1.empty())== False: #Cuando el proceso 1 envía los datos entra aquí para hacer la representacións
            sonido = q1.get() #obtiene el sonido
            
            ax.clear()
            ab.clear()
            ax.cla()
            gc.collect()

            ax.plot(sonido) #hace el plot del dominio en el tiempo
            
            #Este fragmento de código fue obtenido de Joser Zapata 
            sonido = sonido / (2.**15)
            n = len(sonido) 
            AudioFreq = fft(sonido) # Calcular la transformada de Fourier
            # La salida de la FFT es un array de números complejos
            # los números complejos se representan en Magnitud y fase
            MagFreq = np.abs(AudioFreq) # Valor absoluto para obtener la magnitud

            # Escalar por el numero de puntos para evitar que los valores de magnitud
            # dependan del tamaño de la señal o de su frecuencia de muestreo
            MagFreq = MagFreq / float(n)
            
            ab.cla() 
            gc.collect()
            ab.plot(MagFreq) #hace el plot del Espectro de magnitud o Fourier

            del sonido, AudioFreq
            gc.collect()
            flag = True
            
        fig.canvas.draw()
        fig.canvas.flush_events()
    
    if flag:
        #Guarda los datos del espectro de frecuencia 
        frecuencias = MagFreq.tobytes()
        f = open ('dominio_frecuencia.txt','wb')
        f.write(frecuencias)
        f.close()


    #Librera las colas para terminar los procesos
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
    
    #Envía una señal para que el proceso 2 termine
    q2.put("X")
    time.sleep(0.2)
    #Envía una señal para que el proceso 1 termine
    q1.put("X")
    time.sleep(0.2)
    #Termina el proceso 3


#Grabar_graficar
#Método que inicializa los 3 procesos 
def grabar_graficar():
    multiprocessing.freeze_support()
    #Se crean las colas que serán utilizadas por los diferentes procesos
    q1 = multiprocessing.Queue()  #Guarda los datos del dominio del tiempo
    q2 = multiprocessing.Queue()  #Sirve como bandera para terminar los procesos
    q3 = multiprocessing.Queue()  #Sirve como bandera entre el proceso 1 y 2 es el que lleva el tiempo y permite el envío de datos
    q4 = multiprocessing.Queue()  #Sirve como bandera para saber si se Graba o se Pausa 
    procesos =[]
    colas=[q1,q2,q3,q4]

    p = Process(target=timer, args=(q2,q3,)) #Crea el proceso del timer
    procesos.append(p)
    
    p = Process(target=grabar2, args=(q1,q2,q3,q4,)) #Crea el proceso del grabar
    procesos.append(p)

    p = Process(target=grafica_tiempo_real, args=(q1,q2,q3,q4,)) #Crea el proceso de graficar
    procesos.append(p)

    #Inicia los procesos 
    for i in procesos:
        i.start()

    #Espera que los procesos terminen
    for i in procesos:
        i.join()

    #Cierra las colas
    for i in colas:
        i.close()

    #Termina los procesos
    for i in procesos:
        i.close()

    archivo = get_nombre_atm(0)
    comprimir("",archivo) #Comprime y elimina los archivos

##########################################################################################

#### PARTE 2 DEL PROGRAMA - GRABACIÓN Y GRÁFICAS DE UN ARCHIVO YA EXISTENTE  #############

##########################################################################################

#audio_bash
#Método que recibe el nombre de un archivo.wav y realiza las gráficas en el dominio del tiempo y la frecuencia
#También utiliza la base del código de Joser Zapata
def audio_bash():
    try:
        audio =get_nombre_audio()
        #Lee los datos del archivo y los guarda en sonido
        archivo = audio + '.wav'
        fsonido, sonido = waves.read(archivo)         
        MagFreq=graficas_parte_2(0,[sonido]) #Realiza las gráficas
        
        #Guarda los datos del dominio del tiempo en un archivo
        frames = sonido[:,0].copy().tobytes()
        f = open ('dominio_tiempo.txt','wb')
        f.write(frames)
        f.close()

        #Guarda los datos del dominio de frecuencia en un archivo
        frecuencias = MagFreq.tobytes()
        f = open ('dominio_frecuencia.txt','wb')
        f.write(frecuencias)
        f.close()

        nombre =get_nombre_atm(0)
        comprimir(archivo,nombre)


    except:
        print("Ocurrió un error al abrir el archivo")

#get_nombre_audio
#método para obtener el nombre del archivo de audio existente solicitando al usuario
def get_nombre_audio():
    #Recibe el nombre del archivo
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
    return audio #devuelve el nombre del audio



######################################################################

#### PARTE 3 DEL PROGRAMA - MUESTRA DE LOS ARCHIVOS ATM  #############

######################################################################
def muestras_atm():
    try:
        archivo = get_nombre_atm(1)
        archivo = archivo
        descomprimir(archivo)

        f = open('dominio_tiempo.txt', 'rb')
        frames = f.read()
        f.close()
        sonido= np.frombuffer(frames, dtype=np.int16)


        f = open('dominio_frecuencia.txt', 'rb')
        frames = f.read()
        f.close()
        
        MagFreq= np.frombuffer(frames, dtype=np.float64)

        print("bandera1")
        graficas_parte_2(1,[sonido,MagFreq])
        print("bandera2")
        remove("dominio_frecuencia.txt")
        remove("dominio_tiempo.txt")
    except:
        print("Problemas con abrir archivos")

#get_nombre_atm
#método para obtener el nombre del archivo atm  solicitando al usuario
def get_nombre_atm(tipo):
    if tipo == 1:

        while True:
            audio = input("Escriba el nombre del archivo atm para abrir, sin la extension:  ")
            if (audio.find('.atm'))!=-1:
                print ("No puede tener la extension")
                pass

            elif (audio.find('.zip'))!=-1:
                print ("Solo debe ser archivo atm")
                pass

            else:
                break
        return audio+".atm"
    else:
        ruta= pathlib.Path(__file__).parent.absolute()
        valido = True
        while True:
            audio = input("Escriba el nombre del archivo atm a guardar, sin la extension:  ")
            archivos =os.listdir(ruta)

            for i in archivos:
                if i==audio+".atm":
                    print("entra")
                    valido= False

            if (audio.find('.atm'))!=-1:
                print ("No puede tener la extension")
                pass

            elif (audio.find('.zip'))!=-1:
                print ("Solo debe ser archivo atm")

                pass
            
            elif valido== False:
                print ("Ya existe un archivo atm con este nombre")
                valido=True
                pass

            else:
                break
        return audio+".atm"

#####################################################

#### COMPRIMIR Y DESCOMPRIMIR ARCHIVOS  #############

#####################################################
# Código obtenido de Monty Shokeen
# https://code.tutsplus.com/es/tutorials/compressing-and-extracting-files-in-python--cms-26816

def comprimir(audio,nombre):
    try:
        bandera = False
        if audio == "":
            audio= "recorded.wav"
            bandera = True

        autrum = zipfile.ZipFile(nombre, 'w')
        ruta= pathlib.Path(__file__).parent.absolute()
    
        autrum.write(os.path.join(ruta, "dominio_frecuencia.txt"), os.path.relpath(os.path.join(ruta,"dominio_frecuencia.txt"), ruta), compress_type = zipfile.ZIP_DEFLATED)
        autrum.write(os.path.join(ruta, "dominio_tiempo.txt"), os.path.relpath(os.path.join(ruta,"dominio_tiempo.txt"), ruta), compress_type = zipfile.ZIP_DEFLATED)
        autrum.write(os.path.join(ruta, audio), os.path.relpath(os.path.join(ruta,audio), ruta), compress_type = zipfile.ZIP_DEFLATED)
        
        autrum.close()

        remove("dominio_frecuencia.txt")
        remove("dominio_tiempo.txt")
        if (bandera==True):
            remove("recorded.wav")
    except:
        print("Hubo problemas al comprimir los archivos en un .atm")

def descomprimir(nombre):
    try:
        ruta= pathlib.Path(__file__).parent.absolute()
        autrum = zipfile.ZipFile(str(ruta)+"//"+nombre)
        autrum.extractall(ruta)
        
        autrum.close()
    except:
        print("No existe este archivo .atm")
    
def graficas_parte_2(tipo,datos):
    
    sonido = datos[0]
    plt.rcParams['figure.figsize'] = (15, 5)
#-------------------------------------------------
    if tipo == 0: #Si es un gráfica desde un archivo ya existente
        izquierdo = sonido[:,0].copy() #Copia solo un canal del audio
        # SALIDA gráfica del dominio en el tiempo
        plt.subplot(211)
        plt.plot(izquierdo)

        #plt.ylabel('Magnitud'); plt.title('1- Dominio del tiempo || 2- FFT total');
        # SALIDA gráfica del espectro del frecuencia FFT
        #Este fragmento de código fue obtenido de Joser Zapata
        izquierdo = izquierdo / (2.**15)
        n = len(izquierdo) 
        AudioFreq = fft(izquierdo) # Calcular la transformada de Fourier
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

        return MagFreq
    else: #Si es un gráfica desde un archivo.atm
        # SALIDA gráfica del dominio en el tiempo
        
        plt.subplot(211)
        plt.plot(sonido)

        MagFreq = datos[1]
        plt.subplot(212)
        plt.plot(MagFreq) #Espectro de magnitud
        #plt.ylabel('Magnitud'); plt.title('FFT total');

        
        plt.show()
        
        return True


#####################################################

############## MAIN DEL PROGRAMA  ###################

#####################################################

if __name__ == '__main__':
    
    while True:
        print("\n ")
        print("1. Para grabar inserte 1")
        print("2. Para ver el archivo Autrum inserte 2")
        print("3. Para usar un archivo de audio existente inserte 3")
        print("4. Para descomprimir un Autrum 4")
        print("5. Para salir inserte 5")
        x= input("Inserte la opción que desee: ")
        print("\n ")
        if x == "1":
            grabar_graficar() #Inicializa los multiples procesos
            print("Se ha grabado con éxito")
        
        elif x== "2":
            muestras_atm()


        elif x== "3":
            audio_bash()

        elif x=="4":
            try:
                archivo = get_nombre_atm(1)
                descomprimir(archivo)
            except:
                print("No se puede descomprimir el archivo")
        
        elif x== "5":
            break

        else:
            print("\n ")
            print("Debe escribir la una opción valida ")

    
    