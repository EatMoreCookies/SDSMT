package fagrey_nathaniel;

public class Empty {
    protected String type = "Empty";
    private ColorText.Color color = ColorText.Color.BLACK;
    private char character = '⛶';

    Empty( ) { }

    public void visit( Visitor v ) {
        v.accept(this);
    }

    public String printCharacter( ){

        return ColorText.colorString( character, color );
    }

    public String getType(){
        return type;
    }

    public void setColor( ColorText.Color color ){
        this.color = color;
    }
}
