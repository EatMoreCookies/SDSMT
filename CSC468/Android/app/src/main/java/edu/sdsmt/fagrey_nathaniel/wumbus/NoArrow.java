package edu.sdsmt.fagrey_nathaniel.wumbus;

public class NoArrow extends State {
    private boolean bat = false;
    private boolean arrow = false;

    @Override
    public void StartTask(StateMachine stateMachine) {
        this.stateMachine = stateMachine;
        this.game = stateMachine.getGame();
        this.mainActivity = stateMachine.getMainActivity();
        // GRADING: DISABLE
        UpdateShootingButtons(false);

        if( game.getArrowsLeft() == 0 && !game.WumpusDead() )
            stateMachine.setGamResult(3);
    }

    @Override
    public void EndTask() {
        if( bat ){
            game.sendPlayerToRandomPosition();
            game.sendBowToRandomPosition();
            displayMessage(R.string.FOUND_BAT);
        }

        if(arrow)
            displayMessage(R.string.FOUND_ARROW);
    }

    @Override
    public void MaintenanceTask(Game.Elements element) {
        CheckWinLose(element);

        if (element == Game.Elements.ARROW){
            game.pickUpArrow(1);
            arrow = true;
            stateMachine.setState(new Arrow());
        }

        else if( element == Game.Elements.BAT ){
            bat = true;
            // GRADING: BAT
            stateMachine.setState(new NoBow());
        }
    }
}
