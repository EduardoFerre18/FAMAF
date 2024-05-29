package feed;

public class Article {
    private String title;
    private String description;
    private String pubDate;
    private String link;

    public Article(String title, String description, String pubDate, String link) {
        this.title = title;
        this.description = description;
        this.pubDate = pubDate;
        this.link = link;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public String getPubDate() {
        return pubDate;
    }

    public String getLink() {
        return link;
    }

    public void print() {
        System.out.println("Title: " + (title != null ? title : "No hay título."));
        System.out.println("Description: " + (description != null ? description : "No hay descripción."));
        System.out.println("Publication Date: " + (pubDate != null ? pubDate : "No hay fecha de publicación."));
        System.out.println("Link: " + (link != null ? link : "No hay link."));
        System.out.println("*".repeat(80));
    }

}