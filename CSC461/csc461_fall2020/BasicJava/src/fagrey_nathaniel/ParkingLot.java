package fagrey_nathaniel;

import java.text.DecimalFormat;

public class ParkingLot {
    private int timeSinceLotOpened = 0;
    private int numVehiclesInLot = 0;
    private int IDList = -1;

    private int lastTime = -1;

    protected String name = "test";
    protected int numParkingSpaces;

    private int numClosedMinutes = 0;
    private int lastClosedTime = -1;

    private boolean wasClosed = false;
    private int startCloseTime;

    static final double CLOSED_THRESHOLD = 80;

    ParkingLot() {

    }

    ParkingLot( String name, int numParkingSpaces) {
        this( numParkingSpaces );
        this.name = name;
    }

    ParkingLot( int numParkingSpaces ){

        this.numParkingSpaces = numParkingSpaces;
    }

    private Boolean validTime( int time ){
        if( lastTime - time > 0 )
            return false;

        lastTime = time;

        return true;
    }

    public int markVehicleEntry( int entryTime ) {
        if( !validTime( entryTime ) )
            return -1;

        if( numVehiclesInLot == numParkingSpaces )
            return -1;

        numVehiclesInLot++;

        if (isClosed()) {
            if( !wasClosed ) {
                startCloseTime = entryTime;
                wasClosed = true;
            }
        }

        IDList += 1;

        return IDList;
    }

    public int markVehicleExit( int exitTime, int ID ) {
        boolean update = false;

        if( !validTime( exitTime ) )
            return -1;

        if( isClosed() ){
            update = true;
        }

        numVehiclesInLot--;

        if (!isClosed() && update ) {
            updateClosedMinutes(exitTime);
            wasClosed = false;
        }

        return ID;
    }


    public int getNumVehiclesInLot(){

        return numVehiclesInLot;
    }

    public Boolean isClosed( ){

        return occupiedPercentage() >= (double)(CLOSED_THRESHOLD);
    }

    private double occupiedPercentage( ){
        return ((double)numVehiclesInLot / (double)numParkingSpaces ) * 100;
    }

    public String getName(){

        return name;
    }

    public int getVehiclesInLot() {

        return numVehiclesInLot;
    }

    public int getClosedMinutes(){

        return numClosedMinutes;
    }

    public String toString(){
        String closed;
        DecimalFormat df = new DecimalFormat("###.#");

        if( isClosed() )
            closed = "CLOSED";
        else {
            closed = String.valueOf(df.format(occupiedPercentage()));
            closed += "%";
        }
        return "Status for " + name + " parking lot: " + numVehiclesInLot + " vehicles (" +  closed + ")";
    }

    private void updateClosedMinutes(int lastCloseTime){
       numClosedMinutes += lastCloseTime - startCloseTime;
    }
}
