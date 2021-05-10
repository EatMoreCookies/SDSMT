package fagrey_nathaniel;

import javafx.application.Application;
import javafx.collections.ObservableList;
import javafx.event.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.stage.Stage;

/*
Author: Nathaniel Fagrey
Class: CSC468/568 GUI Spring 2021
Description: A simple GUI example that negates and/or doubles a given
             number.
Checklist:
_x_ [3pt] Java FX project made and submitted correctly
_x_ [3pt] All three views there, clearly visible, and not overlapping
_x_ [3pt] Negate works
_x_ [3pt] x2 works

Extensions: JavaFX
Known Bugs: An entered number will automatically be converted to a double
            with a '.0' post-fix. Not a huge deal, but something to consider
            in the future.
*/

public class JavaCheckIn extends Application {
    private TextField input = new TextField();
    private Button negate = new Button("Negate");
    private Button x2= new Button("x2");

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start( Stage primaryStage) {
        //Parent will accept any Group or Pane
        Parent root = makeContents();

        Scene scene = new Scene(root, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Java Check In");
        primaryStage.show();
    }
    private Group makeContents( ) {

        Group g = new Group();
        ObservableList<Node> layout = g.getChildren();
        negate.setLayoutY(40);
        x2.setLayoutY((80));
        layout.addAll(input, negate, x2);

        input.setText(Integer.toString(2));

        negate.addEventFilter(ActionEvent.ACTION, new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                double temp = Double.parseDouble(input.getText());
                temp *= -1;
                input.setText(Double.toString(temp));
            }
        });

        x2.addEventFilter(ActionEvent.ACTION, new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                double temp = Double.parseDouble(input.getText());
                temp *= 2;
                input.setText(Double.toString(temp));
            }
        });

        return g;
    }
}