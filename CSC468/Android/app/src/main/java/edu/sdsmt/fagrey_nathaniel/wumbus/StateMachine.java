package edu.sdsmt.fagrey_nathaniel.wumbus;

import androidx.appcompat.app.AlertDialog;

public class StateMachine {
    private State currentState;
    private Game game;
    private int gameResult;
    private MainActivity mainActivity;

    public enum States {NOWBOW, NOARROW, ARROW};

    StateMachine(Game game, MainActivity mainActivity){
        this.currentState = null;
        this.game = game;
        this.gameResult = -1;
        this.mainActivity = mainActivity;
    }

    public void reset(){
        game.newGame();
        setState(new NoBow());
    }

    public void setState(State state){
        if( this.currentState != null)
            this.currentState.EndTask();

        this.currentState = state;
        this.currentState.StartTask(this);
    }

    public void DoTask(){
        this.currentState.MaintenanceTask(game.getElement());
        getEndGameMessage();
    }

    public void setGamResult(int num){
        this.gameResult = num;
    }

    public void clearGameResult() {
        gameResult = -1;
    }

    private void getEndGameMessage(){
        int ret = -1;

        if( gameResult == 0)
            ret = R.string.WON;

        else if( gameResult == 1)
             ret = R.string.GAME_OVER_P;

        else if( gameResult == 2)
            ret = R.string.GAME_OVER_W;

        else if( gameResult == 3)
            ret = R.string.GAME_OVER_WA;

        // GRADING: DIALOG
        if( ret != -1){
            AlertDialog.Builder builder;
            builder = new AlertDialog.Builder(mainActivity);
            builder.setTitle(ret);
            String newString = this.mainActivity.getString(R.string.SCORE, game.getScore());
            builder.setMessage(newString);
            builder.show();
            clearGameResult();
        }
    }

    public Game getGame(){
        return game;
    }

    public MainActivity getMainActivity(){
        return mainActivity;
    }

    public States saveState(){
        if( currentState instanceof NoBow )
            return States.NOWBOW;

        else if( currentState instanceof NoArrow )
            return States.NOARROW;

        else
            return States.ARROW;
    }

    public void restoreState(States state){
        if(state == States.NOWBOW)
            currentState = new NoBow();
        else if( state == States.NOARROW)
            currentState = new NoArrow();
        else if(state == States.ARROW)
            currentState = new Arrow();

        setState(currentState);
    }

    public int getGameResult(){
        return gameResult;
    }
}
