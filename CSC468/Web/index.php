<?php
   session_start();
?>
<html xmlns="http://www.w3.org/1999/html">
  <header>
    <link rel="stylesheet" href="css/index.css" />
    <script type="text/javascript" src="js/UndoRedo.js"></script>
      <script type="text/javascript" src="js/FileManage.js"></script>
      <div class="header">
          <h1>Web Stick-man</h1>
      </div>
      <div>
          <nav class="nav">
        <a href="index.php">Home</a>
        <a href="FileManagement.php">Manage Files</a>
        <a href="HelpPage.html">Help</a>
      </nav>
    </div>
  </header>
  <body>
    <div class="saveButton">
        <img class="rotate" src="images/arrow.png"/>
        <button class="buttonStd" id="undo">Undo</button>
        <button class="buttonStd" id="redo">Redo</button>
        <button class="buttonStd" id="save" onclick="Save()">Save</button>
    </div>

    <?php
    if (isset($_COOKIE['head']))
        $_SESSION['head'] = $_COOKIE['head'];

    if (isset($_COOKIE['larm']))
        $_SESSION['larm'] = $_COOKIE['larm'];

    if (isset($_COOKIE['body']))
        $_SESSION['body'] = $_COOKIE['body'];

    if (isset($_COOKIE['rarm']))
        $_SESSION['rarm'] = $_COOKIE['rarm'];

    if (isset($_COOKIE['legs']))
        $_SESSION['legs'] = $_COOKIE['legs'];
    ?>
    <div class="displayArea">
        <table id="table">
            <tr>
                <td><button class="buttonStd" id="PirateHead">Pirate Hat</button></td>
                <td><button class="buttonStd" id="DefaultHead">Head</button></td>
                <td><button class="buttonStd" id="LepHead">Green Hat</button></td>
            </tr>

            <tr>
                <td><button class="buttonStd" id="DefaultBody">Body</button></td>
                <td><button class="buttonStd" id="PirateBody">Buckle</button></td>
                <td><button class="buttonStd" id="LepBody">Shirt</button></td>
            </tr>

            <tr>
                <td><button class="buttonStd" id="DefaultLArm">Left Arm</button></td>
                <td><button class="buttonStd" id="LepLArm">Left Arm Pot</button></td>
                <td><button class="buttonStd" id="PirateLArm">Left Arm Hook</button></td>
            </tr>

            <tr>
                <td><button class="buttonStd" id="PirateRArm">Right Arm Sword</button></td>
                <td><button class="buttonStd" id="DefaultRArm">Right Arm</button></td>
                <td><button class="buttonStd" id="LepRArm">Right Arm Shamrock</button></td>
            </tr>

            <tr>
                <td><button class="buttonStd" id="LepLegs">Leprechaun Legs</button></td>
                <td><button class="buttonStd" id="DefaultLegs">Legs</button></td>
                <td><button class="buttonStd" id="PirateLegs">Pirate Legs</button></td>
            </tr>

            <tr>
                <td><button class="buttonStd" id="Default">Default</button></td>
                <td><button class="buttonStd" id="Pirate">Pirate</button></td>
                <td><button class="buttonStd" id="Leprechaun">Leprechaun</button></td>
            </tr>

        </table>
        <div class = "stickman">
            <div>
        <?php
            if($_SESSION['head'] == 0)
                echo'<img
                     id="displayHead"
                     src="images/stickman-head_Default.png"
                     alt="Display Head>"';

            else if($_SESSION['head'] == 1)
                echo'<img
                     id="displayHead"
                     src="images/stickman-head_Pirate-hat.png"
                     alt="Display Head>"';

            else if( $_SESSION['head'] == 2)
                echo'<img
                     id="displayHead"
                     src="images/stickman-head_Leprechaun-beard.png"
                     alt="Display Head>"';
        ?>
    </div>
      <div class="midsection">
          <?php
            if( $_SESSION['larm'] == 0)
                echo' <img
                      id="displayLArm"
                      src="images/stickman-lArm_Default.png"
                      alt="Display Left Arm"/
                      >';
            else if($_SESSION['larm'] == 1)
                echo '<img
                      id="displayLArm"
                      src="images/stickman-lArm_Pirate-hook.png"
                      alt="Display Left Arm"/
                      >';
          else if($_SESSION['larm'] == 2)
                  echo'<img
                      id="displayLArm"
                      src="images/stickman-lArm_Leprechaun-gold.png"
                      alt="Display Left Arm"/
                      >';

          if($_SESSION['body'] == 0)
                  echo'<img
                      id="displayBody"
                      src="images/stickman-body_Default.png"
                      alt="Display Body"/>';

          else if($_SESSION['body'] == 1)
              echo'<img
                      id="displayBody"
                      src="images/stickman-body_Pirate-belt.png"
                      alt="Display Body"/>';

          else if($_SESSION['body'] == 2)
               echo'<img
                      id="displayBody"
                      src="images/stickman-body_Leprechaun-greenShirt.png"
                      alt="Display Body"/
                      >';

          if( $_SESSION['rarm'] == 0)
              echo '<img
                      id="displayRArm"
                      src="images/stickman-rArm_Default.png"
                      alt="Default Right Arm"/
                      >';

          else if( $_SESSION['rarm'] == 1)
              echo '<img
                      id="displayRArm"
                      src="images/stickman-rArm_Pirate-sword.png"
                      alt="Default Right Arm"/
                      >';

          else if( $_SESSION['rarm'] == 2)
              echo '<img
                      id="displayRArm"
                      src="images/stickman-rArm_Leprechaun-shamrock.png"
                      alt="Default Right Arm"
                    />';
          ?>
      </div>
      <div>
          <?php
          if( $_SESSION['legs'] == 0)
              echo ' <img
                      id="displayLegs"
                      src="images/stickman-legs_Default.png"
                      alt="Display Legs"/>';

          else if( $_SESSION['legs'] == 1)
              echo ' <img
                      id="displayLegs"
                      src="images/stickman-legs_Pirate-boots.png"
                      alt="Display Legs"/>';

          else if( $_SESSION['legs'] == 2)
              echo ' <img
                      id="displayLegs"
                      src="images/stickman-legs_Leprechaun-shoe.png"
                      alt="Display Legs"/>';
          ?>

          <?php
          if( isset($_GET['save'])) {
              require_once "Save.php";
              save($_SESSION['head'], $_SESSION['larm'], $_SESSION['body'],
                  $_SESSION['rarm'], $_SESSION['legs']);
          }
          ?>
      </div>
    </div>
    </div>
  </body>
</html>
