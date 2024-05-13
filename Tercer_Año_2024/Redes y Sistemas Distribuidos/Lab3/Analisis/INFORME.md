# Análisis de flujo y congestión en una red simulada en Omnet++

# Grupo 48

# Integrantes:
- Ferré, Eduardo
- Mariano, Matteo
- Navarro, Francisco

## Resumen
En este laboratorio, exploramos el tráfico de redes utilizando simulaciones discretas con Omnet++, con el propósito de comprender y resolver problemas en la Capa de Transporte. Configuramos una red compuesta por varios nodos encargados de transportar paquetes entre sí. Nos centramos en analizar cómo la red responde ante distintas tasas de transmisión y otros parámetros. Finalmente diseñamos una estrategia para controlar la congestión y el flujo de la red, con el objetivo de mejorar su eficiencia.

## Introducción
En el contexto de las redes, la Capa de Transporte desempeña un papel crucial al garantizar la entrega confiable de datos entre nodos emisores y receptores. Sin embargo, esta capa se enfrenta a dos desafíos principales: el control de flujo y el control de congestión.

El control de flujo se encarga de regular la tasa de transferencia de datos entre un emisor y un receptor específico, asegurando que el receptor no se vea sobrecargado por una cantidad excesiva de datos que supere su capacidad de procesamiento. Por otro lado, el control de congestión se enfoca en evitar la saturación de la red en sí, regulando el tráfico total que fluye a través de ella para no exceder su capacidad de transferencia limitada.

En este laboratorio, exploramos estos conceptos mediante simulaciones discretas utilizando OMNeT++, una herramienta de simulación de eventos discretos que nos permite recrear el comportamiento de una red compuesta por nodos que transmiten paquetes entre sí.

En la primera parte del laboratorio, configuramos dos casos de estudio que representan situaciones de control de flujo y congestión, respectivamente. Mediante experimentos paramétricos, variamos factores clave como las tasas de transmisión y los tamaños de buffer, y evaluamos su impacto en el rendimiento de la red, midiendo métricas como la cantidad de paquetes recibidos y perdidos durante la transferencia.
Posteriormente, en la segunda parte, diseñamos e implementamos una estrategia de control de flujo y congestión con el objetivo de mejorar la eficiencia de la red, reduciendo la pérdida de paquetes y optimizando la utilización de los recursos disponibles.


## Tarea Análisis

### Primer caso de estudio

| Connection         | Datarate  | Delay  |
| ------------------ | ----------| ------ |
| `NodeTx` a `Queue` | `1.0 Mbps`| 100 us |
| `Queue` a `NodeRx` | `1.0 Mbps`| 100 us |
| `Queue` a `Sink`   | `0.5 Mbps`|        |

Observemos que la tasa de transferencia de `Queue` es mayor a la tasa de transferencia de `Queue` a `Sink`, es decir, `Queue` va a estar recibiendo más paquetes de los que va a estar enviando. Por ende, si se envían muchos paquetes en la red, es decir, si el intervalo de generación es más pequeño, el buffer de NodeRx se va a saturar. Esto sucede porque NodeRx no puede procesar y enviar los paquetes tan rápido como están llegando. Como resultado, los paquetes se acumularán en el buffer de NodeRx, esperando ser procesados y enviados hacia `Sink`. Esta saturación puede causar demoras en la entrega de los paquetes y, también provoca pérdida de paquetes si el buffer se llena por completo.

Ilustremos esto mediante distintas graficas.

<p align="center">
  <img src="graficos/Analisis/caso1.png" alt="Gráfico" width="900" />
  <br>
  <em>Caso 1: Ocupación del buffer</em>
</p>

Notemos que a medida de que el intervalo de generación aumenta, la ocupación del buffer disminuye, puesto que los paquetes tienen mas tiempo para ser procesados y enviados a `Sink` antes de que llegue el siguiente paquete.


<p align="center">
  <img src="graficos/Analisis/caso1_paquetes.png" alt="Gráfico" width="900" />
  <br>
  <em>Caso 1: Paquetes</em>
</p>

Esto confirma lo dicho anteriormente, si los paquetes se generan con menos frecuencia, hay más tiempo para procesar cada paquete, lo que reduce la probabilidad de que se pierdan paquetes debido a la saturación del buffer.


### Segundo caso de estudio

| Connection         | Datarate  | Delay  |
| ------------------ | ----------| ------ |
| `NodeTx` a `Queue` | `1.0 Mbps`| 100 us |
| `Queue` a `NodeRx` | `0.5 Mbps`| 100 us |
| `Queue` a `Sink`   | `1.0 Mbps`|        |

 En este caso, la tasa de transferencia `Queue` a `NodeRx` es 0.5 Mbps, que es menor que la tasa de transferencia de `NodeTx` a `Queue` y de `Queue` a `Sink`, que son de 1.0 Mbps. Esto significa que `NodeRx` recibe paquetes de `Queue` a una velocidad más lenta de la que `Queue` los recibe de `NodeTx` y los envía a `Sink`. Por lo tanto, si se generan paquetes con alta frecuencia (es decir, si el intervalo de generación es pequeño), el buffer en `NodeRx` se satura rápidamente, ya que los paquetes llegan más rápido de lo que pueden ser procesados y enviados a `Sink`.

 Observemos las siguientes gráficas

<p align="center">
  <img src="graficos/caso2.png" alt="Gráfico" width="900" />
  <br>
  <em>Caso 2: Ocupación del buffer</em>
</p>


 <p align="center">
  <img src="graficos/caso2_paquetes.png" alt="Gráfico" width="900" />
  <br>
  <em>Caso 2: Paquetes</em>
</p>

Podemos visualizar que son bastante parecidas a las del caso de estudio 1. Esto es porque
en ambos casos lo que esta pasando  es que un nodo recibe a una velocidad de 1Mbps pero solo los procesa a una velocidad de 0.5Mbps, solo que la diferencia ocurre en el nodo que sucede el cuello de botella.

### Respuestas a preguntas


## Tarea Diseño



