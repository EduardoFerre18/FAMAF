package feed;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class BigDataFile {
    public static List<Article> buildFile() {
        List<Article> allArticles = new ArrayList<Article>();
        Path feedsFilePath = Paths.get("src/main/java/data/feeds.json");
        Path outputFilePath = Paths.get("src/main/java/data/big_data.txt");

        try (BufferedReader feedsReader = new BufferedReader(new FileReader(feedsFilePath.toFile()));
                BufferedWriter outputWriter = new BufferedWriter(new FileWriter(outputFilePath.toFile()))) {

            JSONTokener tokener = new JSONTokener(feedsReader);
            JSONArray feeds = new JSONArray(tokener);

            for (int i = 0; i < feeds.length(); i++) {
                JSONObject feed = feeds.getJSONObject(i);
                String feedUrl = feed.getString("url");

                try {
                    String feedData = FeedParser.fetchFeed(feedUrl);
                    List<Article> articles = FeedParser.parseXML(feedData);
                    allArticles.addAll(articles);
                    for (Article article : articles) {
                        outputWriter.write(article.getTitle() + "\n" + article.getDescription() + "\n");
                        outputWriter.newLine();
                    }
                } catch (Exception e) {
                    System.err.println("Error procesando el feed: " + feedUrl);
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            System.err.println("Error leyendo el archivo feeds.json: " + feedsFilePath.toAbsolutePath());
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return allArticles;
    }
}
