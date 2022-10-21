Tecnológico de Costa Rica<br> 
Escuela de Ingeniería en Computación<br> 
IC: 7602-Redes  - 2 Semestre 2022 <br> 
2018093728 - Paula Mariana Bustos Vargas
2018086509 - Jocxan Sandi Batista
 
______________________
<center> <h1> Proyecto 1 </h1> </center> 

Para este proyecto se realiza la implementacion dos pequeñas redes virtuales que exponen diferentes servicios, donde la toda la configuración esta implementada mediante Docker y Docker Compose (todo debe estar completamente automatizado)

Para la elavoracion del proyecto se conto con un <u> Repositorio de github </u> el cual es:

 - Poner el enlace al repositorio

Para la elavoración del proyecto se decidio utilizar el sistema operativo Ubuntu.

<u> Diagrama de arquitectura </u> 

<u> Diagrama de flujo</u> 

______________________

<h2> Partes del Proyecto </h2>

<u> Redes </u> 

En primera instancia se solicita la configuracion de las redes esperadas las cuales son las siguiente:

| Nombre | Número de red | Máscara |Comando|
| -- | -- | -- | -- |
| LAN Virtual 1 | 10.0.0.0| 255.255.255.0 | <pre><code>docker network create LANVirtual1 --subnet=10.0.0.0/24 </code></pre>|
| LAN Virtual 2 | 10.0.1.0 |255.255.255.0 | <pre><code>docker network create LANVirtua2 --subnet=10.0.1.0/24 </code></pre>|

Para realizar la automatizacion con docker, se realiza una modificacion al archivo docker-compose.yaml en el cual tendra lo siguiente:

<pre><code>
version: '2'

networks:
  # config LanV1
  LANVirtual1:
    #driver: bridge
    driver: macvlan
    ipam:
      driver: default
      config:
        - subnet: 10.0.0.0/24
        #no permite que sea 10.0.0.1
        - gateway: 10.0.0.99

  # config LanV2
  LANVirtual2:
    #driver: bridge
    driver: macvlan
    ipam:
      driver: default
      config:
        - subnet: 10.0.1.0/24
        #no permite que sea 10.0.1.1
        - gateway: 10.0.1.99
 </code></pre>

Y para ejecutarlo se debe aunque va a mencionar que le tiene servicios seleccionados

<pre><code>
docker compose up
</code></pre>

<u> Routers </u> 

Se deben de crear dos routers con las siguientes especificaciones:

-  Proporcionar acceso a Internet mediante NAT:
   -  Router2 para LAN Virtual 2 
   -  Router2 para LAN Virtual 2 

Por lo cual la imagen a utilizar como base sera kmanna/nat-router:

https://hub.docker.com/r/kmanna/nat-router#:~:text=Docker%20nat%2Drouter,using%20pipework%20to%20create%20eth1.

**Router1**

Proporcionar acceso a Internet a LAN Virtual 1 mediante NAT.

El tráfico de salida permitido será únicamente mediante UDP y los puertos TCP/80 y TCP/443.

 Deberá permitir el acceso externo mediante puertos TCP/80, TCP/443, TCP/3128, TCP/8443, UDP/53, TCP/53 

- TCP/80 y TCP/443 se debe enrutar al Proxy Reverso.
- TCP/3128 se debe enrutar al Web Cache.
- TCP/8443 se debe enrutar al VPN.
- TCP/53 y UDP/53 deben ser enrutados al DNS.

Doc del DockerFile
<pre><code>
# use the ubuntu base image
#FROM ubuntu:latest
FROM kmanna/nat-router

# Router 1
WORKDIR /router1

COPY ./script.sh ./
</code></pre>

Doc  script.sh
<pre><code>
#TCP
#iptables -A INPUT  -p tcp -m multiport --dports 53,80,443,3128,8443 -j ACCEPT

sudo iptables-legacy -A INPUT -p tcp --sport 53 -j ACCEPT
sudo iptables-legacy -A INPUT -p tcp --sport 80 -j ACCEPT
sudo iptables-legacy -A INPUT -p tcp --sport 443 -j ACCEPT
sudo iptables-legacy -A INPUT -p tcp --sport 3128 -j ACCEPT
sudo iptables-legacy -A INPUT -p tcp --sport 8443 -j ACCEPT

#UDP
#iptables -A INPUT  -p upd --dports 53 -j ACCEPT

