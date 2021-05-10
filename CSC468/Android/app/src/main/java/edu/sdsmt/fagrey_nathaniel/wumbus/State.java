package edu.sdsmt.fagrey_nathaniel.wumbus;

import android.widget.Button;
import android.widget.TextView;

public class State {
     StateMachine stateMachine = null;
     Game game = null;
     MainActivity mainActivity = null;
     void StartTask(StateMachine stateMachine){}
     void EndTask(){}
     void MaintenanceTask(Game.Elements element){}
     void UpdateShootingButtons(boolean val){
          Button button = this.mainActivity.findViewById(R.id.shoot_up);
          button.setEnabled(val);
          button = this.mainActivity.findViewById(R.id.shoot_down);
          button.setEnabled(val);
          button = this.mainActivity.findViewById(R.id.shoot_left);
          button.setEnabled(val);
          button = this.mainActivity.findViewById(R.id.shoot_right);
          button.setEnabled(val);
     }

     void displayMessage(int id){
          TextView tv = this.stateMachine.getMainActivity().findViewById(R.id.CHEAT_TEXT);
          tv.setText(id);
     }

     void CheckWinLose(Game.Elements element){
           if( element == Game.Elements.WUMBUS )
               stateMachine.setGamResult(2);

           // GRADING: EXIT
          else if( element == Game.Elements.EXIT){
               game.setFoundExit(true);

               if( game.WumpusDead())
                    stateMachine.setGamResult(0);
          }

          else if( element == Game.Elements.PIT)
               stateMachine.setGamResult(1);
     }
}
