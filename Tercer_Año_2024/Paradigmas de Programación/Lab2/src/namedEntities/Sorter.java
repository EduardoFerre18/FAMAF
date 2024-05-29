package namedEntities;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.Normalizer;
import java.io.IOException;
import org.json.JSONArray;
import org.json.JSONObject;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

import javax.print.attribute.standard.MediaSize;
import namedEntities.categories.Category;
import namedEntities.categories.Location;
import namedEntities.categories.Organization;
import namedEntities.categories.Other;
import namedEntities.categories.Person;

public class Sorter {
    private static JSONArray jsonArray;

    // Metodo privado para quitar diacriticos al comparar entre el diccionario y las
    // palabras tomadas.
    private static String removeDiacritics(String str) {
        String normalized = Normalizer.normalize(str, Normalizer.Form.NFD);
        Pattern pattern = Pattern.compile("\\p{InCombiningDiacriticalMarks}+");
        return pattern.matcher(normalized).replaceAll("");
    }

    // Metodo para clasificar al texto tomado segun lo que se encuentra en el
    // diccionario.
    public static NamedEntity Create(String text) {

        if (jsonArray == null) {
            try {
                String filepath = "src/data/dictionary.json";
                String contenido = new String(Files.readAllBytes(Paths.get(filepath)));
                jsonArray = new JSONArray(contenido);

            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        }

        String textoNormalizado = removeDiacritics(text).toLowerCase();

        for (int i = 0; i < jsonArray.length(); i++) {
            JSONObject jsonObject = jsonArray.getJSONObject(i);
            JSONArray keywords = jsonObject.getJSONArray("keywords");

            for (int j = 0; j < keywords.length(); j++) {
                String keywordNormal = removeDiacritics(keywords.getString(j)).toLowerCase();
                if (keywordNormal.equals(textoNormalizado)) {
                    String category = jsonObject.getString("Category");
                    String label = jsonObject.getString("label");
                    JSONArray topics = jsonObject.getJSONArray("Topics");
                    List<String> topicsList = new ArrayList<>();
                    for (int k = 0; k < topics.length(); k++) {
                        topicsList.add(topics.getString(k));
                    }

                    NamedEntity namedEntity = new NamedEntity(label);

                    if (category.equalsIgnoreCase("PERSON")) {
                        namedEntity.setCategory(new Person(text, label, 30));
                    } else if (category.equalsIgnoreCase("LOCATION")) {
                        namedEntity.setCategory(new Location(1, 2, 3));
                    } else if (category.equalsIgnoreCase("ORGANIZATION")) {
                        namedEntity.setCategory(new Organization(text));
                    }

                    namedEntity.setTopics(topicsList);
                    return namedEntity;
                }
            }
        }

        NamedEntity nueva = new NamedEntity(text);
        nueva.setCategory(new Other());
        nueva.setTopics(Arrays.asList("OTHER"));
        return nueva;
    }
}