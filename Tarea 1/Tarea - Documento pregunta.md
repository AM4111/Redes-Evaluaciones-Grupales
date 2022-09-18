Tecnológico de Costa Rica<br> 
Escuela de Ingeniería en Computación<br> 
IC: 7602-Redes  - 2 Semestre 2022 <br> 
2018086509 - Jocxan Sandi Batista <br> 
2018093728 - Paula Mariana Bustos Vargas
______________________
<center> <h1> Tarea - Documento  de la pregunta </h1> </center> 

<h2> “¿Por qué las voces de los integrantes son diferentes?” </h2>

Para poder responder de la manera mas apropiada primero se ve que en el capitulo 2.1 y 7.4 del libro de Redes de computadoras de Tanenbaum, explica puntos que consideramos importantes para la solucion de esta respuestas, ademas de unos terminos que nos parecen importante resaltar:

- Se da el analisis de Fourier donde cabe destacar el comportamiento de amplitudes de seno y coseno de terminos armónicos en una frecuencia.
  
- Todas las instalaciones de transmisión disminuyen los distintos componentes de Fourier en diferente grado, lo que provoca distorsión. Por lo general, las amplitudes se transmiten sin ninguna disminución desde 0 hasta cierta frecuencia fc *[medida en ciclos/seg o Hertz (Hz)]*
  - Todas las frecuencias que se encuentren por arriba de esta frecuencia de corte serán atenuadas. 
  - El rango de frecuencias que se transmiten sin atenuarse con
fuerza se conoce como **ancho de banda**.

- Una onda senoidal, es la grafica de la función seno.
  - Viene ligado a la representación 

- Una onda de audio (sonido) es una onda acústica (de presión) de una dimensión. 
  
- Comportamiendo cuando una onda acústica entra en el oído, el tímpano vibra, causando que los pequeños huesos del oído interno vibren con él, enviando pulsos nerviosos al cerebro. El escucha percibe estos pulsos como sonido.

- El oído escucha de manera logarítmica, por lo que la relación entre dos sonidos de amplitudes A y B se expresa convencionalmente en dB (decibeles) de acuerdo con la fórmula
<center> dB: 10 log(A/B) </center>

- El oído es sorprendentemente sensible a variaciones de sonido que duran apenas unos milisegundos.

- La gama de frecuencias perceptibles por el oído humano va de 20 Hz a 20,000 Hz.
- La voz humana tiende a estar en el rango de 600 a 6000 Hz.

- La voz se compone de vocales y consonantes
  - Las vocales se producen cuando el tracto vocal está libre, produciendo resonancias cuya frecuencia fundamental depende del tamaño y de la forma del sistema vocal y de la posición de la lengua y mandíbula de quien habla. Estos sonidos son casi periódicos en intervalos de aproximadamente 30 mseg. 
  - Las consonantes se producen cuando se producen cuando el tracto vocal está bloqueado parcialmente. Estos sonidos son menos regulares que las vocales.

- La compresión de audio se puede realizar con la **codificación de forma de onda** la señal se transforma de manera matemática en sus componentes de frecuencia mediante una **transformación de Fourier** (La cual fue la base de esta tarea) 

Ahora bien sabiendo lo anterior y basandos en las graficas generadas en la tarea que se muestran a continuación:

Fourier generado por Jocxan

![Imagen1](imagenes_documentacion/Jocxan.png)


Fourier generado por Mariana

![Imagen1](imagenes_documentacion/Mariana.png)

Notemos que en ambas imagenes el primer dibujo hace referencia al dominio del Tiempo y en la segunda grafica se observa la amplitud de Fourier.

Es importante destacar que con lo investigado más las explicación que presenta el libro, lo que diferencia principalmente la voz de una persona con otra es el timbre que es el espectro específico de una voz, que consiste en el sonido básico y los formantes vocales, es decir la característica vocal que cada individuo posee, y esta se produce por como el tracto vocal se comporta a la hora de generar una vocal o una consonates. Por lo que esta es lo que se va a representar en las ondas armonicas continuas que se graficaron.

Otra cosa que cambia la voz de una persona es el rango, la frecuencia y la potencia que genere.

Si bien es cierto que se muestra un comportamiento similar entre las dos graficas. Se puede observar que las graficas tanto del dominio como la de fourier son diferentes aunque se diga lo mismo ya que el espacio entre las amplitudes de seno y coseno; el rango y la frecuencia (el espectro de voz) generado tambien son distintos.

## G) Referencias 
> Análisis de Fourier. (s. f.). Recuperado de http://www.sc.ehu.es/sbweb/fisica/ondas/fourier/Fourier.html


> Audio de banda ancha. (s. f.). NFON AG. Recuperado de https://www.nfon.com/es/get-started/cloud-telephony/lexicon/base-de-conocimiento-destacar/audio-de-banda-ancha#:%7E:text=Desde%20hace%20m%C3%A1s%20de%20100,ancho%20de%20banda%20tan%20limitado.

>Luis Carrillo. (2006) ResearchGate. Recuperado de https://www.researchgate.net/figure/Figura-6-Grafica-de-los-pixeles-del-contorno-en-el-dominio-del-tiempo-y-la-frecuencia-Al_fig1_301956946

>Granada, C. P. D. D. A. de. (2014, 20 mayo). InformaciÃ3n General: AnÃ¡lisis espectral: Â¿Que es y que se representa en las grÃ¡ficas? Recuperado  de https://www.granada.org/inet/sonidos.nsf/d483b298c3f6a1b9c1257cdd00384c53/3fdfc36a7489b607c1257cde0024bb34!OpenDocument#:%7E:text=Se%20define%20el%20espectro%20de,es%20de%20naturaleza%20predominantemente%20espectral. 

> Musiki. Espectro. Gustavo Basso (2001) Recuperado de https://musiki.org.ar/Espectro

> Valdes, A. (2022, 18 febrero). ¿Cuál es el Rango de Frecuencia de la Voz? Productora Audiovisual en Colombia. Recuperado de https://almagina.com/cual-es-el-rango-de-frecuencia-de-la-voz/


> TIPOS DE ONDAS. (s. f.). ITCA. Recuperado de https://virtual.itca.edu.sv/Mediadores/irmfi1/IRMFI_32.htm#:%7E:text=Una%20onda%20senoidal%20o%20senoide,intervalos%20regulares%20(son%20peri%C3%B3dicas).

> Zapata, J. R. (2021). Representacion del Audio. Jose Ricardo Zapata. Recuperado de https://joserzapata.github.io/courses/mineria-audio/representacion_audio/
