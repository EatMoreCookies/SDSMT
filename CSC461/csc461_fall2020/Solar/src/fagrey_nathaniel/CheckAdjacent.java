package fagrey_nathaniel;

public class CheckAdjacent implements Visitor {
    private int numPanels = 0;

    public void accept( Empty e ) { }

    public void accept( GreenSpace g ) { }

    public void accept( LightBulb b ) { }

    public void accept( Panel p ) {
        ++numPanels;
    }

    public int getNumPanels(){
        return numPanels;
    }
}
