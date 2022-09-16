import os
import zipfile
import pathlib
ruta= pathlib.Path(__file__).parent.absolute()

archivos=(os.listdir(ruta), "\n")

for i in archivos[0]:
    if i=="primero.atm":
        print("hay")