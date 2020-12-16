package fagrey_nathaniel;

interface Visitor {
    public void accept( Empty e );
    public void accept( GreenSpace g );
    public void accept( LightBulb b );
    public void accept( Panel p );
}
