package namedEntities.heuristics;

import java.util.List;

public interface Heuristic {
    public List<String> extractCandidates(String text);
}