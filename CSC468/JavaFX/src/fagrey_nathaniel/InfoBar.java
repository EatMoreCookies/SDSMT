package fagrey_nathaniel;

import javafx.scene.control.Label;

public class InfoBar implements Observer {
    private Label rentToCollect;
    private Label maintenence;
    private Label filled;
    private Label month;
    private Label funds;
    private ApartmentComplex apartmentComplex;

    InfoBar(ApartmentComplex apartmentComplex, Label maintenence, Label filled,
            Label funds, Label rentToCollect, Label month){
        this.maintenence = maintenence;
        this.filled = filled;
        this.month = month;
        this.funds = funds;
        this.rentToCollect = rentToCollect;
        this.apartmentComplex = apartmentComplex;

        // GRADING: SUBJECT_CUSTOM
        this.apartmentComplex.attachObserver(this);
        update();
    }

    // GRADING: OBSERVE_CUSTOM
    public void update(){
        this.month.setText("Month: " + this.apartmentComplex.getMonth());
        this.rentToCollect.setText("Rent to Collect: " + this.apartmentComplex.getRentToCollect());
        this.maintenence.setText("Maintenance: " + this.apartmentComplex.getMaintenence());
        this.funds.setText("Funds: " + this.apartmentComplex.getFunds());
        this.filled.setText("Filled: " + this.apartmentComplex.getFilled());
    }
}
