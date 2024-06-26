package namedEntities.heuristics;

import org.apache.spark.api.java.JavaRDD;

import java.util.List;

public interface Heuristic {
    public JavaRDD<String> extractCandidates(JavaRDD<String> text);
}