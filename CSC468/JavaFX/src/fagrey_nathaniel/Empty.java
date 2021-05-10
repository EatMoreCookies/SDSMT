package fagrey_nathaniel;

public class Empty extends Apartment{
    Empty(){
        this.name = "Empty";
        this.rent = 0;
        this.maintenence = 200;
        this.remodel = 0;
    }

    @Override
    public void increaseRent(int newAmount ){
        this.rent = 0;
    }

}
