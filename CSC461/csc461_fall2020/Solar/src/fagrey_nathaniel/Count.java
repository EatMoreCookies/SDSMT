package fagrey_nathaniel;

public class Count implements Visitor {
    private int emptyCount = 0;
    private int greenSpaceCount = 0;
    private int lightBulbCount = 0;
    private int panelCount = 0;

    @Override
    public void accept( Empty e ) {
        ++emptyCount;
    }

    @Override
    public void accept( GreenSpace g ) {
        ++greenSpaceCount;
    }

    @Override
    public void accept( LightBulb b ) {
        ++lightBulbCount;
    }

    @Override
    public void accept( Panel p ) {
        ++panelCount;
    }

    public int getEmptyCount() {
        return emptyCount;
    }

    public int getGreenSpaceCount() {
        return greenSpaceCount;
    }

    public int getLightBulbCount() {
        return lightBulbCount;
    }

    public int getPanelCount() {
        return panelCount;
    }
}
