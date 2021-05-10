package edu.sdsmt.fagrey_nathaniel.wumbus;

import java.util.Random;

public class Game {

    public enum Moves {UP, RIGHT, DOWN, LEFT};

    private final int SIZE = 4;
    private Elements[][] game = new Elements[SIZE][SIZE];
    private Random rand = new Random();
    private int Xpos, Ypos, exitX, exitY;
    private int score = 0;
    private int arrows = 0;
    private int arrowsLeft;
    private boolean bow = false;
    private boolean foundExit;
    private boolean wumpusDead;
    private boolean[] visited = new boolean[SIZE * SIZE];
    
    public enum Elements { EMPTY, BOW_QUIVER, ARROW, BAT, PIT, WUMBUS, EXIT}

    public void newGame(){
        for( int i = 0; i < SIZE; ++i){
            for( int j = 0; j < SIZE; ++j){
                game[i][j] = Elements.EMPTY;
                visited[j * SIZE + i] = false;
            }
        }

        Xpos = 0;
        Ypos = 0;
        score = 0;
        arrows = 0;
        arrowsLeft = 2;
        bow = false;
        foundExit = false;
        wumpusDead = false;

        addElements(Elements.PIT, 1 );
        addElements(Elements.WUMBUS, 1);
        addElements(Elements.ARROW, 2);
        addElements(Elements.BOW_QUIVER, 1);
        addElements(Elements.BAT, 1);
        addElements(Elements.EXIT, 1);

        visited[0] = true;
    }

    public int getArrowsLeft(){
        return arrowsLeft;
    }

    private void addElements(Elements elements, int num){
        int randRow, randCol;

        for( int i = 0; i < num; ++i){
            randRow = rand.nextInt(4);
            randCol = rand.nextInt(4);

            while( game[randRow][randCol] != Elements.EMPTY || randRow == 0 && randCol == 0){
                randRow = rand.nextInt(4);
                randCol = rand.nextInt(4);
            }

            game[randRow][randCol] = elements;
        }
    }

    public Elements getElement(){
        return game[Ypos][Xpos];
    }

    public void removeArrow(int num){
        arrows -= num;
        if( arrows < 0)
            arrows = 0;
    }

    public void pickUpBow(){
        game[Ypos][Xpos] = Elements.EMPTY;
        bow = true;
    }

    public boolean WumpusDead(){
        return wumpusDead;
    }

    public void setFoundExit(boolean val){
        exitX = Xpos;
        exitY = Ypos;
        foundExit = val;
    }

    public boolean[] getVisited(){
        return visited;
    }

    public boolean haveVisited(int x, int y){
        return visited[x * SIZE + y];
    }

    public void move(Moves moves){
        score += 1;

        if( moves == Moves.DOWN){
            Ypos = (Ypos + 1 ) % SIZE;
        }

        else if( moves == Moves.RIGHT){
            Xpos = (Xpos + 1) % SIZE;
        }

        else if( moves == Moves.UP){
            Ypos = (subtractRange(Ypos) - 1) % SIZE;
        }

        else if( moves == Moves.LEFT){
            Xpos = (subtractRange(Xpos) - 1) % SIZE;
        }

        visited[Xpos * SIZE + Ypos] = true;
    }

    public void pickUpArrow(int num){
        game[Ypos][Xpos] = Elements.EMPTY;
        arrows += num;
        arrowsLeft -= num;
    }

    private int subtractRange(int pos){
        if( pos - 1 < 0 ){
            return SIZE;
        }

        return pos;
    }

    public void shoot(Game.Moves shot){
        int arrX = Xpos;
        int arrY = Ypos;

        for( int i = 0; i < 2; ++i ) {
            if (shot == Moves.DOWN) {
                arrY = (arrY + 1) % SIZE;
            } else if (shot == Moves.RIGHT) {
                arrX = (arrX + 1) % SIZE;
            } else if (shot == Moves.UP) {
                arrY = (subtractRange(arrY) - 1) % SIZE;
            } else if (shot == Moves.LEFT) {
                arrX = (subtractRange(arrX) - 1) % SIZE;
            }

            if( game[arrY][arrX] == Elements.WUMBUS ){
                wumpusDead = true;
                game[arrY][arrX] = Elements.EMPTY;
            }
        }

        removeArrow(1);
    }

