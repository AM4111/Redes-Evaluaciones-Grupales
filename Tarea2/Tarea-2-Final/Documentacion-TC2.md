Tecnológico de Costa Rica.

Escuela de Ingeniería en Computación.

IC: 7602-Redes - 2 Semestre 2022.

2018086509 - Jocxan Sandi Batista.

---
# DOCUMENTACIÓN - TAREA CORTA 2

## Índice

- Servidor y calculadora
- Cliente
- Manual de usuario
- Especificación de carpetas
- Crear elementos
- Referencias


**NOTA:** EL PROGRAMA ES EJECUTADO EN UBUNTU.

## Servidor y calculadora

Se usa un servidor TCP que espera la conexión de un cliente por medio de un socket, este ejecuta las solicitudes que le envía el cliente y le da una respuesta. 

## Cliente

Para realizar un cliente y poder hacer uso de la calculadora se utiliza la imagen de ubuntu con unas herramientas para realizar consultas al servidor por medio de telnet.

Herramientas instaladas en la imagen de ubuntu. Esta se puede encontrar en la carpeta Ubuntu, se hizo una imagen y se subió para el uso en helm.

<pre><code>
RUN apt-get update -y
RUN apt install iputils-ping -y
RUN apt-get install telnet -y
RUN apt install net-tools -y a
</code></pre>

## Manual de usuario

- Para obtener el programa utilizar los siguientes comandos en la terminal de ubuntu:
<pre><code>
helm repo add calculadora https://jocxans7.github.io/Calculadora/
helm install --dry-run helm calculadora/tarea
helm install helm calculadora/tarea
</code></pre>

- Una vez se haya instalado, abrir docker-desktop saldrá un contenedor con el siguiente nombre **k8s_ubuntu_calculadora-**. Una vez se haya identificado el contenedor abrir el terminal. 

- Otra forma de abrir este terminal es con el siguiente comando en la terminal de ubuntu **docker exec -it id-container  bin/sh**. Para saber este id-container escribir en la terminal de ubuntu **docker ps** y aquí les saldrá sus contenedores, este programa instala 2, pero estamos con el de nombre **k8s_ubuntu_calculadora-** por lo que les saldrá y su id-container.

- Una vez este en el terminal del contenedor escribir **telnet 127.0.0.1 9666**. Este los conectará al server y podrán hacer consultas a la calculadora. 

### Ejemplos de consultas:
1. GET BROADCAST IP 10.8.2.5 MASK /29
2. GET BROADCAST IP 172.16.0.56 MASK 255.255.255.128
3. GET NETWORK NUMBER IP 10.8.2.5 MASK /29
4. GET NETWORK NUMBER IP 172.16.0.56 MASK 255.255.255.128


**NOTA:** TENER CUIDADO CON LOS ESPACIOS EN BLANCO Y RESPETAR LOS ESPACIOS ENTRE PARÁMETROS.


## Especificación de carpetas

1. Imagenes: Carpeta de las imágenes usada en esta documentación. 
2. Server: Contiene el archivo **server2.c** en el cual se encuentra el server de la calculadora y un **dockerfile** de como se realizó la imagen del servidor. 
3. Ubuntu: Contiene un **dockerfile** de como se hizo el cliente. 
4. Tarea2: La carpeta donde se encuentran los archivos para hacer el helm chart.

- El archivo principal se encuentra en tarea2/tarea/templates/deployment.yaml

## Crear elementos

1. Server-tcp: **Se sube al docker hub**

<pre><code>
docker build -t jocxans7/server-tcp .
</code></pre>

2. Cliente: **Se sube al docker hub**
<pre><code>
docker build -t jocxans7/ubuntu-cliente .
</code></pre>

3. Helm Chart: **Se sube al github pages**

<pre><code>
helm package tarea/ #Empaqueta los archivos del helm  chart
helm repo index .   #Crea un archivo index 
</code></pre>


## Referencias 
> https://www.youtube.com/watch?v=DCoBcpOA7W4&t=929s&ab_channel=PeladoNerd

> https://www.youtube.com/watch?v=5-Qcig2_8xo&t=540s&ab_channel=NullSafeArchitect

> https://www.youtube.com/watch?v=l-UZQjdPUAI&ab_channel=FernandoHerrera

> https://www.youtube.com/watch?v=jScW2XaS8uI&ab_channel=PeladoNerd

> https://www.youtube.com/watch?v=wyRfN5oLzx4&ab_channel=PeladoNerd

> https://github.com/pablokbs/peladonerd

> https://kubernetes.io/docs/tasks/manage-kubernetes-objects/kustomization/

> https://computingforgeeks.com/deploy-ubuntu-pod-in-kubernetes-openshift/

> https://refactorizando.com/como-crear-helm-chart-kubernetes/

> https://kubernetes.io/es/docs/concepts/workloads/controllers/deployment/

> https://docs.docker.com/engine/reference/commandline/exec/

> https://docs.docker.com/compose/environment-variables/

> https://www.educative.io/answers/splitting-a-string-using-strtok-in-c

> https://hub.docker.com/_/gcc

> https://hub.docker.com/_/ubuntu


