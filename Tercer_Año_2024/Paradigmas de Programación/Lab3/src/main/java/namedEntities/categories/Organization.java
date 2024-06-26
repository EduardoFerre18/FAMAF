package namedEntities.categories;

import java.util.HashMap;
import namedEntities.heuristics.CapitalizedWordHeuristic;

public class Organization extends Category {

    public Organization(String country) {
        attrbs.put("COUNTRY", country);
    }

}