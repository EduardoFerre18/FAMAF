package namedEntities.heuristics;

import org.apache.spark.api.java.JavaRDD;

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
    public JavaRDD<String> extractCandidates(JavaRDD<String> text) {
        JavaRDD<String> capitalizedCandidates = super.extractCandidates(text);
        JavaRDD<String> filteredCandidates = capitalizedCandidates.filter(s -> !commonWords.contains(s));
        return filteredCandidates;
    }
}
