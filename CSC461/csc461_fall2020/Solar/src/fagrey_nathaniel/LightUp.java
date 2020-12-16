package fagrey_nathaniel;

import java.util.ArrayList;

public class LightUp implements Visitor {

    private ArrayList<Integer> gridPoints = new ArrayList<Integer>();
    private Grid grid;
    private int numPanels;
    private int x = 0;
    private int y = 0;

    public void accept( Empty e ) {
        storeGridPoints();
    }

    public void accept( GreenSpace g ) {
        storeGridPoints();
    }

    public void accept( LightBulb b ) {
        //GRADING: NESTED
        CheckAdjacent visitor = new CheckAdjacent();
        int lightBulbX, lightBulbY;

        storeGridPoints();

        // Get light bulb grid points
        lightBulbX = gridPoints.get(gridPoints.size()-2);
        lightBulbY = gridPoints.get(gridPoints.size()-1);

        // Check all adjacent spaces
        grid.checkGridSpace( checkGridPoints(lightBulbX, -1), lightBulbY ).visit(visitor);
        grid.checkGridSpace(checkGridPoints(lightBulbX, 1), lightBulbY ).visit(visitor);
        grid.checkGridSpace(lightBulbX, checkGridPoints(lightBulbY, 1 )).visit(visitor);
        grid.checkGridSpace(lightBulbX, checkGridPoints(lightBulbY , -1 )).visit(visitor);

        numPanels = visitor.getNumPanels();

        changeColor(b, numPanels );
    }

    public void accept( Panel p ) {
        storeGridPoints();
    }

    private void storeGridPoints( ){
        if( x > 4 ){
            x = 0;
            y += 1;
        }

        gridPoints.add(x);
        gridPoints.add(y);

        x += 1;
    }

    public void storeGrid( Grid grid ){
        this.grid = grid;
    }

    private int checkGridPoints( int x, int diff ){
        if( x + diff > 4 || x + diff < 0 )
            return x;
        else
            return x + diff;
    }

    private void changeColor( LightBulb b, int numPanels ){
        switch (numPanels){
            case 0:
                b.setColor(ColorText.Color.BLACK);
                break;
            case 1:
                b.setColor(ColorText.Color.GRAY);
                break;
            case 2:
                b.setColor(ColorText.Color.ORANGE);
                break;
            case 3:
                b.setColor(ColorText.Color.YELLOW);
                break;
            default:
                b.setColor(ColorText.Color.LIGHT_YELLOW);
                break;
        }
    }
}
