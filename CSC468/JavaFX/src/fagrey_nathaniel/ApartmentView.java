package fagrey_nathaniel;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class ApartmentView extends Button implements PropertyChangeListener {

    Floor floor;

    ApartmentView(Floor f){
        this.floor = f;
        this.floor.addPropertyChangeListener(this);
        setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        setText("\nEmpty" + "\n");
    }

    // GRADING: OBSERVER
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        String newName = floor.getName();
        Image image;

        if(!newName.equals("Empty")){
            this.setText(newName + "\n" + "Duration: " + floor.getDuration() + "\n" + "Rent: " + floor.getRent());

            if( newName.equals("Basic")){
                image = new Image(getClass().getResourceAsStream("house.jpg"));
            }

            else{
                image = new Image(getClass().getResourceAsStream("castle.png"));
            }

            setGraphic(setImage(image));
        }

        else{
            setGraphic(null);
            this.setText("\nEmpty" + "\n");
        }
    }

    private ImageView setImage(Image image){
        ImageView view = new ImageView(image);
        view.setX(10);
        view.setY(10);
        view.setFitHeight(20);
        view.setFitWidth(20);
        view.setPreserveRatio(false);
        return view;
    }
}
