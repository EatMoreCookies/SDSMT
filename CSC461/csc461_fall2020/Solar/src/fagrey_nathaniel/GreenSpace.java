package fagrey_nathaniel;

public class GreenSpace extends Empty {

    GreenSpace() {
        super.character = '❦';
        super.type = "GreenSpace";
    }

    @Override
    public void visit( Visitor v )
    {
        v.accept(this);
    }
}
