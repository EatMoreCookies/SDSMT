package fagrey_nathaniel;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.*;


public class PayParkingLot extends ParkingLot {

    private double hourlyRate = 2.00;
    private double profit = 0;

    private ArrayList<Integer> carsAndTimes= new ArrayList<Integer>(Collections.nCopies(1000, -1));

    PayParkingLot( String name, int numSpaces, double rate ){
       initialize(name, numSpaces, rate );
    }

    PayParkingLot( int numSpaces, double rate ){
        initialize(super.name, numSpaces, rate);
    }

    PayParkingLot( String name, int numSpaces) {
        initialize(name, numSpaces, hourlyRate);
    }

    private void initialize( String name, int numSpaces, double rate ){
        super.name = name;
        super.numParkingSpaces = numSpaces;
        this.hourlyRate = rate;
    }

    public int markVehicleExit( int exitTime, int ID ){
        if( !validID(ID) )
            return -1;

        int myID = super.markVehicleExit(exitTime, ID);

        if( myID != -1 ) {
            if (exitTime - carsAndTimes.get(myID) > 15) {
                updateProfit(exitTime, carsAndTimes.get(myID));
            }

            carsAndTimes.add(myID, -1);
        }

        return myID;
    }

    public double getProfit() {

        return profit;
    }

    private boolean validID( int ID ){
        if( ID < 0 )
            return false;

        if( carsAndTimes.get(ID) == -1 )
            return false;

        return true;
    }

    private void updateProfit(int exitTime, int entryTime ) {
        profit += hourlyRate * ((double)(exitTime - entryTime - 15.0) / 60.0);
    }

    @Override
    public int markVehicleEntry( int entryTime ) {
        int ID = super.markVehicleEntry(entryTime);

        if( ID != -1 )
            carsAndTimes.add(ID, entryTime);

        return ID;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("##0.00");
        String profitString = String.valueOf(df.format( getProfit() ));

        return super.toString() + " Money collected: $" + profitString;
    }

}
