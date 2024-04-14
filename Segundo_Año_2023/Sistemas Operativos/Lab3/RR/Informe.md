# Informe Lab 3

- Ferre Valderrama, Eduardo
- Navarro, Francisco
- Ponce, Kevin

---


# Primera parte: Estudiando el planificador de xv6-riscv

## Pregunta 1

¿Qué política de planificación utiliza `xv6-riscv` para elegir el próximo proceso a ejecutarse? 
**Pista**: `xv6-riscv` nunca sale de la función scheduler por medios “normales”.

### Respuesta 

xv6-riscv utiliza una politica de planificacion Round Robin. La funcion `scheduler` busca un proceso que sea **RUNNABLE** (listo para correr), y hace un `context switch` para empezar a correr el primero que encuentra. Eventualmente, ya sea por un time interrupt o porque el proceso no esta utilizando la CPU, se salta a la funcion `sched`. 
La funcion `sched` se encarga de hacer el context switch necesario para volver a correr `scheduler`. Entonces `scheduler` busca el siguiente proceso **RUNNABLE**, y asi sucesivamente

## Pregunta 2

¿Cuánto dura un *quantum* en `xv6-riscv`?

### Respuesta 

El quantum es el tiempo que ocurre entre las interrupciones. En kernel/start.c en la función `timerinit` podemos ver:

```c
  
  int interval = 1000000; // cycles; about 1/10th second in qemu.
  *(uint64*)CLINT_MTIMECMP(id) = *(uint64*)CLINT_MTIME + interval;
```

En este caso la variable interval establece 1000000 ciclos de clock (en qemu 1/10s), que un proceso puede ejecutarse antes de que se programe una interrupción de temporizador. 

Por lo tanto, el quantum de tiempo que un proceso tiene para ejecutarse es de aproximadamente 1000000 ciclos de clock antes de que se produzca una interrupción de temporizador y se realice la planificación del próximo proceso.

## Pregunta 3

¿Cuánto dura un cambio de contexto en `xv6-riscv`?

### Respuesta 

Pudimos analizar que mientras mas achicamos el *quantum*, se llega a un punto en el que los procesos no llegan a ejecutarse, ya que ese tiempo lo utiliza el cambio de contexto. En particular, nosotros llegamos a reducir el *quantum* a 450 ticks, en este punto los procesos no se ejecutan y podemos deducir que el cambio de contexto dura aproximadamente 450 ticks. 

## Pregunta 4

¿El cambio de contexto consume tiempo de un *quantum*?

### Respuesta 

El cambio de contexto consume tiempo dentro de un *quantum*, ya que el proceso no se detiene y espera a que el nuevo proceso comience, sino que el reloj del *quantum* sigue avanzando mientras se realiza el cambio de contexto, lo que disminuye la cantidad de tiempo efectivo disponible para la ejecución del proceso. 

## Pregunta 5

¿Hay alguna forma de que a un proceso se le asigne menos tiempo? 
**Pista**: Se puede empezar a buscar desde la system call `uptime`.

### Respuesta 

Sí, con la información de la syscall `uptime`, se puede diseñar un scheduler que permita asignar más de un *quantum* a un proceso en función de su tiempo de ejecución o antigüedad.

## Pregunta 6

¿Cúales son los estados en los que un proceso pueden permanecer en `xv6-riscv` y que los hace cambiar de estado?

### Respuesta 

Un proceso en `xv6-riscv` puede estar en 6 estados.

**UNUSED**: Es el estado que se le da a cada proceso al momento de inicializar la *proc table*. Equivale a una posicion desocupada en la *proc table*. Cuando la entrada de un proceso en la *proc table* es liberada, se marca el campo `state` como **UNUSED**.

**USED**: Es el estado que se le asigna a un proceso cuando se asigna memoria a su entrada en la *proc table*, previo a estar en el estado **RUNNABLE**.

**SLEEPING**: Significa que el proceso esta esperando, sin usar la CPU. El proceso cambia a este estado luego de una llamada a la syscall `sleep`.

**RUNNABLE**: Significa que el proceso esta listo para correr en la CPU. Un proceso recientemente creado pasa primero por el estado **USED**. Ademas, se llega a este estado si el estado anterior del proceso era **SLEEPING** y se llamo a la syscall `wakeup` pasandole el *sleep channel* correspondiente, o si el estado anterior del proceso era **RUNNING**; en ese caso el estado actual es **RUNNABLE** porque su *quantum* se termino y el scheduler lo desplanifico o bien porque el proceso llamo a `yield`.