    public boolean foundExit() {
        return foundExit;
    }

    public int[] getExitPos(){
        return new int[]{exitX, exitY};
    }

    public int[] getCharacterPos(){
        return new int[]{Xpos, Ypos};
    }

    public String getCheat(){
        String retString = "";

        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j ){
                if( game[i][j] != Elements.EMPTY){
                    int temp1 = j + 1;
                    int temp2 = i + 1;
                    retString += "[" + temp1 + "," + temp2 + "]: " + game[i][j].name().toLowerCase() + "\n";
                }
            }
        }

        return retString;
    }

    public int getScore(){
        return score;
    }

    public int getArrows(){
        return arrows;
    }

    public String getBow(){
        if(bow)
            return "Yes";
        return "No";
    }

    public int[] saveGameBoard() {
        int[] savedData = new int[32];
        int index = 0;

        for(int i = 0; i < SIZE; ++i)
        {
            for( int j = 0; j < SIZE; ++j )
            {
                savedData[index] = j * SIZE + i;
                savedData[index + 1] = game[i][j].ordinal();
                index += 2;
            }
        }

        return savedData;
    }

    public int[] savedPositions(){
        int[] savedData = new int[4];

        savedData[0] = Xpos;
        savedData[1] = Ypos;
        savedData[2] = exitX;
        savedData[3] = exitY;

        return savedData;
    }

    public void sendPlayerToRandomPosition(){
        Xpos = rand.nextInt(4);
        Ypos = rand.nextInt(4);

        while( game[Ypos][Xpos] != Elements.EMPTY){
            Xpos = rand.nextInt(4);
            Ypos = rand.nextInt(4);
        }

        visited[Xpos * SIZE + Ypos] = true;
    }

    public void sendBowToRandomPosition(){
        bow = false;
        int randRow = rand.nextInt(4);
        int randCol = rand.nextInt(4);

        while( game[randRow][randCol] != Elements.EMPTY || randCol == Xpos && randRow == Ypos){
            randRow = rand.nextInt(4);
            randCol = rand.nextInt(4);
        }

        game[randRow][randCol] = Elements.BOW_QUIVER;

        for( int i = 0; i < arrows; ++i ){
            randRow = rand.nextInt(4);
            randCol = rand.nextInt(4);

            while( game[randRow][randCol] != Elements.EMPTY || randCol == Xpos && randRow == Ypos){
                randRow = rand.nextInt(4);
                randCol = rand.nextInt(4);
            }

            game[randRow][randCol] = Elements.ARROW;
            arrowsLeft++;
            arrows--;
        }
    }

    public void restoreGame(int[] savedGame, int score, int arrows, String bow, int[] positions,
                            Boolean foundExit, boolean[] visited, boolean wumpusDead){

        arrowsLeft = 0;

        for(int i = 0; i < savedGame.length - 1; i+=2)
        {
            int x = (int)Math.floor((float)savedGame[i] / SIZE);
            int y = savedGame[i] % SIZE;
            game[y][x] = Game.Elements.values()[savedGame[i + 1]];

            if(game[y][x] == Elements.ARROW)
                arrowsLeft++;
        }

        this.bow = bow.equals("Yes");

        this.arrows = arrows;
        this.score = score;

        this.Xpos = positions[0];
        this.Ypos = positions[1];

        this.foundExit = foundExit;

        if( this.foundExit ){
            this.exitX = positions[2];
            this.exitY = positions[3];
        }

        this.visited = visited;
        this.wumpusDead = wumpusDead;
    }
}
