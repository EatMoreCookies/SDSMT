package edu.sdsmt.fagrey_nathaniel.wumbus;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

/*
1a and 1b are the same tier. They are noted only for category clarity.

Tierless: State machine*	24
X_ State machine framework is present
X_ Framework controls bow, arrows, pickup
X_ Framework controls exit or not
X_ End conditions


X_ Tierless: rotation (-4 each item missed) *	8


1a: Layout *	24
X_ Arrow buttons
X_ Player select exit and opens
X_ Majority of area the game area
X_ Aspect kept, and resize to new devices works
X_ Different layout for portrait and landscape


1b: Game logic	30
X_ Bat event (loss of bow, arrows, and new position)
X_ Rooms start hidden, and then revealed
X_ Shooting the arrow components (Wumpus and loss)
X_ Player select works *


2 Tier: End game	14
X_ End dialog exists
X_ Both end dialogs open at right time
X_ End activity score/loss reason correct (50% each)


3: extensions 	30
Extension 1: 1b. 10pt: add another 1+ player option that uses another primitive (e.g. triangle) player.
                       In the player FAB menu, you can also choose a triangle for the player shape.
Extension 2: 1e. 20pt: grant the ability for the user to choose among 2+ different background options.
                       There is another FAB menu, with a hollow circle for the user to select different
                       colors for the rooms.
*/

public class MainActivity extends AppCompatActivity {

    private Game game;
    private StateMachine machine;

