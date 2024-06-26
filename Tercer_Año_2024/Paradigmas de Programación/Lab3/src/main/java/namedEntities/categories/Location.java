package namedEntities.categories;

import java.util.HashMap;

import namedEntities.heuristics.CapitalizedWordHeuristic;

public class Location extends Category {

    public Location(double x, double y, double z) {
        attrbs.put("X", String.valueOf(x));
        attrbs.put("Y", String.valueOf(y));
        attrbs.put("Z", String.valueOf(z));
    }
}