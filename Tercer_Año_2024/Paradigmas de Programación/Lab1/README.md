# Laboratorio de Funcional
### Grupo 22
**Autores:** 
- Eduardo Ferré Valderrama 
- Joaquín López Verdini
- José Francisco Navarro

La consigna del laboratorio está en https://tinyurl.com/funcional-2024-famaf

# 1. Tareas
Pueden usar esta checklist para indicar el avance.

## Verificación de que pueden hacer las cosas.
- [ ] Haskell instalado y testeos provistos funcionando. (En Install.md están las instrucciones para instalar.)

## 1.1. Lenguaje
- [ ] Módulo `Dibujo.hs` con el tipo `Dibujo` y combinadores. Puntos 1 a 3 de la consigna.
- [ ] Definición de funciones (esquemas) para la manipulación de dibujos.
- [ ] Módulo `Pred.hs`. Punto extra si definen predicados para transformaciones innecesarias (por ejemplo, espejar dos veces es la identidad).

## 1.2. Interpretación geométrica
- [ ] Módulo `Interp.hs`.

## 1.3. Expresión artística (Utilizar el lenguaje)
- [ ] El dibujo de `Dibujos/Feo.hs` se ve lindo.
- [ ] Módulo `Dibujos/Grilla.hs`.
- [ ] Módulo `Dibujos/Escher.hs`.
- [ ] Listado de dibujos en `Main.hs`.

## 1.4 Tests
- [ ] Tests para `Dibujo.hs`.
- [ ] Tests para `Pred.hs`.

# 2. Experiencia

Gracias a este laboratorio conocimos una aplicación de la programación funcional y de Haskell en particular más allá de lo que habíamos visto en primer año. Utilizamos la librería Gloss.

# 3. Preguntas
## 3.1 ¿Por qué están separadas las funcionalidades en los módulos indicados? Explicar detalladamente la responsabilidad de cada módulo.

La separación de funcionalidades en módulos diferentes ayuda a mantener el código organizado y fácil de mantener. Cada módulo tiene una responsabilidad única, lo que nos permite comprender de una manera más fácil el código y poder trabajar en distintas partes del código sin interferir entre nosotros.

- El módulo `Dibujo` se encarga de definir la sintaxis del lenguaje de figuras (los constructores y las funciones que podemos usar).
- El módulo `Interp` define la semántica del lenguaje, es decir, la interpretación geométrica de las figuras.
- El módulo `Pred` se definen las funciones de predicado que nos permiten evaluar las propiedades de las figuras.

## 3.2 ¿Por qué las figuras básicas no están incluidas en la definición del lenguaje, y en vez de eso, es un parámetro del tipo?

Las figuras básicas no están incluidas en la definición del lenguaje para tener la flexibilidad de poder definir el tipo de figura básica que queremos utilizar. Al hacerlas un parámetro del tipo, se pueden agregar o modificar figuras básicas sin tener que cambiar la definición del lenguaje.

## 3.3 ¿Qué ventaja tiene utilizar una función de `fold` sobre hacer pattern-matching directo?

Utilizar una función de `fold` nos ayuda a simplificar el código y hacerlo más legible. En vez de manejar cada caso posible con pattern-matching, una función de `fold` puede manejar todos los casos de una vez.

## 3.4 ¿Cuál es la diferencia entre los predicados definidos en Pred.hs y los tests?

Los predicados definidos en Pred.hs son funciones que toman un valor y devuelven un booleano, indicando si el valor cumple con cierta condición. Los tests, por otro lado, son pruebas que verifican que el código se comporta como se espera. Los predicados pueden ser utilizados en los tests para verificar el comportamiento del código.

# 4. Extras
Completar si hacen algo.