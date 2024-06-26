## Lab 3 - Computación Distribuida con Apache Spark

### Dependencias

Necesitan Java 17, tanto el JRE como el JDK. En Ubuntu, pueden instalarlo con:

```bash
apt install openjdk-17-jdk openjdk-17-jre
```

Luego se necesita Maven, que se puede instalar con:

```bash

apt install maven

```

### Compilación y ejecución

Para compilar el proyecto, ejecutamos el siguiente comando en el directorio del laboratorio:

```bash

mvn install

```

Esto lo que hace es descargar las dependencias y generar un archivo `.jar` en el directorio `target/` del proyecto.

Sea ```SPARK_HOME``` el directorio de instalación de Spark, ejecutamos el siguiente comando en el 
directorio del laboratorio para ejecutar el programa:

```bash
 ~$SPARK_HOME/bin/spark-submit --master spark://localhost:7077 target/Lab3-0.1.jar src/main/java/data/big_data.txt "flags" 2>/dev/null
```

Donde `src/main/java/data/big_data.txt` es el archivo de entrada y `flags` son las banderas que se desean utilizar.

Para no ver la información de spark redirigimos `stderr` a `/dev/null`.

