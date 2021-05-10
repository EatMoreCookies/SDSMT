package fagrey_nathaniel;

import javafx.event.ActionEvent;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.*;

public class ApartmentComplexView extends GridPane {
    private ApartmentComplex apartmentComplex;
    private Controller control;
    private int currCols = 3;

    ApartmentComplexView(){
        setRowConstraints();
        setColConstraints();
        setAlignment(Pos.TOP_CENTER);
    }

    private void setColConstraints(){
        for( int i = 0; i < currCols; ++i) {
            ColumnConstraints col = new ColumnConstraints();
            col.setPercentWidth(Math.floor(100.0/this.currCols));
            getColumnConstraints().add(col);
        }
    }

    private void setRowConstraints(){
        for( int i = 0; i < 7; ++i ){
            RowConstraints row1 = new RowConstraints();
            row1.setPercentHeight(14);
            getRowConstraints().add(row1);
        }
    }

    void setModel( ApartmentComplex ac, Controller controller){
        this.apartmentComplex = ac;
        this.control = controller;
    }

    void resize(int col){
        getChildren().clear();
        getRowConstraints().clear();
        getColumnConstraints().clear();

        this.currCols = col;

        setColConstraints();
        setRowConstraints();

        for( int index = 0; index < this.currCols; index++){
            Button button = new Button("Build");
            button.setMaxWidth(Double.MAX_VALUE);
            button.setMaxHeight(50);
            button.addEventFilter(ActionEvent.ACTION, control.new BuildFloor(index));
            add( button, index, 0);
        }
    }

    public void addView(ApartmentView apartmentView, int index) {
        add(apartmentView, index, apartmentComplex.getAvailableRows()[index] + 1);
    }
}
