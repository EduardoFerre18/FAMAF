package feed;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.util.ArrayList;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.List;

public class FeedParser {

    // Método para obtener el valor de un elemento en un documento XML
    private static String getElementValue(Element parent, String tagName) {
        NodeList nodeList = parent.getElementsByTagName(tagName);
        if (nodeList != null && nodeList.getLength() > 0) {
            NodeList subList = nodeList.item(0).getChildNodes();
            if (subList != null && subList.getLength() > 0) {
                return subList.item(0).getNodeValue();
            }
        }
        return null;
    }

    public static List<Article> parseXML(String xmlData) {
        List<Article> articles = new ArrayList<>();

        try {
            // Creo un DocumentBuilder
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();

            // Parseo el string XML a un Document
            InputStream is = new ByteArrayInputStream(xmlData.getBytes());
            Document doc = builder.parse(is);

            // Normalizo el documento XML
            doc.getDocumentElement().normalize();

            // Obtengo todos los nodos <item> en el documento
            NodeList nodeList = doc.getElementsByTagName("item");

            // Itero a través de los nodos <item>
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);

                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;

                    // Obtengo los valores de los elementos <title>, <description>, <pubDate>,
                    // <link>
                    String title = getElementValue(element, "title");
                    String description = getElementValue(element, "description");
                    String pubDate = getElementValue(element, "pubDate");
                    String link = getElementValue(element, "link");

                    // Creo una nueva instancia de Article y la agrego a la lista
                    Article article = new Article(title, description, pubDate, link);
                    articles.add(article);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return articles;
    }

    public static String fetchFeed(String feedURL) throws MalformedURLException, IOException, Exception {

        URL url = new URL(feedURL);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();

        connection.setRequestMethod("GET");
        connection.setRequestProperty("Content-Type", "application/json");

        // Si todos los grupos usan el mismo user-agent, el servidor puede bloquear las
        // solicitudes.
        connection.setRequestProperty("User-agent", "JEF-dream-team");
        connection.setConnectTimeout(5000);
        connection.setReadTimeout(5000);

        int status = connection.getResponseCode();
        if (status != 200) {
            throw new Exception("HTTP error code: " + status);
        } else {
            BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String inputLine;
            StringBuffer content = new StringBuffer();
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
                content.append("\n");
            }
            in.close();
            connection.disconnect();
            return content.toString();
        }
    }
}
