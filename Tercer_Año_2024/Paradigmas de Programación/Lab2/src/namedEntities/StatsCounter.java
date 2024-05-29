package namedEntities;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StatsCounter {
    private Map<String, Map<String, Integer>> categoryCounts;
    private Map<String, Map<String, Integer>> topicCounts;

    public StatsCounter() {
        categoryCounts = new HashMap<>();
        topicCounts = new HashMap<>();

        initializeMaps(categoryCounts, "Person", "Location", "Organization", "Other");
        initializeMaps(topicCounts, "SPORTS", "POLITICS", "ECONOMICS", "BUSINESS", "TECHNOLOGY", "ENTERTAINMENT",
                "OTHER");
    }

    private void initializeMaps(Map<String, Map<String, Integer>> map, String... keys) {
        for (String key : keys) {
            map.put(key, new HashMap<>());
        }
    }

    public void addCount(Map<String, Integer> map, String name, int count) {
        map.put(name, map.getOrDefault(name, 0) + count);
    }

    public void compute(NamedEntity entity) {
        String name = entity.getName();
        String category = entity.getCategoryName();
        List<String> topics = entity.getTopics();

        addCount(categoryCounts.getOrDefault(category, categoryCounts.get("Other")), name, 1);

        if (topics != null) {
            for (String topic : topics) {
                addCount(topicCounts.getOrDefault(topic, topicCounts.get("OTHER")), name, 1);
            }
        }
    }

    public Map<String, Integer> getCategoryCounts(String category) {
        return categoryCounts.getOrDefault(category, new HashMap<>());
    }

    public Map<String, Integer> getTopicCounts(String topic) {
        return topicCounts.getOrDefault(topic, new HashMap<>());
    }

    public void printCounts(Map<String, Integer> counts) {
        for (Map.Entry<String, Integer> entry : counts.entrySet()) {
            System.out.printf("\t%-20s (%d)\n", entry.getKey(), entry.getValue());
        }
        System.out.println();
    }

}
