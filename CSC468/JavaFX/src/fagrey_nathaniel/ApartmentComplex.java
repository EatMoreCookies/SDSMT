package fagrey_nathaniel;

import java.util.ArrayList;

public class ApartmentComplex{

    private ArrayList<Observer> observers = new ArrayList<>();
    private ArrayList<Floor> floors = new ArrayList<Floor>();

    private int currMonth = 0;
    private int funds = 100000;
    private int buildFloor = 20000;
    private int[] availableRow = {6,6,6,6,6,6};

    public void increaseRent(int newAmount){
        for( Floor f : floors ) {
            f.increaseRent(newAmount);
        }

        notifyObservers();
    }

    public void remodelFloor(Floor floor){
        this.funds -= floor.getRemodel();
    }

    private void resetAvailableRows(){
        for( int i = 0; i < 6; ++i){
            availableRow[i] = 6;
        }
    }

    public int[] getAvailableRows(){
        return availableRow;
    }

    public int getRentToCollect(){
        int sum = 0;

        for( Floor f : floors ) {
            sum += f.getRent();
        }

        return sum;
    }

    public int getMonth() {
        return this.currMonth;
    }

    public void newMonth(){
        currMonth++;

        for( Floor f : floors ) {
            f.newMonth();
        }

        this.funds = this.funds + getRentToCollect() - getMaintenence();

        notifyObservers();
    }

    // GRADING: TRIGGER_CUSTOM.
    public void notifyObservers(){
        for( Observer o: observers){
            o.update();
        }
    }

    public void attachObserver(Observer observer){
        this.observers.add(observer);
    }

    public Boolean addFloor( Floor floor, int index){
        if( availableRow[index] > 0){
            availableRow[index] -= 1;

            this.floors.add(floor);
            this.funds = this.funds - this.buildFloor - floor.getRemodel();
            notifyObservers();

            return true;
        }

        return false;
    }

    public int getFunds(){
        return this.funds;
    }

    public int getMaintenence() {
        int sum = 0;

        for( Floor f : floors ) {
            sum += f.getMaintenence();
        }

        return sum;
    }

    public int getFilled(){
        int sum = 0;
        for( Floor f : floors ) {
           if(f.filled())
               sum += 1;
        }
        return sum;
    }

    public void resize() {
        resetAvailableRows();
        floors.clear();
        notifyObservers();
    }
}
