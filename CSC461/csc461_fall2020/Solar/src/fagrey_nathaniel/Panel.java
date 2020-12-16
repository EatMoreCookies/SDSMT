package fagrey_nathaniel;

public class Panel extends Empty {
    Panel() {
        super.character = '⊞';
        super.type = "Panel";
    }

    @Override
    public void visit( Visitor v ) {
        v.accept(this);
    }
}