sudo iptables-legacy -A INPUT -p upd --sport 53 -j ACCEPT


</code></pre>

Creamos la imagen del router
<pre><code>
 docker image build -t router:1.0 .
</code></pre>


https://unrouted.io/2017/08/15/docker-firewall/

https://medium.com/swlh/manage-iptables-firewall-for-docker-kubernetes-daa5870aca4d


**Router2**

Permitirá acceso del VPN hacia cualquier host en LAN Virtual 1 e Internet.

Permitirá acceso desde cualquier host en LAN Virtual 2 a cualquier host en la LAN Virtual 1 en los puertos TCP/80, TCP/443 y el protocolo ICMP. 




Doc del DockerFile
<pre><code>
# use the ubuntu base image
#FROM ubuntu:latest
FROM kmanna/nat-router

# Router 1
WORKDIR /router2

COPY ./script.sh ./
</code></pre>

Doc  script.sh
<pre><code>
#TCP
#iptables -A INPUT  -p tcp -m multiport --dports 80,443 -j ACCEPT

sudo iptables-legacy -A INPUT -p tcp --sport 80 -j ACCEPT
sudo iptables-legacy -A INPUT -p tcp --sport 443 -j ACCEPT

#UDP
#iptables -A INPUT  -p upd --dports 53 -j ACCEPT

sudo iptables-legacy -A INPUT -p upd --sport 53 -j ACCEPT

</code></pre>

<u> Archivo docker-compose.yaml</u>

ports:
  - "53/udp"
  - "80:443/tcp"

Para la creación de los routes que se comportan com

<u> DNS </u> 

<u> Clientes </u> 

<u> Web Server 1 y Web Server 2 </u> 

Deberán implementar un Web Server en Apache, el mismo expone una simple página

**Consutruccion de las imagenes de los servidores**
Se contrulle la imagen del server 1 
<pre><code>docker image build -t helloworld:1.0 .</code></pre>

Pero para poder realizarlo se tiene que tener el dockerfile y el formato del la pagina a mostrar.

Dockerfile: 

<pre><code>
# use the httpd base image
FROM httpd:2.4

# Reemplazar index
COPY ./index.html/ /usr/local/apache2/htdocs/

</code></pre>

Se decide subir la imagen para no perderla y poder utilizarla en un futuro

<pre><code>docker tag helloworld:1.0 mari1018/helloworld:1.0</code></pre>
<pre><code>docker push mari1018/helloworld:1.0</code></pre>

Se vuelve a realizar lo mismo para el server 2 

- docker image build -t helloworld2:1.0 .
- docker tag helloworld2:1.0 mari1018/helloworld2:1.0
- docker push mari1018/helloworld2:1.0

| Nombre |Docker compose | Image |
| -- | -- | -- | -- |
| LAN Virtual 1 |<img src="/image/web1.jpg" alt="Web 1">|<img src="/image/vweb1.jpeg" alt="Visualizacion web 1"> |
| LAN Virtual 2 | <img src="/image/web020.png" alt="Web 2">|<img src="/image/vweb2.jpeg" alt="Visualizacion web 2"> |


<u> Proxy Reverso </u> 


<pre><code>

location /web1 {
    proxy_pass Server1
}

</code></pre>

<u> VPN </u> 

<u> Web Cache </u> 
______________________

<u> Diagramas de arquitectura </u> 

<u> Diagramas de flujo</u> 
______________________

<h2> Pruebas realizadas, con pasos para reproducirlas. </h2>
______________________



______________________

<h2> Resultados de las pruebas unitarias. </h2>
______________________

<h2> Recomendaciones </h2>

- Ir a consulta con el profesor
- Si se tiene una duda mejor preguntar
- 

______________________

<h2> Bibliografia </h2>



- Configuración de red (Networking) en Dockers - Blog Virtualizacion https://www.maquinasvirtuales.eu/configuracion-red-networking-dockers/

- Docker and iptables | Docker Documentation https://docs.docker.com/network/iptables/

- https://forums.docker.com/t/routing-network-traffic-from-one-service-to-another/117816/5

- Compose file version 3 reference. Docker Documentation. Recuperado de https://docs.docker.com/compose/compose-file/compose-file-v3/#host-or-none

- https://www.returngis.net/2019/02/publicar-tu-imagen-en-docker-hub/

