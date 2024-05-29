import feed.Article;
import feed.FeedParser;
import java.io.IOException;
import java.util.ArrayList;
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

public class App {

    public static void main(String[] args) {
        List<FeedsData> feedsDataArray = new ArrayList<>();
        try {
            feedsDataArray = JSONParser.parseJsonFeedsData("src/data/feeds.json");
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        UserInterface ui = new UserInterface();
        Config config = ui.handleInput(args);
        run(config, feedsDataArray);
    }

    private static void run(Config config, List<FeedsData> feedsDataArray) {

        if (config.getPrintHelp()) {
            printHelp(feedsDataArray);
            return;
        }

        if (feedsDataArray == null || feedsDataArray.size() == 0) {
            System.out.println("No feeds data found");
            return;
        }

        HashMap<String, String> feedUrls = new HashMap<>();
        for (FeedsData feedData : feedsDataArray) {
            if (config.getFeedKey() == null || config.getFeedKey().equals(feedData.getLabel())) {
                feedUrls.put(feedData.getLabel(), feedData.getUrl());
            }
        }

        List<Article> allArticles = new ArrayList<>();
        for (String url : feedUrls.values()) {
            try {
                String xmlData = FeedParser.fetchFeed(url);
                List<Article> articles = FeedParser.parseXML(xmlData);
                allArticles.addAll(articles);
            } catch (Exception e) {
                System.out.println("Error fetching feed: " + url);
                e.printStackTrace();
            }
        }

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

            StatsCounter counter = new StatsCounter();

            System.out.println("Computing named entities using " + heuristic.getClass().getSimpleName());

            System.out.println("\nStats: ");
            System.out.println("-".repeat(80));

            for (Article article : allArticles) {
                String articleText = article.getTitle() + article.getDescription();
                if (articleText != null) {
                    List<String> candidates = heuristic.extractCandidates(articleText);

                    for (String candidate : candidates) {
                        NamedEntity entity = Sorter.Create(candidate);
                        // Create puede devolver null
                        if (entity == null) {
                            System.out.println("Error creating entity");
                            System.exit(1);
                        }
                        counter.compute(entity);
                    }
                }
            }

            // Imprimir estadísticas basadas en el formato especificado
            if (format != null && format.equals("topic")) {
                Map<String, Map<String, Integer>> topicCounts = new HashMap<>();
                topicCounts.put("SPORTS", counter.getTopicCounts("SPORTS"));
                topicCounts.put("POLITICS", counter.getTopicCounts("POLITICS"));
                topicCounts.put("ECONOMICS", counter.getTopicCounts("ECONOMICS"));
                topicCounts.put("BUSINESS", counter.getTopicCounts("BUSINESS"));
                topicCounts.put("TECHNOLOGY", counter.getTopicCounts("TECHNOLOGY"));
                topicCounts.put("ENTERTAINMENT", counter.getTopicCounts("ENTERTAINMENT"));
                topicCounts.put("OTHER", counter.getTopicCounts("OTHER"));

                for (Map.Entry<String, Map<String, Integer>> topicEntry : topicCounts.entrySet()) {
                    String topicName = topicEntry.getKey();
                    Map<String, Integer> counts = topicEntry.getValue();

                    if (!counts.isEmpty()) {
                        System.out.println("Topic: " + topicName);
                        counter.printCounts(counts);
                    }
                }

            } else {
                Map<String, Map<String, Integer>> categoryCounts = new HashMap<>();
                categoryCounts.put("Person", counter.getCategoryCounts("Person"));
                categoryCounts.put("Location", counter.getCategoryCounts("Location"));
                categoryCounts.put("Organization", counter.getCategoryCounts("Organization"));
                categoryCounts.put("Other", counter.getCategoryCounts("Other"));

                for (Map.Entry<String, Map<String, Integer>> categoryEntry : categoryCounts.entrySet()) {
                    String categoryName = categoryEntry.getKey();
                    Map<String, Integer> counts = categoryEntry.getValue();

                    if (!counts.isEmpty()) {
                        System.out.println("Category: " + categoryName.toUpperCase());
                        counter.printCounts(counts);
                    }
                }
            }
        }

    }

    private static void printHelp(List<FeedsData> feedsDataArray) {
        System.out.println("Usage: make run ARGS=\"[OPTION]\"");
        System.out.println("Options:");
        System.out.println("  -h, --help: Show this help message and exit");
        System.out.println("  -f, --feed <feedKey>:                Fetch and process the feed with");
        System.out.println("                                       the specified key");
        System.out.println("                                       Available feed keys are: ");
        for (FeedsData feedData : feedsDataArray) {
            System.out.println("                                       " + feedData.getLabel());
        }
        System.out.println("  -ne, --named-entity <heuristicName>: Use the specified heuristic to extract");
        System.out.println("                                       named entities");
        System.out.println("                                       Available heuristic names are: ");
        System.out.println("                                       cwh: Capitalized word heuristic");
        System.out.println("                                       cnh: Composite name heuristic");
        System.out.println("                                       ceh: Contextual entity heuristic");
        System.out.println("  -pf, --print-feed:                   Print the fetched feed");
        System.out.println("  -sf, --stats-format <format>:        Print the stats in the specified format");
        System.out.println("                                       Available formats are: ");
        System.out.println("                                       cat: Category-wise stats");
        System.out.println("                                       topic: Topic-wise stats");
    }

}