**RUNNING**: Significa que el proceso esta corriendo sobre la CPU. Se pasa a este estado unicamente desde el estado **RUNNABLE**, cuando el scheduler decide correr el proceso.

**ZOMBIE**: Significa que nuestro proceso termino pero sigue habiendo informacion sobre el en el kernel. Esto ocurre porque el padre del proceso no llamo a una syscall `wait`. Llamar a `wait` desde el proceso padre es la unica manera de limpiar la informacion de sus procesos hijos que han terminado.

# Segunda Parte: Cómo el planificador afecta a los procesos (Round Robin)

## Quantum normal

### Caso 1

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | Round Robin |
| Caso | iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 5294.21 |
| Promedio OPR/100T | 5294.21 |
| |  |
| Cant. select IO | 332224 |
| Cant. select 1er CPU | |
| Cant. select 2do CPU | |

### Caso 2

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 676.125 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 2126 |
| Cant. select 2do CPU | |

### Caso 3

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | Round Robin |
| Caso | iobench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 671.25 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 35.22 |
| Promedio OPR/100T | 35.22 |
| |  |
| Cant. select IO | 2225 |
| Cant. select 1er CPU | 2109 |
| Cant. select 2do CPU | |

### Caso 4

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 755.75 |
| Promedio MFLOPS /100T 2do cpubench | 544 |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 1051 |
| Cant. select 2do CPU | 1055 |

### Caso 5

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench &; cpubench &; iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 930.2778 |
| Promedio MFLOPS /100T 2do cpubench | 916.7222 |
| Promedio OPW/100T | 19.5 |
| Promedio OPR/100T | 19.5 |
| |  |
| Cant. select IO | 1227 |
| Cant. select 1er CPU | 1057 |
| Cant. select 2do CPU | 1060 |

## Quantums 10 veces más cortos

### Caso 1

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | Round Robin |
| Caso | iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 5354.7368 |
| Promedio OPR/100T | 5354.7368 |
| |  |
| Cant. select IO | 350532 |
| Cant. select 1er CPU | |
| Cant. select 2do CPU | |

### Caso 2

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 660.4375 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 21098 |
| Cant. select 2do CPU | |

### Caso 3

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | Round Robin |
| Caso | iobench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 617.6429 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 334.6471 |
| Promedio OPR/100T | 334.6471 |
| |  |
| Cant. select IO | 20930 |
| Cant. select 1er CPU | 21050 |
| Cant. select 2do CPU | |

### Caso 4

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 889.0588 |
| Promedio MFLOPS /100T 2do cpubench | 901.2222 |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 10563 |
| Cant. select 2do CPU | 10546 |

### Caso 5

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | Round Robin |
| Caso | cpubench &; cpubench &; iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 792.3125 |
| Promedio MFLOPS /100T 2do cpubench | 903.6471 |
| Promedio OPW/100T | 158.7647 |
| Promedio OPR/100T | 158.7647 |
| |  |
| Cant. select IO | 10480 |
| Cant. select 1er CPU | 10570 |
| Cant. select 2do CPU | 10483 |

#### Análisis QUANTUM ORIGINAL

* En el **Caso 1** y **Caso 2**, corremos un(1) IObench y un(1) CPUbench respectivamente, tomemos estos dos casos como parametros para realizar el analisis de los demas casos.
* En el **Caso 3**, corremos un(1) IObench en paralelo con un(1) CPUbench, aquí podemos observar que el planificador afecta drasticamente las metricas del IObench comparadas a las del **Caso 1**, mientras que las metricas del CPUbench se mantienen parecidas a las del **Caso 2**. Esto se debe a que cuando IObench realizar operaciones I/O, este cede su *quantum* y retoma el control una vez que CPUbench termine su tiempo antes de hacer otra operación y ceder su *quantum*.
* En el **Caso 4**, corremos dos(2) CPUbench en paralelo, aquí podemos ver que tienen prácticamente la misma cantidad de veces ejecutadas por el planificador y la misma cantidad total de operaciones, esto se debe a que ambos procesos agotan su *quantum* en cada ciclo, y el planificador intentará que los procesos se ejecuten equitativamente. Por lo tanto es probable que ambos procesos reciban un número similar de *quantums* de tiempo de CPU.
* En el **Caso 5** ejecutamos dos(2) CPUbench y un(1) IObench en paralelo, este escenario confirma lo que habiamos analizado en el caso 3, donde claramente se ven favorecidos los procesos de CPUbench, y los procesos IObench se ven claramente afectados de forma negativa. 

