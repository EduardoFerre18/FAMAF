package namedEntities.categories;

import java.util.HashMap;

public class Person extends Category {

    public Person(String name, String lastName, int age) {
        attrbs.put("NAME", name);
        attrbs.put("LASTNAME", lastName);
        attrbs.put("AGE", String.valueOf(age));
    }

}
