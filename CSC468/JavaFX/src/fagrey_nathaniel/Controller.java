package fagrey_nathaniel;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;

public class Controller {

    private ApartmentComplex apartmentComplex;
    private ApartmentComplexView apartmentComplexView;
    private ToggleGroup toggleGroup;

    Controller( ApartmentComplex a, ApartmentComplexView v ){
        this.apartmentComplex = a;
        this.apartmentComplexView = v;
    }

    public void setToggleGroup(ToggleGroup tg ){
        this.toggleGroup = tg;
    }

    class increaseRentEvent implements EventHandler<ActionEvent>{
        public TextField increaseRentTextField;

        increaseRentEvent(TextField tf) {
            this.increaseRentTextField = tf;
        }

        @Override
        public void handle(ActionEvent event){
            try {
                int newRent = Integer.parseInt(this.increaseRentTextField.getText());
                apartmentComplex.increaseRent(newRent);
            }

            catch(Exception e){
                System.out.println(e);
            };
        }
    }

    class newMonthEvent implements EventHandler<ActionEvent>{
        @Override
        public void handle(ActionEvent event){
            apartmentComplex.newMonth();
        }
    }

    class BuildComplex implements EventHandler<ActionEvent>{
        private int col;

        BuildComplex( int col ){

            this.col = col;
        }
        @Override
        public void handle( ActionEvent event){

            apartmentComplexView.resize(this.col);
            apartmentComplex.resize();
        }
    }

    class BuildFloor implements EventHandler<ActionEvent>{
        private int index;

        BuildFloor(int index){
            this.index = index;
        }

        @Override
        public void handle(ActionEvent event){
            Floor floor = new Floor();
            if (apartmentComplex.addFloor(floor, index)){
                ApartmentView view = new ApartmentView(floor);
                view.addEventFilter(ActionEvent.ACTION, new UpgradeFloor(floor));
                apartmentComplexView.addView(view, this.index);
            }
        }
    }

    class UpgradeFloor implements EventHandler<ActionEvent>{
        private Floor floor;

        UpgradeFloor(Floor f ){
            this.floor = f;
        }

        @Override
        public void handle( ActionEvent event){
            RadioButton selectedRadioButton = (RadioButton)toggleGroup.getSelectedToggle();

            if(selectedRadioButton.getText() == "Basic"){
                floor.upgrade(1);
            }

            else if( selectedRadioButton.getText() == "Penthouse"){
                floor.upgrade(2);
            }

            else{
                floor.upgrade(0);
            }

            apartmentComplex.remodelFloor(floor);
            apartmentComplex.notifyObservers();
        }
    }
}
