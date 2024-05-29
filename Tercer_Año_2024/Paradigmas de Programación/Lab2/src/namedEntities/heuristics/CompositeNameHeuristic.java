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