import os
import zipfile
import pathlib
def comprimir():
    audio= "recorded.wav"
    autrum = zipfile.ZipFile('archivo.atm', 'w')
    ruta= pathlib.Path(__file__).parent.absolute()
   
    autrum.write(os.path.join(ruta, "dominio_frecuencia.txt"), os.path.relpath(os.path.join(ruta,"dominio_frecuencia.txt"), ruta), compress_type = zipfile.ZIP_DEFLATED)
    autrum.write(os.path.join(ruta, "dominio_tiempo.txt"), os.path.relpath(os.path.join(ruta,"dominio_tiempo.txt"), ruta), compress_type = zipfile.ZIP_DEFLATED)
    autrum.write(os.path.join(ruta, audio), os.path.relpath(os.path.join(ruta,audio), ruta), compress_type = zipfile.ZIP_DEFLATED)
    
    autrum.close()

def descomprimir():
    ruta= pathlib.Path(__file__).parent.absolute()
    autrum = zipfile.ZipFile(str(ruta)+"//primero.atm")
    autrum.extractall(ruta)
    
    autrum.close()


descomprimir()
#comprimir()