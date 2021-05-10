package edu.sdsmt.fagrey_nathaniel.wumbus;

public class NoBow extends State{
    @Override
    public void StartTask(StateMachine stateMachine){
        this.stateMachine = stateMachine;
        this.game = stateMachine.getGame();
        this.mainActivity = stateMachine.getMainActivity();
        this.game.removeArrow(game.getArrows());
        UpdateShootingButtons(false);
    }

    @Override
    public void EndTask() {

    }

    @Override
    public void MaintenanceTask(Game.Elements element){
        CheckWinLose(element);

        if( element == Game.Elements.BOW_QUIVER){
            game.pickUpBow();
            displayMessage(R.string.FOUND_BOW);
            // GRADING: BOW
            stateMachine.setState(new NoArrow());
        }
    }
}
