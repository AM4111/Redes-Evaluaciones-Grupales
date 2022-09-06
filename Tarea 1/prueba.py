# https://pypi.org/project/PyAudio/
# https://pypi.org/project/Wave/

from glob import glob
import threading
import wave
import pyaudio
import sounddevice as sd 
from scipy.io.wavfile import write 
import wavio as wv 

global estado
estado = True 

def grabar2():
    global estado
    freq = 44100
    
    duration = 5
    
    while estado:
        recording = sd.rec(int(duration * freq), samplerate=freq, channels=2) 
    
    sd.wait() 
    
    write("recording0.wav", freq, recording) 
    
    wv.write("recording1.wav", recording, freq, sampwidth=2)

def grabar():
    global estado
    #the file name output you want to record into
    filename = "recorded.wav"
    # set the chunk size of 1024 samples
    chunk = 1024
    # sample format
    FORMAT = pyaudio.paInt16
    # mono, change to 2 if you want stereo
    channels = 1
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
    print("Recording...")
    while estado:
        data = stream.read(chunk)
        # if you want to hear your voice while recording
        # stream.write(data)
        frames.append(data)
        record_seconds = 5
    
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



# Create a new thread
Thread1 = threading.Thread(target=grabar2)

# Create another new thread
Thread2 = threading.Thread(target=detener_grabacion)

# Start the thread
Thread1.start()

# Start the thread
Thread2.start()

# Wait for the threads to finish
Thread2.join()
Thread1.join()

