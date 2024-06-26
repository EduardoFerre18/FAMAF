package namedEntities.heuristics;

import org.apache.spark.api.java.JavaRDD;

import java.text.Normalizer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// Heuristica para buscar cadena de 2 o mas palabras que comiencen con mayuscula
public class CompositeNameHeuristic implements Heuristic {

    @Override
    public JavaRDD<String> extractCandidates(JavaRDD<String> text) {
        JavaRDD<String> candidates1 = text.map(s -> s.replaceAll("[-+.^:,\"]", ""));
        JavaRDD<String> candidates2 = candidates1.map(s -> Normalizer.normalize(s, Normalizer.Form.NFD));
        JavaRDD<String> candidates3 = candidates2.map(s -> s.replaceAll("\\p{M}", ""));
        Pattern pattern = Pattern.compile("\\b[A-Z][a-z]*\\b(?:\\s\\b[A-Z][a-z]*\\b)+");
        JavaRDD<String> candidates4 = candidates3.flatMap(s -> {
            Matcher matcher = pattern.matcher(s);
            List<String> matches = new ArrayList<>();
            while (matcher.find()) {
                matches.add(matcher.group());
            }
            return matches.iterator();
        });
        return candidates4;
    }
}