package fagrey_nathaniel;

public class Color implements Visitor {
    private ColorText.Color color;
    private String type = "";
    private boolean first = true;

    public void accept( Empty e ) {
        if( e.getType() == type)
            e.setColor(color);
    }

    public void accept( GreenSpace g ) {
        if( g.getType() == type)
            g.setColor(color);
    }

    public void accept( LightBulb b ) {
        if( b.getType() == type)
            b.setColor( color );
    }

    public void accept( Panel p ) {
        if( p.getType() == type)
            p.setColor( color );
    }

    public void setColor( ColorText.Color color ){
        this.color = color;
    }

    public void setType( String type ){
        this.type = type;
    }
}
