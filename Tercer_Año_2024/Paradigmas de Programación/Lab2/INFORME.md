
# Laboratorio de Programación Orientada a Objetos
## Ferré Eduardo, Verdini Joaquín, Navarro Francisco


El enunciado del laboratorio se encuentra en [este link](https://docs.google.com/document/d/1wLhuEOjhdLwgZ4rlW0AftgKD4QIPPx37Dzs--P1gIU4/edit#heading=h.xe9t6iq9fo58).

# 1. Tareas
Pueden usar esta checklist para indicar el avance.

## Verificación de que pueden hacer las cosas.
- [ X ] Java 17 instalado. Deben poder compilar con `make` y correr con `make run` para obtener el mensaje de ayuda del programa.

## 1.1. Interfaz de usuario
- [ X ] Estructurar opciones
- [ X ] Construir el objeto de clase `Config`

## 1.2. FeedParser
- [ X ] `class Article`
    - [ X ] Atributos
    - [ X ] Constructor
    - [ X ] Método `print`
    - [ X ] _Accessors_
- [ X ] `parseXML`

## 1.3. Entidades nombradas
- [ X ] Pensar estructura y validarla con el docente
- [ X ] Implementarla
- [ X ] Extracción
    - [ X ] Implementación de heurísticas
- [ X ] Clasificación
    - [ X ] Por tópicos
    - [ X ] Por categorías
- Estadísticas
    - [ X ] Por tópicos
    - [ X ] Por categorías
    - [ X ] Impresión de estadísticas

## 1.4 Limpieza de código
- [ X ] Pasar un formateador de código
- [ X ] Revisar TODOs

# 2. Experiencia
La programación orientada a objetos en java nos resulto similar a la programación a la que estábamos acostumbrados en C, pero con varias características extra que nos facilitaron mucho el trabajo. Entre ellas podemos nombrar la recolección de basura automática, las clases y la herencia y el subtipado.

# 3. Preguntas
1. Explicar brevemente la estructura de datos elegida para las entidades nombradas.

En este proyecto implementamos las siguientes estructuras de datos para las entidades nombradas:

Una clase Category que define la estructura básica de todas las categorias
```java
package namedEntities.categories;

import java.util.HashMap;

// Esta clase es abstracta porque
// no queremos que se instancie directamente
public abstract class Category {

    // Diccionario de atributos protected
    // para que cada clase hija pueda
    // acceder a el y poner sus propios atributos
    protected HashMap<String, String> attrbs;

    // Esta clase se encarga de inicializar
    // el diccionario para no tener que
    // hacerlo en cada clase hija y reutilizar
    // codigo
    public Category() {
        attrbs = new HashMap<String, String>();
    }

    // Metodos final ya que todas las sublcases
    // de category deberian coportarse asi al
    // llamar a estos metodos y no de otra forma
    public final String getName() {
        return getClass().getSimpleName();
    }

    public final HashMap<String, String> getAttrbs() {
        return attrbs;
    }
}
```

Instancias concretas de esta clase, por ejemplo Person
```java
package namedEntities.categories;

import java.util.HashMap;

public class Person extends Category {

    public Person(String name, String lastName, int age) {
        attrbs.put("NAME", name);
        attrbs.put("LASTNAME", lastName);
        attrbs.put("AGE", String.valueOf(age));
    }

}

```
Y finalmente nuestras entidades nombradas son objetos con campos de tipo Category y List<String>, que representan la categoría y los tópicos de la entidad respectivamente. El campo name de tipo String es la palabra o palabras que representan a la entidad, por ejemplo "Nueva York"
```java
package namedEntities;

import java.util.HashMap;
import java.util.List;
import namedEntities.categories.*;

public class NamedEntity {
    // campos encapsulados
    private Category cat;
    private List<String> topics;
    private String name;

    // Constructor sobrecargado
    public NamedEntity(String name) {
        cat = null;
        topics = null;
        this.name = name;
    }

    // Constructor sobrecargado
    public NamedEntity(Category cat, List<String> topics, String name) {
        this.cat = cat;
        this.topics = topics;
        this.name = name;
    }

    public void setCategory(Category cat) {
        this.cat = cat;
    }

    public void setTopics(List<String> topics) {
        this.topics = topics;
    }

    public String getName() {
        return name;
    }

    public String getCategoryName() {
        return cat.getName();
    }

    public List<String> getTopics() {
        return topics;
    }

    public HashMap<String, String> getAttrbs() {
        return cat.getAttrbs();
    }

}
```
2. Explicar brevemente cómo se implementaron las heurísticas de extracción.

Creamos una interfaz Heuristic que define el método que toda heurística debe implementar
```java
package namedEntities.heuristics;

import java.util.List;

public interface Heuristic {
    public List<String> extractCandidates(String text);
}
```
Luego, tenemos la clase CompositeNameHeuristic cuya implementación de extractCandidates consiste en extraer toda aquella cadena que contenga 2 o más palabras que comiencen en mayúscula
```java
package namedEntities.heuristics;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// Heuristica para buscar cadena de 2 o mas palabras que comiencen con mayuscula
public class CompositeNameHeuristic implements Heuristic {

    @Override
    public List<String> extractCandidates(String text) {
        List<String> candidates = new ArrayList<>();

        // Expresión regular que incluye caracteres con diacríticos
        Pattern pattern = Pattern.compile("\\b\\p{Lu}\\p{L}*(?:\\s\\p{Lu}\\p{L}*){1,}\\b");

        Matcher matcher = pattern.matcher(text);

        while (matcher.find()) {
            candidates.add(matcher.group());
        }
        return candidates;
    }
}
```

Y por último en la clase ContextualEntityHeuristic implementamos la segunda heurística. Esta clase hereda de CapitalizedWordHeuristic ya que usa la implementación de extractCandidates de su clase madre, pero no se limita a extraer las palabras que comiencen en mayúscula; además las filtra usando una lista de palabras comunes que no representan entidades nombradas.

```java
package namedEntities.heuristics;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// Heuristica para buscar palabras que comienzen en mayuscula excluyendo posibles palabras de inicio de oracion entre otras.
public class ContextualEntityHeuristic extends CapitalizedWordHeuristic {

    private static final List<String> commonWords = Arrays.asList(
            "The", "A", "An", "In", "On", "Of", "And", "Or", "To", "With", "Without",
            "By", "For", "From", "As", "At", "But", "If", "While", "Though", "Yet",
            "Is", "Are", "Was", "Were", "Be", "Being", "Been", "Has", "Have", "Had",
            "Do", "Does", "Did", "Will", "Would", "Can", "Could", "Should", "May", "Might",
            "Must", "Shall", "This", "That", "These", "Those", "It", "Its", "Their", "There", "Then",
            "El", "La", "Los", "Las", "Un", "Una", "Unos", "Unas", "En", "Sobre", "De", "Y", "O", "A",
            "Con", "Sin", "Por", "Para", "Desde", "Como", "Al", "Pero", "Si", "Mientras", "Aunque",
            "Sin embargo", "Es", "Son", "Era", "Eran", "Ser", "Siendo", "Sido", "Ha", "Han", "Había",
            "Hacer", "Hace", "Hizo", "Hará", "Harían", "Puede", "Podría", "Debería", "Puede que", "Debe", "Deberá",
            "Este", "Ese", "Estos", "Esos", "Esto", "Aquellos", "Su", "Sus", "Allí", "Entonces", "Se", "Lo", "No");

    @Override
    public List<String> extractCandidates(String text) {
        List<String> candidates = new ArrayList<>();

        List<String> capitalizedCandidates = super.extractCandidates(text);

        for (String candidate : capitalizedCandidates) {

            String[] words = candidate.split("\\s+");
            StringBuilder filteredCandidate = new StringBuilder();

            // En caso que se encuentre alguna de las palabras excluidas en la cadena se
            // reemplaza con un espacio vacio.
            for (String word : words) {
                if (!commonWords.contains(word)) {
                    if (filteredCandidate.length() > 0) {
                        filteredCandidate.append(" ");
                    }
                    filteredCandidate.append(word);
                }
            }

            if (filteredCandidate.length() > 0) {
                candidates.add(filteredCandidate.toString().trim());
            }
        }

        return candidates;
    }
}
```