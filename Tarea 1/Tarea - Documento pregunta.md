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

<center><h2>  Agregar Imagen </h2></center>

Fourier generado por Mariana

<center><h2>  Agregar Imagen </h2></center>

Se puede observar que las graficas de fourier son diferentes aunque se diga lo mismo ya que el espacio entre las amplitudes de seno y coseno, el rango y la frecuencia (el espectro de voz) generado tambien son distintos.