A modo de conclusión probamos un escenario más donde ejecutamos dos(2) CPUbench y dos(2) IObench, donde el segundo proceso IObench casi ni se ejecuta, donde finalmente podemos afirmar que el planifcador Round Robin con el *quantum* normal ejecuta de forma más eficiente los procesos CPUbench y los procesos IObench no. 

#### Análisis QUANTUM 10 VECES MAS CORTO

Aquí haremos un análisis más general:
 
* Con los *quantums* 10 veces mas cortos, claramente los procesos IObench se ven favorecidos en el caso de que se ejecute con procesos CPUbench porque al achicar el *quantum*, los procesos CPUbench tienen un menor tiempo para ejecutarse, por lo tanto ceden su *quantum* con mas frecuencia, así los procesos iobench tienen menos tiempo de espera para ser ejecutados.  
* Cuando el quantum es más chico, los procesos "CPUBench" se ejecutan durante un tiempo mucho menor significativo antes de ceder el CPU al siguiente proceso. Dado que CPUbench utiliza el tiempo de CPU de manera intensiva, puede completar menos operaciones de punto flotante durante un quantum más corto. 

#### Análisis QUANTUM ORIGINAL VS QUANTUM 10 VECES MAS CORTO

Dividimos este análisis en 3 casos:

* Ejecución de CPUBench en Quantum Original vs. Quantum 10 Veces Más Corto:  Con el *quantum* original, CPUBench puede ejecutarse durante más tiempo antes de ceder el control, lo que le permite completar más operaciones de CPU en cada quantum. Esto puede resultar en una mayor eficiencia en términos de operaciones. En el caso del quantum 10 veces más corto, CPUBench cede el control con mucha más frecuencia, lo que significa que se gasta más tiempo en cambios de contexto en lugar de realizar operaciones.

* Ejecución de IObench en Quantum Original vs. Quantum 10 Veces Más Corto: Tanto como con el *quantum* original y con el *quantum* 10 veces más corto, podemos ver que los procesos IObench comportan de forma parecida. Como no esta compitiendo con otros procesos por tiempo de CPU, la diferencia se podrá ver cuando corramos un proceso IObench con procesos CPUbench.  

* Comparación de la ejecución de CPUBench e IObench en Quantum Original vs. Quantum 10 Veces Más Corto: Cuando achicamos el *quantum* claramente los procesos IObench se ven favorecidos por el efecto negativo que se produce en los procesos CPUbench, puesto que estos procesos tienen menos tiempo de ejecución por lo tanto ceden el *quantum* con mas frecuencia, y los procesos iobench tienen un menor tiempo de espera significativo, por lo tanto se ejecutan más veces y realizan más operaciones.
 
# Cuarta Parte: Análisis con el planificador MLFQ

## Quantum normal

### Caso 1

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | MLFQ |
| Caso | iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 5357.8947 |
| Promedio OPR/100T | 5357.8947 |
| |  |
| Cant. select IO | 336009 |
| Cant. select 1er CPU | |
| Cant. select 2do CPU | |

### Caso 2

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 673.8125 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 2105 |
| Cant. select 2do CPU | |

### Caso 3

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | MLFQ |
| Caso | iobench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 670.8125 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 36 |
| Promedio OPR/100T | 36 |
| |  |
| Cant. select IO | 2225 |
| Cant. select 1er CPU | 2110 |
| Cant. select 2do CPU | |

### Caso 4

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 746.6875 |
| Promedio MFLOPS /100T 2do cpubench | 655.25 |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 1051 |
| Cant. select 2do CPU | 1064 |

### Caso 5

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 1000000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench &; cpubench &; iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 912.83333 |
| Promedio MFLOPS /100T 2do cpubench | 906.7778 |
| Promedio OPW/100T | 35.7 |
| Promedio OPR/100T | 35.7 |
| |  |
| Cant. select IO | 2226 |
| Cant. select 1er CPU | 1053 |
| Cant. select 2do CPU | 1060 |
	 
## Quantums 10 veces más cortos

