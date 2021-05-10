package edu.sdsmt.fagrey_nathaniel.wumbus;

public class Arrow extends State {
    private boolean bat = false;

    @Override
    void StartTask(StateMachine stateMachine) {
        this.stateMachine = stateMachine;
        this.game = stateMachine.getGame();
        this.mainActivity = stateMachine.getMainActivity();

        // GRADING: ENABLE
        UpdateShootingButtons(true);
    }

    @Override
    void EndTask() {
        if( bat ){
            game.sendPlayerToRandomPosition();
            game.sendBowToRandomPosition();
            displayMessage(R.string.FOUND_BAT);
        }
    }

    @Override
    void MaintenanceTask(Game.Elements element) {
        CheckWinLose(element);

        if (element == Game.Elements.ARROW){
            game.pickUpArrow(1);
            displayMessage(R.string.FOUND_ARROW);
        }

        else if( element == Game.Elements.BAT ){
            bat = true;
            stateMachine.setState(new NoBow());
        }

        // GRADING: EMPTY
        else if( game.getArrows() <= 0 ){
            stateMachine.setState(new NoArrow());
        }
    }
}