    private static final String GAME = "Game";
    private static final String SCORE = "Score";
    private static final String BOW = "Bow";
    private static final String ARROWS = "Arrows";
    private static final String POSITIONS = "Positions";
    private static final String FOUND_EXIT = "FoundExit";
    private static final String STATE = "State";
    private static final String VISITED = "Visited";
    private static final String WUMPUS_DEAD = "WumpusDead";
    private static final String GAME_RESULT = "GameResult";
    private static final String CHEAT_TEXT = "CheatText";
    private static final String PLAYER_SHAPE = "PlayerColor";
    private static final String ROOM_COLOR = "RoomColor";
    private boolean isFABOpen = false;
    private boolean isFABColorOpen = false;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        game = new Game();
        machine = new StateMachine(game, this);
    }

    @Override
    protected void onStart(){
        super.onStart();
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.setGame(game);
        machine.reset();
        update();
    }

    @Override
    public void onSaveInstanceState(@NonNull Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putInt(SCORE, game.getScore());
        savedInstanceState.putInt(ARROWS, game.getArrows());
        savedInstanceState.putString(BOW, game.getBow());
        savedInstanceState.putIntArray(GAME, game.saveGameBoard());
        savedInstanceState.putIntArray(POSITIONS, game.savedPositions());
        savedInstanceState.putBoolean(FOUND_EXIT, game.foundExit());
        savedInstanceState.putInt(STATE, machine.saveState().ordinal());
        savedInstanceState.putBooleanArray(VISITED, game.getVisited());
        savedInstanceState.putBoolean(WUMPUS_DEAD, game.WumpusDead());
        savedInstanceState.putInt(GAME_RESULT, machine.getGameResult());

        TextView tv = findViewById(R.id.CHEAT_TEXT);
        savedInstanceState.putString(CHEAT_TEXT, (String)tv.getText());

        MyGameView2 gv = findViewById(R.id.myGameView22);
        savedInstanceState.putInt(PLAYER_SHAPE, gv.getPlayerShape());
        savedInstanceState.putInt(ROOM_COLOR, gv.getRoomColor());
    }

    @Override
    public void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);

        game.restoreGame(savedInstanceState.getIntArray(GAME), savedInstanceState.getInt(SCORE),
                savedInstanceState.getInt(ARROWS), savedInstanceState.getString(BOW),
                savedInstanceState.getIntArray(POSITIONS), savedInstanceState.getBoolean(FOUND_EXIT),
                savedInstanceState.getBooleanArray(VISITED), savedInstanceState.getBoolean(WUMPUS_DEAD));

        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.setGame(game);
        tvg.SetPlayerShape(savedInstanceState.getInt(PLAYER_SHAPE));
        tvg.ChangeRoomColor(savedInstanceState.getInt(ROOM_COLOR));

        machine.restoreState(StateMachine.States.values()[savedInstanceState.getInt(STATE)]);
        machine.setGamResult(savedInstanceState.getInt(GAME_RESULT));

        TextView tv = findViewById(R.id.CHEAT_TEXT);
        tv.setText(savedInstanceState.getString(CHEAT_TEXT));
        update();
    }

    public void MoveUP(android.view.View view) {
        game.move(Game.Moves.UP);
        update();
    }

    public void MoveDOWN(android.view.View view) {
        game.move(Game.Moves.DOWN);
        update();
    }

    public void MoveRIGHT(android.view.View view) {
        game.move(Game.Moves.RIGHT);
        update();
    }

    public void MoveLEFT(android.view.View view) {
        game.move(Game.Moves.LEFT);
        update();
    }

    public void Cheat(android.view.View view) {
        TextView tv = findViewById(R.id.CHEAT_TEXT);
        tv.setText(game.getCheat());
    }

    public void Reset(android.view.View view) {
        TextView tv = findViewById(R.id.CHEAT_TEXT);
        tv.setText(null);
        machine.reset();
        update();
    }

    public void ShootRight(android.view.View view){
        game.shoot(Game.Moves.RIGHT);
        update();
    }

    public void ShootLeft(android.view.View view){
        game.shoot(Game.Moves.LEFT);
        update();
    }

    public void ShootUp(android.view.View view){
        game.shoot(Game.Moves.UP);
        update();
    }

    public void ShootDown(android.view.View view){
        game.shoot(Game.Moves.DOWN);
        update();
    }

    public void FloatingButtonsDisplay(android.view.View view){
        if( !isFABOpen){
            showFABMenu();
        }

        else
            closeFABMenu();
    }

    public void FABColor(android.view.View view)
    {
        if( !isFABColorOpen){
            showFABColorMenu();
        }

        else
            closeFABColorMenu();
    }

    private void showFABColorMenu(){
        isFABColorOpen = true;
        FloatingActionButton button = findViewById(R.id.color_blue);
        button.animate().translationY(DpToPixel(70));
        button = findViewById(R.id.color_red);
        button.animate().translationY(DpToPixel(140));
        button = findViewById(R.id.color_gray);
        button.animate().translationY(DpToPixel(210));
    }

    private void closeFABColorMenu(){
        isFABColorOpen = false;
        FloatingActionButton button = findViewById(R.id.color_blue);
        button.animate().translationY(DpToPixel(0));
        button = findViewById(R.id.color_red);
        button.animate().translationY(DpToPixel(0));
        button = findViewById(R.id.color_gray);
        button.animate().translationY(DpToPixel(0));
    }

    private void closeFABMenu(){
        isFABOpen = false;
        FloatingActionButton button = findViewById(R.id.circle);
        button.animate().translationY(0);
        button = findViewById(R.id.square);
        button.animate().translationY(0);
        button = findViewById(R.id.triangle);
        button.animate().translationY(DpToPixel(0));
    }

    private void showFABMenu(){
        isFABOpen = true;
        FloatingActionButton button = findViewById(R.id.circle);
        button.animate().translationY(DpToPixel(70));
        button = findViewById(R.id.square);
        button.animate().translationY(DpToPixel(140));
        button = findViewById(R.id.triangle);
        button.animate().translationY(DpToPixel(210));
    }

    private float DpToPixel(float dp){
        float pxPerDp = (float)getResources().getDisplayMetrics().densityDpi;
        pxPerDp = pxPerDp / DisplayMetrics.DENSITY_DEFAULT;

        return dp * pxPerDp;
    }

    public void ChangePlayerSquare(android.view.View view) {
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.SetPlayerShape(1);
    }

    public void ChangePlayerTriangle(android.view.View view) {
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.SetPlayerShape(2);
    }

    public void ChangePlayerCircle(android.view.View view){
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.SetPlayerShape(0);
    }

    public void ChangeBackgroundBlue(android.view.View view)
    {
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.ChangeRoomColor(Color.BLUE);
        tvg.update();
    }

    public void ChangeBackgroundRed(android.view.View view)
    {
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.ChangeRoomColor(Color.RED);
        tvg.update();
    }

    public void ChangeBackgroundGreen(android.view.View view)
    {
        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.ChangeRoomColor(Color.GREEN);
        tvg.update();
    }


    // Toy version of observer pattern
    private void update(){
        machine.DoTask();

        TextView tva = findViewById(R.id.ARROWS);
        String newString = getString(R.string.ARROWS, game.getArrows());
        tva.setText(newString);

        tva = findViewById(R.id.SCORE);
        newString = getString(R.string.SCORE, game.getScore());
        tva.setText(newString);

        tva = findViewById(R.id.BOW);
        newString = getString(R.string.BOW, game.getBow());
        tva.setText(newString);

        MyGameView2 tvg = findViewById(R.id.myGameView22);
        tvg.update();
    }
}