### Caso 1

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | MLFQ |
| Caso | iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 5374.6842 |
| Promedio OPR/100T | 5374.6842 |
| |  |
| Cant. select IO | 350782 |
| Cant. select 1er CPU | |
| Cant. select 2do CPU | |

### Caso 2

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 584.2632 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 21311 |
| Cant. select 2do CPU | |

### Caso 3

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | MLFQ |
| Caso | iobench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 611.625 |
| Promedio MFLOPS /100T 2do cpubench | |
| Promedio OPW/100T | 439.0833 |
| Promedio OPR/100T | 439.0833 |
| |  |
| Cant. select IO | 20368 |
| Cant. select 1er CPU | 20300 |
| Cant. select 2do CPU | |

### Caso 4

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench &; cpubench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 743.1765 |
| Promedio MFLOPS /100T 2do cpubench | 612.7647 |
| Promedio OPW/100T | |
| Promedio OPR/100T | |
| |  |
| Cant. select IO | |
| Cant. select 1er CPU | 10524 |
| Cant. select 2do CPU | 10523 |

### Caso 5

| | Resultados |
|--------------|--------------|
| Hardware | AMD Athlon 3000G with Radeon Vega Graphics |
| Software | Versión de QEMU 6.2.0 |
| Quantum | 100000 |
| Politica Scheduler | MLFQ |
| Caso | cpubench &; cpubench &; iobench |
| |  |
| Promedio MFLOPS /100T 1er cpubench | 831.875 |
| Promedio MFLOPS /100T 2do cpubench | 827.625 |
| Promedio OPW/100T | 335.5294 |
| Promedio OPR/100T | 335.5294 |
| |  |
| Cant. select IO | 21137 |
| Cant. select 1er CPU | 10460 |
| Cant. select 2do CPU | 10514 |

#### Análisis QUANTUM ORIGINAL

* En el **Caso 1** y **Caso 2**, corremos un(1) IObench y un(1) CPUbench respectivamente, tomemos estos dos casos como parametros para realizar el analisis de los demas casos.
* En el **Caso 3**, corremos un(1) IObench en paralelo con un(1) CPUbench, y no hay una gran diferencia en la cantidad de veces que cada proceso fue elegido por el planificador, a pesar de tratarse de un planificador MLFQ. Esto se debe a que al haber solo dos procesos ejecutandose, un iobench y un cpubench, la prioridad es lo de menos, puesto que cuando el proceso iobench se duerme, y el único proceso para ejecutarse es cpubench, el planificador elige ejecutar este proceso y sabemos los procesos cpubench siempre agotan su quantum, por lo tanto el comportamiento que se produce es similar al del planificador Round Robin.
* En el **Caso 4**, corremos dos(2) CPUbench en paralelo, como ambos procesos usan intensivamente la CPU, en este caso el comportamiento es similar al planificador RR pues ambos procesos tienen la misma prioridad.
* En el **Caso 5** ejecutamos dos(2) CPUbench y un(1) IObench en paralelo, este caso refleja claramente la politica que se intenta implementar con MLFQ; el proceso IObench fue planificado mas del doble de veces que los procesos CPUbench.

#### Análisis QUANTUM 10 VECES MAS CORTO
* En el **Caso 1** los resultados son practicamente los mismos a los de quantum original. Nuestra hipotesis al respecto es que el proceso IObench utiliza un tiempo aun menor al quantum 10 veces mas corto, por ende el proceso tuvo una planificacion similar en ambos casos.
* En el **Caso 2** el proceso fue seleccionado alrededor de 10 veces mas que con el quantum original. Una explicacion a este hecho es que, al tener un tiempo disponible 10 veces menor, el proceso tuvo que ser seleccionado 10 veces mas para completar su computo.
* En el **Caso 3** como deducimos que el comportamiento es similar al planificador Round Robin, la justificación es la misma que en el planificador Roud Robin. Los procesos IObench se benefician del efecto negativo que se les produce a CPUbench.
* En el **Caso 4** ocurre lo mismo.
* En el **Caso 5** ocurre lo mismo.

	 
### ¿Se puede producir starvation en el nuevo planificador?
	
Primero, ¿Qué es starvation? Si hay "demasiados" trabajos interactivos se combinarán para consumir todo el tiempo de CPU y, por lo tanto los trabajos de largo duración nunca recibirán tiempo de CPU (se mueren de hambre).
	
