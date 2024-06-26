package namedEntities;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import scala.Tuple2;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StatsCounter {
        public static List<Tuple2<String, Tuple2<List<String>, Integer>>> computeTopicStats(
                        JavaRDD<NamedEntity> entities) {
                JavaPairRDD<String, Tuple2<List<String>, Integer>> tuples = entities
                                .mapToPair(e -> new Tuple2(e.getName(), new Tuple2(e.getTopics(), 1)));

                JavaPairRDD<String, Tuple2<List<String>, Integer>> reduced = tuples
                                .reduceByKey((a, b) -> new Tuple2(a._1(), a._2() + b._2()));

                // Accion de Spark; recien cuando se llama a collect sobre un RDD
                // se hacen los calculos (laziness)
                return reduced.collect();
        }

        public static List<Tuple2<String, Tuple2<String, Integer>>> computeCatStats(JavaRDD<NamedEntity> entities) {
                JavaPairRDD<String, Tuple2<String, Integer>> tuples = entities
                                .mapToPair(e -> new Tuple2(e.getName(), new Tuple2(e.getCategoryName(), 1)));

                JavaPairRDD<String, Tuple2<String, Integer>> reduced = tuples
                                .reduceByKey((a, b) -> new Tuple2(a._1(), a._2() + b._2()));

                // Accion de Spark; recien cuando se llama a collect sobre un RDD
                // se hacen los calculos (laziness)
                return reduced.collect();

        }
}
