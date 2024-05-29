package namedEntities;

import java.util.HashMap;
import java.util.List;
import namedEntities.categories.*;

public class NamedEntity {
    // campos encapsulados
    private Category cat;
    private List<String> topics;
    private String name;

    // Constructor sobrecargado
    public NamedEntity(String name) {
        cat = null;
        topics = null;
        this.name = name;
    }

    // Constructor sobrecargado
    public NamedEntity(Category cat, List<String> topics, String name) {
        this.cat = cat;
        this.topics = topics;
        this.name = name;
    }

    public void setCategory(Category cat) {
        this.cat = cat;
    }

    public void setTopics(List<String> topics) {
        this.topics = topics;
    }

    public String getName() {
        return name;
    }

    public String getCategoryName() {
        return (cat != null) ? cat.getName() : null;
    }

    public List<String> getTopics() {
        return topics;
    }

    public HashMap<String, String> getAttrbs() {
        return cat.getAttrbs();
    }

}