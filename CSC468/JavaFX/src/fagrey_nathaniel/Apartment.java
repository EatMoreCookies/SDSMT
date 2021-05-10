package fagrey_nathaniel;

public abstract class Apartment {
    protected int rent;
    protected int maintenence;
    protected int remodel;
    protected int timeSinceRemodel;
    protected String name;

    public void increaseRent(int newAmount){
        this.rent += newAmount;
    }

    public int getRent(){
        return this.rent;
    }

    public String getName(){
        return this.name;
    }

    public int getDuration(){
        return this.timeSinceRemodel;
    }

    public int getMaintenence(){
        return this.maintenence;
    }

    public int getRemodel(){
        return this.remodel;
    }

    public void newMonth(){
        this.timeSinceRemodel += 1;
    }
}
