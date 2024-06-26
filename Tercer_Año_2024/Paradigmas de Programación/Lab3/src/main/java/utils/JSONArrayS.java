package utils;

import java.io.Serializable;
import org.json.JSONArray;

// Clase con la misma funcionalidad que JSONArray pero serializable
public class JSONArrayS extends JSONArray implements Serializable {
    public JSONArrayS(String source) {
        super(source);
    }
}