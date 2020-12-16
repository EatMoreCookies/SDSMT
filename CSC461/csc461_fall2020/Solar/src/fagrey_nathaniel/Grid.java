package fagrey_nathaniel;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Grid {
    private final int rowSize = 5;
    private final int colSize = 5;
    private Empty[][] grid = new Empty[rowSize][colSize];

    Grid( ) {
        init();
    }

    private void init( ){
        for( int i = 0; i < rowSize; ++i ) {
            for( int j = 0; j < colSize; ++j ) {
                grid[i][j] = new Empty();
            }
        }
    }

    public void printGrid( ) {

        for( int i = 0; i < rowSize; ++i ) {
            for (int j = 0; j < colSize; ++j) {
                System.out.print(grid[i][j].printCharacter());
            }

            System.out.println();
        }
    }

    public void countTypes(){
        Count visitor = new Count();

        //GRADING: COUNT
        runVisitor(visitor);

        System.out.println( "Empty: " + visitor.getEmptyCount() + "\nGreenspaces: " + visitor.getGreenSpaceCount() + "\nPanel: " + visitor.getPanelCount() + "\nLight: " + visitor.getLightBulbCount());
    }

    public void colorType( Scanner cin ) {
        Color visitor = new Color();

        int input = 0;
        int xCoord, yCoord;

        Empty space = getSpaceChoice(cin);
        ColorText.Color color = ColorText.Color.BLACK;


        System.out.print( "Input color 1) red 2) yellow 3) blue 4) green #) black: " );
        input = cin.nextInt();

        switch( input ){
            case 1:
                color = ColorText.Color.RED;
                break;
            case 2:
                color = ColorText.Color.YELLOW;
                break;
            case 3:
                color = ColorText.Color.BLUE;
                break;
            case 4:
                color = ColorText.Color.GREEN;
                break;
            default:
                break;
        }

        visitor.setType( space.type);
        visitor.setColor(color);
        // GRADING: COLOR
        runVisitor(visitor);
    }

    public void runVisitor( Visitor visitor ){
        for( int i = 0; i < rowSize; ++i ) {
            for (int j = 0; j < colSize; ++j) {
                grid[i][j].visit(visitor);
            }
        }
    }

    public void setArea(Scanner cin) {
        int input = 0;
        int xCoord, yCoord;

        Empty space = getSpaceChoice( cin );

        System.out.print("Input location (x y): ");
        xCoord = cin.nextInt();
        yCoord = cin.nextInt();

        if ( !checkCoordinates(xCoord, yCoord) )
            throw new InputMismatchException();

        grid[yCoord][xCoord] = space;
    }

    public void removeArea( Scanner cin ) {
        int xCoord, yCoord;

        System.out.print("Input location (x y): ");
        xCoord = cin.nextInt();
        yCoord = cin.nextInt();

        if ( !checkCoordinates(xCoord, yCoord) )
            throw new InputMismatchException();

        grid[yCoord][xCoord] = new Empty();
    }

    public void makeDefaultGrid() {
        grid[0][0] = new Panel();
        grid[0][1] = new Panel();
        grid[0][2] = new Panel();
        grid[0][4] = new GreenSpace();

        grid[1][0] = new LightBulb();
        grid[1][1] = new LightBulb();
        grid[1][2] = new LightBulb();
        grid[1][3] = new Panel();

        grid[2][1] = new Panel();
        grid[2][2] = new Panel();
        grid[2][3] = new LightBulb();
        grid[2][4] = new Panel();

        grid[3][3] = new Panel();

        grid[4][0] = new GreenSpace();
        grid[4][1] = new LightBulb();
        grid[4][4] = new GreenSpace();
    }

    private boolean checkCoordinates(int x, int y ){
        if( x > 4 || x < 0 )
            return false;

        if( y > 4 || y < 0 )
            return false;

        return true;
    }

    private Empty getSpaceChoice( Scanner cin ){

        System.out.print( "Input area type 1) greenspace 2) light 3) panel #) empty: " );
        int input = cin.nextInt();
        Empty space = new Empty();

        switch( input ){
            case 1:
                space = new GreenSpace();
                break;
            case 2:
                space = new LightBulb();
                break;
            case 3:
                space = new Panel();
                break;
            default:
                break;
        }

        return space;
    }

    public void colorLightBulb( ){
        LightUp visitor = new LightUp();
        visitor.storeGrid( this );

        runVisitor(visitor);
    }

    public Empty checkGridSpace( int x, int y){
        return grid[y][x];
    }
}

