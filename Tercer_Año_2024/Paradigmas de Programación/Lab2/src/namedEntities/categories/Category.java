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