import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.SparkConf;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.broadcast.Broadcast;
import org.json.JSONArray;
import java.nio.file.Files;
import scala.Tuple2;
import feed.Article;
import feed.FeedParser;
import feed.BigDataFile;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import namedEntities.*;
import namedEntities.heuristics.CapitalizedWordHeuristic;
import namedEntities.heuristics.CompositeNameHeuristic;
import namedEntities.heuristics.ContextualEntityHeuristic;
import namedEntities.heuristics.Heuristic;
import utils.Config;
import utils.FeedsData;
import utils.JSONParser;
import utils.UserInterface;
import utils.JSONArrayS;

public class App {
    public static void main(String[] args) {
        List<FeedsData> feedsDataArray = new ArrayList<>();
        try {
            feedsDataArray = JSONParser.parseJsonFeedsData("src/main/java/data/feeds.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        UserInterface ui = new UserInterface();
        Config config = ui.handleInput(args);
        run(config, feedsDataArray);
    }

    private static void run(Config config, List<FeedsData> feedsDataArray) {
        JSONArrayS jsonArray;
        if (config.getPrintHelp()) {
            printHelp(feedsDataArray);
            return;
        }

        if (feedsDataArray == null || feedsDataArray.size() == 0) {
            System.out.println("No feeds data found");
            return;
        }

        List<Article> allArticles = BigDataFile.buildFile();

        if (config.getPrintFeed() || !config.getComputeNamedEntities()) {
            allArticles.forEach(Article::print);
        }

        if (config.getComputeNamedEntities()) {
            String heuristicKey = config.getHeuristicKey();
            String format = config.getFormatKey();
            Heuristic heuristic = null;

            switch (heuristicKey) {
                case "cwh":
                    heuristic = new CapitalizedWordHeuristic();
                    break;
                case "cnh":
                    heuristic = new CompositeNameHeuristic();
                    break;
                case "ceh":
                    heuristic = new ContextualEntityHeuristic();
                    break;
                default:
                    System.out.println("There is no heuristic called \"" + heuristicKey + "\". Use flag -h for help");
                    System.exit(1);
            }

            System.out.println("Computing named entities using " + heuristic.getClass().getSimpleName());

            System.out.println("\nStats: ");
            System.out.println("-".repeat(80));

            // Iniciamos una sesion de Spark
            SparkSession spark = SparkSession.builder().appName("Lab3g22").getOrCreate();
            // Creamos Resilient Distributed Datasets (RDDs) para
            // aplicar transformaciones sucesivas a los datos
            JavaRDD<String> lines = spark.read().textFile("src/main/java/data/wiki_dump_parcial.txt").javaRDD();
            JavaRDD<String> candidates = heuristic.extractCandidates(lines);
            try {
                String filepath = "src/main/java/data/dictionary.json";
                String contenido = new String(Files.readAllBytes(Paths.get(filepath)));
                jsonArray = new JSONArrayS(contenido);
                JavaRDD<NamedEntity> entities = candidates.map(c -> Sorter.Create(c, jsonArray));
                // Imprimir estadísticas basadas en el formato especificado
                if (format != null && format.equals("topic")) {
                    // Invoca una accion de Spark; recien en este punto se
                    // empiezan a realizar calculos (laziness)
                    List<Tuple2<String, Tuple2<List<String>, Integer>>> results = StatsCounter
                            .computeTopicStats(entities);
                    for (String s : Arrays.asList("SPORTS", "POLITICS", "ECONOMICS", "BUSINESS", "TECHNOLOGY",
                            "ENTERTAINMENT",
                            "OTHER")) {
                        System.out.println("Topic: " + s);
                        for (Tuple2<String, Tuple2<List<String>, Integer>> t : results) {
                            if (t._2()._1().contains(s)) {
                                System.out.printf("\t%-20s (%d)\n", t._1(), t._2()._2());
                            }
                        }
                    }

                } else {
                    // Invoca una accion de Spark; recien en este punto se
                    // empiezan a realizar calculos (laziness)
                    List<Tuple2<String, Tuple2<String, Integer>>> results = StatsCounter.computeCatStats(entities);
                    for (String s : Arrays.asList("OTHER", "ORGANIZATION", "LOCATION", "PERSON")) {
                        System.out.println("Category: " + s);
                        for (Tuple2<String, Tuple2<String, Integer>> t : results) {
                            if (t._2()._1().equalsIgnoreCase(s)) {
                                System.out.printf("\t%-20s (%d)\n", t._1(), t._2()._2());
                            }
                        }
                    }
                }

            } catch (IOException e) {
                e.printStackTrace();
                System.out.println(e);
                System.exit(1);
            }
            // Cerramos la sesion de Spark
            spark.stop();
        }

    }

    private static void printHelp(List<FeedsData> feedsDataArray) {
        System.out.println("Usage: make run ARGS=\"[OPTION]\"");
        System.out.println("Options:");
        System.out.println("  -h, --help: Show this help message and exit");
        System.out.println("  -ne, --named-entity <heuristicName>: Use the specified heuristic to extract");
        System.out.println("                                       named entities");
        System.out.println("                                       Available heuristic names are: ");
        System.out.println("                                       cwh: Capitalized word heuristic");
        System.out.println("                                       cnh: Composite name heuristic");
        System.out.println("                                       ceh: Contextual entity heuristic");
        System.out.println("  -sf, --stats-format <format>:        Print the stats in the specified format");
        System.out.println("                                       Available formats are: ");
        System.out.println("                                       cat: Category-wise stats");
        System.out.println("                                       topic: Topic-wise stats");
    }

}