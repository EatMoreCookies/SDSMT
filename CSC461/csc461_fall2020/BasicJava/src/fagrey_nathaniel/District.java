package fagrey_nathaniel;

import java.util.ArrayList;

public class District {

    int startCloseTime = 0;
    int endCloseTime = 0;
    int totalClosedTime = 0;
    boolean wasClosed = false;

    District() {

    }

    private ArrayList<ParkingLot> parkingLots = new ArrayList<ParkingLot>();

    public int markVehicleEntry( int index, int time){

        int ID = parkingLots.get(index).markVehicleEntry(time);

        if( allParkingLotsClosed() && !wasClosed ){
            startCloseTime = time;
            wasClosed = true;
        }

        return ID;

    }

    public int markVehicleExit( int index, int time, int ID ) {
        boolean update = false;

        if( allParkingLotsClosed() ){
            update = true;
        }
        int myID = parkingLots.get(index).markVehicleExit(time , ID );

        if( !allParkingLotsClosed() && update ){
            endCloseTime = time;
            updateClosedMinutes();
            wasClosed = false;
        }

        return myID;
    }

    private void updateClosedMinutes(){
        totalClosedTime += endCloseTime - startCloseTime;
    }


    public boolean isClosed() {
        boolean retVal = true;

        for( int i = 0; i < parkingLots.size(); i++ ){
            if( !parkingLots.get(i).isClosed() ) {
                retVal= false;
            }
        }

        return retVal;
    }

    public int getClosedMinutes(){
        return totalClosedTime;
    }

    public int add( ParkingLot lot ) {
        parkingLots.add(lot);

        return parkingLots.size() - 1;
    }

    public ParkingLot getLot( int index ) {
        return parkingLots.get(index);
    }

    public int getVehiclesParkedInDistrict() {
        int sum = 0;

        for ( int i = 0; i < parkingLots.size(); i++ ){
                sum += parkingLots.get(i).getVehiclesInLot();
        }
        return sum;
    }

    public String toString() {
        String sum = "District status:";

        for ( int i = 0; i < parkingLots.size(); i++ ){

            sum += "\n" + parkingLots.get(i).toString();
        }
        sum += "\n";

        return sum;
    }

    public double getTotalMoneyCollected(){
        double sum = 0;

        for ( int i = 0; i < parkingLots.size(); i++ ){

            if( parkingLots.get(i) instanceof PayParkingLot ){
                sum += ((PayParkingLot)parkingLots.get(i)).getProfit();
            }
        }

        return sum;
    }

    private boolean allParkingLotsClosed() {
        boolean retVal = true;

        for ( int i = 0; i < parkingLots.size(); i++ ){

            if( !parkingLots.get(i).isClosed() ){
               retVal = false;
            }
        }

        return retVal;
    }
}
