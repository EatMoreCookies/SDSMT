package fagrey_nathaniel;

public class LightBulb extends Empty {
    LightBulb() {
        super.character = '✦';
        super.type = "LightBulb";
    }

    @Override
    public void visit( Visitor v ) {
        v.accept(this);
    }
}
