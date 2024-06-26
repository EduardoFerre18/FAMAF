package utils;

public class Config {
    private boolean printHelp = false;
    private boolean printFeed = false;
    private boolean computeNamedEntities = false;
    private String feedKey;
    private String heuristicKey;
    private String formatKey;

    public Config(boolean printHelp, boolean printFeed, boolean computeNamedEntities, String feedKey,
            String heuristicKey, String formatKey) {
        this.printHelp = printHelp;
        this.printFeed = printFeed;
        this.computeNamedEntities = computeNamedEntities;
        this.feedKey = feedKey;
        this.heuristicKey = heuristicKey;
        this.formatKey = formatKey;
    }

    public boolean getPrintHelp() {
        return printHelp;
    }

    public boolean getPrintFeed() {
        return printFeed;
    }

    public boolean getComputeNamedEntities() {
        return computeNamedEntities;
    }

    public String getFeedKey() {
        return feedKey;
    }

    public String getHeuristicKey() {
        return heuristicKey;
    }

    public String getFormatKey() {
        return formatKey;
    }

}
