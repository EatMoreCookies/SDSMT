package fagrey_nathaniel;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

public class Floor{

    // GRADING: SUBJECT
    private final PropertyChangeSupport pcs = new PropertyChangeSupport(this);
    Apartment apartment;

    private ArrayList<Observer> observers = new ArrayList<>();

    Floor(){
        apartment = new Empty();
    }

    public void increaseRent(int newAmount){
        apartment.increaseRent(newAmount);
        // GRADING: TRIGGER
        firePropertyChange();
    }

    public int getMaintenence(){
        return apartment.getMaintenence();
    }

    public int getRent(){
        return apartment.getRent();
    }

    public void newMonth(){
        apartment.newMonth();
        // GRADING: TRIGGER
        firePropertyChange();
    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
        this.pcs.addPropertyChangeListener(listener);
    }

    public void firePropertyChange(){
        this.pcs.firePropertyChange("Update", "old", "new");
    }

    public String getName(){
        return apartment.getName();
    }

    public int getDuration() {
        return apartment.getDuration();
    }

    public int getRemodel() {
        return apartment.getRemodel();
    }

    public void upgrade(int indicator){
        if( indicator == 1 ){
            apartment = new Basic();
        }

        else if( indicator == 2 ){
            apartment = new Penthouse();
        }

        else
            apartment = new Empty();

        // GRADING: TRIGGER
        firePropertyChange();
    }

    public Boolean filled(){
        if( apartment instanceof Basic || apartment instanceof Penthouse)
            return true;
        return false;
    }
}

