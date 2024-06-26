
# Laboratorio 3: Computación Distribuida con Apache Spark

# Grupo 22

# Integrantes 
- Ferré, Eduardo
- Navarro, Francisco 
- Verdini, Joaquín 


El enunciado del laboratorio se encuentra en [este link](https://docs.google.com/document/d/e/2PACX-1vQn5BpCPQ6jKMN-sz46261Qot82KbDZ1RUx8jNzAN4kBEAq_i97T3R6ZA0_yRA5elN66e-EArXQXuAh/pub).

## Introducción

En este laboratorio, vamos a extender el lector de feeds que desarrollamos previamente en el laboratorio 2 para soportar el procesamiento de grandes volúmenes de datos (big data) utilizando Apache Spark. El objetivo principal es computar entidades nombradas en un gran conjunto de datos de manera eficiente y en paralelo.


## Compilación y ejecución

Para compilar el proyecto, ejecutamos el siguiente comando en el directorio del laboratorio:

```bash

mvn install

```
Esto lo que hace es descargar las dependencias y generar un archivo `.jar` en el directorio `target/` del proyecto.

Sea ```SPARK_HOME``` el directorio de instalación de Spark, ejecutamos el siguiente comando en el 
directorio del laboratorio para ejecutar el programa:

```bash
 ~$SPARK_HOME/bin/spark-submit --master spark://localhost:7077 target/Lab3-0.1.jar "flags" 2>/dev/null
```

donde `flags` son las banderas que se desean utilizar, estas pueden ser:
- `-h`, `--help` para imprimir el programa de ayuda.
- `-ne`, `--named_entity` _heuristicName_. Para especificar el nombre de la heurística a utilizar para computar entidades nombradas. 
- `-sf`, `stats-format` _format_. Para especificar el formato de salida de las estadísticas.

Para no ver la información de spark redirigimos `stderr` a `/dev/null`.

## Desarrollo

### Creación de la big data

Para la creación de la big data creamos una clase llamada ```BigDataFile``` , donde implementamos un método llamado ```buildFile```, donde lee las URLs de los feeds desde ```src/main/java/data/feeds.json``` descarga el contenido de cada feed, lo parsea como XML para extraer artículos, y los escribe en un archivo de texto ```big_data.txt```.  En este archivo se incluyen únicamente el título y la descripción de cada artículo procesado.


### Integración con el framework Spark

Notemos que en laboratorio dos extraíamos las entidades nombradas de los feeds de manera secuencial. Ahora, vamos a utilizar Apache Spark para procesar los feeds de manera paralela. 

Primero inicializamos una SparkSession, que es el punto de entrada para utilizar Spark. La SparkSession nos permite leer datos de diferentes fuentes y convertirlos en RDDs (Resilient Distributed Datasets), que son las estructuras de datos fundamentales en Spark.

```java
SparkSession spark = SparkSession.builder().appName("Lab3g22").getOrCreate();
```

Luego utilizamos Spark para leer el archivo de texto que contiene los datos que queremos procesar, en nuestro caso el ```bigData.txt``` que generamos anteriormente, y lo convertimos convertimos en un RDD de Strings. 

```java
JavaRDD<String> lines = spark.read().textFile("src/main/java/data/big_data.txt").javaRDD();
```

Luego utilizamos una heuristica especificada por el usuario para computar las entidades nombradas en los feeds. Esta heurística se aplica a cada línea del archivo leído y produce un RDD de candidatos.

```java
JavaRDD<String> candidates = heuristic.extractCandidates(lines);
```
Convertimos los candidatos extraídos en entidades nombradas utilizando la clase Sorter. Cada candidato se procesa para determinar su categoría y tópicos asociados, generando un RDD de entidades nombradas.

```java
JavaRDD<NamedEntity> entities = candidates.map(c -> Sorter.Create(c));
```

Dependiendo del formato especificado por el usuario, calculamos las estadísticas de las entidades nombradas por categoría o por tópico.

```java
if (format != null && format.equals("topic")) {
    List<Tuple2<String, Tuple2<List<String>, Integer>>> results = StatsCounter.computeTopicStats(entities);
    // Imprimimos resultados por tópicos...
} else {
    List<Tuple2<String, Tuple2<String, Integer>>> results = StatsCounter.computeCatStats(entities);
    // Imprimimos resultados por categorías...
}
```
Finalmente una vez que hemos procesado los datos y calculado las estadísticas, detenemos la SparkSession para liberar los recursos.

```java
spark.stop();
```

Ahora bien, esto fue un vistazo general de como utilizamos Apache Spark para procesar los feeds de manera paralela. A continuación vamos a detallar que cambios tuvimos que realizar en las distintas clases ya implementadas en el laboratorio dos para lograr paralelismo.

### Computación de Entidades nombradas

#### Heurísticas

Para computar las entidades nombradas en paralelo, tuvimos que modificar la clase ```Heuristic``` para que sea compatible con Spark. Ahora las heuristicas deben implementar el método ```extractCandidates``` que recibe un RDD de Strings y devuelve un RDD de Strings.

En lugar de procesar las cadenas de texto de manera secuencial y local, utilizamos las transformaciones de Spark como map, flatMap y filter para realizar las operaciones de limpieza y extracción de candidatos en paralelo. Las principales transformaciones utilizadas son:

- **map** : Aplica una función a cada elemento del RDD y devuelve un nuevo RDD con los resultados.
- **flatMap** : Aplica una función a cada elemento del RDD y devuelve un nuevo RDD con los resultados aplanados.
- **filter** : Filtra los elementos del RDD que cumplen con una condición dada.

#### StatsCounter

Para calcular las estadísticas de las entidades nombradas en paralelo, tuvimos que modificar la clase ```StatsCounter``` para que sea compatible con Spark. Tuvimos que reescribir la lógica de conteo utilizando RDDs y las funciones de Spark para mapear y reducir datos distribuidos.

En la implementación anterior, StatsCounter utilizaba mapas de hash (HashMap) para almacenar los conteos de categorías y tópicos de las entidades nombradas. En la nueva implementación, utilizamos JavaPairRDD para realizar estos cálculos de manera distribuida y paralela, aprovechando las capacidades de procesamiento de datos de Spark.

En lugar de manipular directamente los maps, ahora utilizamos transformaciones de Spark como mapToPair y reduceByKey junto a la acción collect, donde mapToPair se utiliza para transformar las entidades nombradas en pares clave-valor, reduceByKey se utiliza para agrupar las entidades nombradas por clave y agregar sus valores y collect se utiliza para recolectar los resultados en una lista. Las transformaciones no computan ningún valor; los cálculos se realizan cuando se llama a una acción como collect. Esta característica de Spark es conocida como <em>laziness</em>.


#### NamedEntity, Category y JSONArrayS

En estas clases tuvimos que realizar cambios menores para que sean compatibles con Spark. Ahora las clases ```NamedEntity``` y ```Category``` deben implementar la interfaz ```Serializable```. Esto es necesario porque Spark distribuye las tareas de procesamiento a través de un clúster y los objetos que se pasan entre los nodos deben ser serializables para que puedan ser enviados a través de la red. En el caso de la clase ```JSONArray```, no podemos hacer que implemente la interfaz ```Serializable``` direcamente, pues esta clase pertenece a una librería extera. Nuestra solución a esto fue crear una clase ```JSONArrayS``` que hereda de ```JSONArray``` e implementa la interfaz ```Serializable```.

Implementar la interfaz ```Serializable``` en estas clases asegura que los objetos de tipo ```NamedEntity```, ```Category``` y ```JSONArrayS``` puedan ser serializados y deserializados por Spark, permitiendo su uso en operaciones distribuidas.

### Comparativa de versiones

Primero aclarar que para este análisis, estamos montando un clúster de Spark compuesto por un nodo maestro y dos nodos workers, donde cada nodo tiene 2 cores y 2GB de memoria. Para lograr esta configuración nos guiamos por [esta fuente.](https://mallikarjuna_g.gitbooks.io/spark/content/spark-standalone-example-2-workers-on-1-node-cluster.html)

Para hacer dicha comparación con el laboratorio dos, vamos a ejecutar el programa sin indicar un feed en particular, así se asemenaja al comportamiento que tiene nuestro big data aquí, donde se tienen todos los feeds.

En el laboratorio dos obtuvimos este tiempo de respuesta:

```bash
real	0m2,465s
user	0m1,981s
```

Mientras que en este laboratorio:

```bash 
real	0m7,534s
user	0m11,585s
```
Nuestra suposición es que el tiempo de respuesta es mayor en este laboratorio ya que estamos utilizando un framework de procesamiento distribuido, lo que implica un mayor overhead por la comunicación entre los nodos del clúster. El overhead que se paga no se justifica ya que los datos a procesar son pocos. Además nuestro laboratorio tres tiene la tarea extra de escribir en disco estos datos.

Entonces con una cantidad de datos pequeña, como en este caso, el tiempo de respuesta es mayor al utilizar Spark en lugar de procesamiento secuencial. Sin embargo, a medida que aumenta el volumen de datos, Spark se vuelve más eficiente y puede procesar grandes conjuntos de datos de manera más rápida que un enfoque secuencial.

Para confirmar esto, ejecutamos el programa con el archivo ```wiki_dump_parcial.txt``` provisto por el profesor Miguel Pagano. Copiamos ```wiki_dump_parcial.txt``` en el directorio ```src/main/java/data``` del proyecto y luego modificamos la linea 94 en ```App.java```

```java
JavaRDD<String> lines = spark.read().textFile("src/main/java/data/wiki_dump_parcial.txt.txt").javaRDD();
```

Notemos que es un archivo que pesa aproximadamente ```1.6 GB```.

Entonces los resultados obtenidos fueron los siguientes:

```bash
real	0m7,376s
user	0m12,632s

```
Como podemos observar, se obtuvo un tiempo de respuesta similar al anterior, lo que confirma nuestra hipótesis de que Spark es más eficiente que un enfoque secuencial al procesar grandes volúmenes de datos.  


## Conclusión
En este laboratorio, hemos extendido el lector de feeds que desarrollamos previamente en el laboratorio 2 para soportar el procesamiento de grandes volúmenes de datos utilizando Apache Spark. Esta extensión nos permitió aprovechar las capacidades de procesamiento distribuido de Spark para computar entidades nombradas en un gran conjunto de datos de manera eficiente y en paralelo. 

A lo largo del desarrollo, pudimos observar como el procesamiento distribuido puede mejorar significativamente la eficiencia al manejar grandes conjuntos de datos.

## Referencias

- [Apache Spark](https://spark.apache.org/)
- [Apache Spark Programming Guide](https://spark.apache.org/docs/latest/programming-guide.html)
- [Apache Spark Java API](https://spark.apache.org/docs/latest/api/java/index.html)
- [Example 2-workers-on-1-node Standalone Cluster (one executor per worker)](https://mallikarjuna_g.gitbooks.io/spark/content/spark-standalone-example-2-workers-on-1-node-cluster.html)