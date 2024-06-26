package namedEntities.heuristics;

import org.apache.spark.api.java.JavaRDD;

import java.text.Normalizer;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CapitalizedWordHeuristic implements Heuristic {

    @Override
    public JavaRDD<String> extractCandidates(JavaRDD<String> text) {
        JavaRDD<String> candidates1 = text.map(s -> s.replaceAll("[-+.^:,\"]", ""));
        JavaRDD<String> candidates2 = candidates1.map(s -> Normalizer.normalize(s, Normalizer.Form.NFD));
        JavaRDD<String> candidates3 = candidates2.map(s -> s.replaceAll("\\p{M}", ""));
        Pattern space = Pattern.compile(" ");
        JavaRDD<String> candidates4 = candidates3.flatMap(s -> Arrays.asList(space.split(s)).iterator());
        JavaRDD<String> candidates5 = candidates4.filter(s -> s.matches("[A-Z][a-z]+(?:\\\\s[A-Z][a-z]+)*"));
        return candidates5;
    }
}
