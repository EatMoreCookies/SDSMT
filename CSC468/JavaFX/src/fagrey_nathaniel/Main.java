package fagrey_nathaniel;

import javafx.application.Application;
import javafx.scene.layout.HBox;
import javafx.scene.Scene;
import javafx.stage.Stage;

/*

Author: Nathaniel Fagrey

Class: CSC468/568 GUI Spring 2021

Tierless: Initial Layout with 3 buildings 	30 total
__X__ Location of info bar, command bar, build bar, and apartment complex in correct areas
__X__ Info and command areas properly spaced
__X__ Command bar vertically aligned and in correct order
__X__ Apartment complex area fill the remaining space
__X__ Floors are even rectangles
__X__ All of the above holds true on window resize

1. Tier: Functionality 	40  total
__X__ Able to add a new floor
__X__ New floor build costs applied properly
__X__ Rent increase does not affect new tenants
__X__ Rent increase works on all tenants, and does not affect Empty floors
__X__ Able to remodel the 3 apartment types
__X__ Remodeling immediately, and properly affects monthly funds, rent, maintenance, and filled
__X__ New month affects tenants time since remodel, run time, and funds.


2. Tier: Stress Test with Resize	30  total
__X__ Resize clears the apartment complex area
__X__ Correct # of build buttons after resize
__X__ New floors the right size after resize (filled area and evenly sized)
__X__ Resize reset info pane (5 items, evenly weighted)
__X__ All of tier 3 still works (-3 for each up to a max)


3 Final Tier: Extensions	20  total
Extension 1: 1. 10pts. Add Images: When upgrading floors, images will appear for Basic and Penthouse floors.
Extension 2: 3. 10pts. Menu Bar: Will appear on bottom right of screen.

*/

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Layout layout = new Layout();
        HBox root = layout.makeLayout();

        primaryStage.setTitle("Apartment Complex Simulator");
        primaryStage.setScene(new Scene(root, 800, 400));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