Ahora bien, sabiendo la definición podemos decir que nuestra implementación del planificador MLFQ prioriza procesos en función de la prioridad y el número de veces programados, lo que puede llevar a la "starvation" de procesos de baja prioridad si hay una presencia excesiva de procesos de alta prioridad en el sistema.

Para solucionar dicho problema, una opción podria ser implementar Priority boost. Periodicamente, ajustar las prioridades de los procesos en función de su comportamiento y las necesidades del sistema. Esto asegura que los procesos no queden permanentemente en *starvation*. 

## RR vs MLFQ
* Con respecto al **Caso 1** y **Caso 2**, podemos decir que la cantidad de IOP's es similar al planificador Round Robin. Por más que haya prioridades, como el proceso se ejecuta solo, la prioridad no importa y se produce un comportamiento parecido a Round Robin.
* En el **Caso 3** y **Caso 5** donde ejecutamos tanto IObench y CPUbench, en particular con el **Caso 5**, se puede ver que el planificador MLFQ ejecutó prácticamente el doble de veces al proceso IObench que a los otros dos procesos CPUbench. Esto se debe a que IObench se ejecutará con mayor frecuencia en comparación con CPUbench debido a su alta prioridad. IObench tendrá ejecutará operaciones de I/O, lo que puede resultar en un mayor rendimiento en términos de lecturas y escrituras.  
* Finalmente en el **Caso 4**, donde corremos dos(2) CPUbench, los dos procesos utilizan todo su *quantum* y terminan más o menos con el mismo número de MFLOPs totales. Esto se debe a que estos procesos van a tener la misma prioridad, y por la **Regla 2**, corre el que menos veces fue elegido por el planificador, y en este sentido se produce un comportamiento parecido a Round Robin.

## Respuesta a las hipótesis de la cátedra

*	1) En un workload/escenario de cpubench todos los procesos deberían recibir la misma cantidad de quantums y tener el mismo número de MFLOPs totales. Esto debería ser cierto para RR y MLFQ
	* En RR: Todos los procesos reciben un quantum de tiempo de CPU de igual duración. Esto significa que, en un escenario de cpubench, todos los procesos reciben la misma cantidad de quantums. Dado que el quantum es igual para todos, todos los procesos tienen la misma oportunidad de utilizar la CPU y, así tienen el mismo número de MFLOPs totales, siempre y cuando los procesos sean parecidos en términos de requerimientos de tiempo de CPU.
	* En MLFQ: todos los procesos resultan tener la misma prioridad, consecuencia de que todos son CPUbench. Por lo tanto el planificador MLFQ hace algo muy similar a RR en este contexto, dandole la misma atencion a todos los procesos y es asi que se cumple la hipotesis planteada.
*	2) En un escenario con dos(2) cpubench y un(1) IObench: MLFQ debería favorecer al proceso que hace IO en comparación con RR. O sea se debería observar más cambios de contexto y más IOPs totales	
	* Efectivamente se observan mas cambios de contexto e IOPS para IObench, puesto que al ceder con frecuencia la CPU su prioridad se mantiene alta y por ello el scheduler lo planifica mas veces. Por eso mismo se observa una mayor cantidad de operaciones de IO en la misma cantidad de tiempo para MLFQ.
*	3) Con RR, un quantum menor debería favorecer a los procesos que hacen IO (en comparación al mismo workload/escenario con quantum mas grande)
	* En un escenario que se ejecuta solamente 1 proceso IObench el comportamiento es similar que con el *quantum* original. 
	* Con procesos CPUbench: Como habiamos analizado esto se debe a que con un *quantum* más pequeño los procesos IObench se benefician de los procesos CPUbench que se vieron efectados negativamente. Esto les permite completar más operaciones al haber un tiempo de espera mucho menor. En comparación, con un quantum más grande, los procesos de IObench tienen un mayor tiempo de espera hasta que los procesos CPUbench agoten su *quantum*.	
*	4) En escenarios de todos cpubench: al achicar el quantum el output total de trabajo debería ser menor o igual.	
	* Cuando se reduce el quantum en escenarios con todos los procesos cpubench, se produce una mayor frecuencia de cambios de contexto, ya que los procesos ceden el control con más frecuencia. Esto aumenta la sobrecarga de cambio de contexto y disminuye la eficiencia en términos de uso de la CPU para realizar operaciones. En por eso que es que el output total de trabajo sea menor o igual cuando se reduce el quantum, ya que se dedica más tiempo a administrar la alternancia de procesos en lugar de realizar operaciones.

