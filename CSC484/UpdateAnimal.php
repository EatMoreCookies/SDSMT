<html>
    <head>
        <link href="css/style.css" rel="stylesheet">
        <link href="css/updateAnimal.css" rel="stylesheet" /> 
    </head>
    <body>
        <header>
            <div class="main-nav">
                <a class="button" href="index.html">Home</a>
                <a class="button" href="AdoptAnimal.php">Adopt</a>
                <a class="button" href="AddAnimal.php">Add</a>
                <a class="button" href="SearchAnimals.php">Search</a>
                <a class="button selected" href="UpdateAnimal.php">Update</a>
            </div>
            <div class="sub-nav">
                <div class="button <?php echo !isset($_POST["selectedForm"]) || $_POST["selectedForm"] == "0" ? "selected" : "" ?>" id="cat-selector">Cat</div>
                <div class="button <?php echo isset($_POST["selectedForm"]) && $_POST["selectedForm"] == "1" ? "selected" : "" ?>" id="dog-selector">Dog</div>
                <div class="button <?php echo isset($_POST["selectedForm"]) && $_POST["selectedForm"] == "2" ? "selected" : "" ?>" id="rabbit-selector">Rabbit</div>
            </div>
        </header>

    <?php
        $host="services1.cse.sdsmt.edu"; //hostname URL
        $port=3306;						 //default port 3306
        $user="s7416949_f19";				 //DBMS login username
        $password="n8ate123";			 //DBMS login password
        $dbname="db_s7416949_f19";		 //Select DB 

        $animals = array("Cat", "Dog", "Rabbit");

        /* Connect to MySQL */
        $mysqli = new mysqli($host, $user, $password, $dbname, $port);

        if($mysqli->connect_errno) {
            die("Connection failed. Error (".$mysqli->connect_errno."): ".$mysqli->connect_error);
        }
        $catID = 0;
        $dogID = 0;
        $rabbitID = 0;
        
        if(isset($_POST["selectedForm"])) {
            $formSelection = $animals[(int)$_POST["selectedForm"]];
        } else {
            $formSelection = "Cat";
        }

        if(isset($_POST["right"])) {
            if($formSelection == "Cat") {
                $newCatIDQuery = 'SELECT ID FROM Cat WHERE ID > '.$_POST["catID"].' ORDER BY ID LIMIT 1';
                $newCatIDResult = $mysqli->query($newCatIDQuery);
                if($newCatIDResult->num_rows > 0)
                {
                    $catID = $newCatIDResult->fetch_row()[0];
                }
            } else if($formSelection == "Dog") {
                $newDogIDQuery = 'SELECT ID FROM Dog WHERE ID > '.$_POST["dogID"].' ORDER BY ID LIMIT 1';
                $newDogIDResult = $mysqli->query($newDogIDQuery);
                if($newDogIDResult->num_rows > 0)
                {
                    $dogID = $newDogIDResult->fetch_row()[0];
                }
            } else if($formSelection == "Rabbit") {
                $newRabbitIDQuery = 'SELECT ID FROM Rabbit WHERE ID > '.$_POST["rabbitID"].' ORDER BY ID LIMIT 1';
                $newRabbitIDResult = $mysqli->query($newRabbitIDQuery);
                if($newRabbitIDResult->num_rows > 0)
                {
                    $rabbitID = $newRabbitIDResult->fetch_row()[0];
                }            
            }
        }

        if(isset($_POST["left"])) {
            if($formSelection == "Cat") {
                $newCatIDQuery = 'SELECT TOP 1 ID FROM Cat WHERE ID < '.$_POST["catID"].' ORDER BY ID DESC';
                $newCatIDResult = $mysqli->query($newCatIDQuery);
                if($newCatIDResult->num_rows > 0)
                {
                    $catID = $newCatIDResult->fetch_row()[0];
                }
            } else if($formSelection == "Dog") {
                $newDogIDQuery = 'SELECT TOP 1 ID FROM Dog WHERE ID < '.$_POST["dogID"].' ORDER BY ID DESC';
                $newDogIDResult = $mysqli->query($newDogIDQuery);
                if($newDogIDResult->num_rows > 0)
                {
                    $dogID = $newDogIDResult->fetch_row()[0];
                }
            } else if($formSelection == "Rabbit") {
                $newRabbitIDQuery = 'SELECT TOP 1 ID FROM Rabbit WHERE ID < '.$_POST["rabbitID"].' ORDER BY ID DESC';
                $newRabbitIDResult = $mysqli->query($newRabbitIDQuery);
                if($newRabbitIDResult->num_rows > 0)
                {
                    $rabbitID = $newRabbitIDResult->fetch_row()[0];
                }            
            }
        }
        
        if(isset($_POST["update"])) {
            if($formSelection == "Dog") {
                if(!$stmt = $mysqli->prepare("UPDATE $formSelection SET Name = ?, DOB = ?, isFixed = ?, Breed = ?, Fee = ?, DateBooked = ?, isAvailable = ?, RoomNum = ? WHERE ID = ?")) {
                    die("Error in dog prepare: (".$mysqli->errno .") ".$mysqli->error);
                }
                
                if(!$stmt->bind_param("ssssdssii",  $_POST["dogName"], $_POST["dogDOB"], $_POST["dogIsFixed"], $_POST["dogBreed"], $_POST["dogFee"], $_POST["dogDateBooked"], $_POST["dogIsAvailable"], $_POST["dogRoomNum"], $_POST["dogID"])) {
                    die("Error in dog bind_param: (".$mysqli->errno .") ".$mysqli->error);
                }
            }
            if($formSelection == "Cat") {
                if(!$stmt = $mysqli->prepare("UPDATE $formSelection SET Name = ?, DOB = ?, isFixed = ?, Color = ?, Breed = ?, Fee = ?, DateBooked = ?, isAvailable = ?, RoomNum = ? WHERE ID = ?")) {
                    die("Error in cat prepare: (".$mysqli->errno .") ".$mysqli->error);
                }
                
                if(!$stmt->bind_param("sssssdssii",  $_POST["catName"], $_POST["catDOB"], $_POST["catIsFixed"], $_POST["catColor"], $_POST["catBreed"], $_POST["catFee"], $_POST["catDateBooked"], $_POST["catIsAvailable"], $_POST["catRoomNum"], $_POST["catID"])) {
                    die("Error in cat bind_param: (".$mysqli->errno .") ".$mysqli->error);
                }
            }
            if($formSelection == "Rabbit") {
                if(!$stmt = $mysqli->prepare("UPDATE $formSelection SET Name = ?, DOB = ?, isFixed = ?, Breed = ?, Fee = ?, DateBooked = ?, isAvailable = ?, RoomNum = ? WHERE ID = ?")) {
                    die("Error in rabbit prepare: (".$mysqli->errno .") ".$mysqli->error);
                }
                
                if(!$stmt->bind_param("ssssdssii",  $_POST["rabbitName"], $_POST["rabbitDOB"], $_POST["rabbitIsFixed"], $_POST["rabbitBreed"], $_POST["rabbitFee"], $_POST["rabbitDateBooked"], $_POST["rabbitIsAvailable"], $_POST["rabbitRoomNum"], $_POST["rabbitID"])) {
                    die("Error in rabbit bind_param: (".$mysqli->errno .") ".$mysqli->error);
                }
            }

            $stmt->execute();
            $updateSuccess = $stmt->affected_rows > 0;
            $stmt->close();
        }
        
        $catQuery = "SELECT * FROM `Cat` WHERE ID >= ".$catID." ORDER BY ID LIMIT 1";
        $catResult = $mysqli->query($catQuery);
        $cat = $catResult->fetch_row();
        $catID = $cat[0];
        $catName = $cat[1];
        $catDOB = substr($cat[2], 0, 10);
        $catIsFixed = $cat[3];
        $catColor = $cat[4];
        $catBreed = $cat[5];
        $catFee = $cat[6];
        $catDateBooked = substr($cat[7], 0, 10);
        $catIsAvailable = $cat[8];
        $catRoomNum = $cat[9];
        
        $dogQuery = "SELECT * FROM `Dog` WHERE ID >=".$dogID." ORDER BY ID LIMIT 1";
        $dogResult = $mysqli->query($dogQuery);
        $dog = $dogResult->fetch_row();
        $dogID = $dog[0];
        $dogName = $dog[1];
        $dogDOB = substr($dog[2], 0, 10);
        $dogIsFixed = $dog[3];
        $dogFee = $dog[4];
        $dogDateBooked = substr($dog[5], 0, 10);
        $dogIsAvailable = $dog[6];
        $dogRoomNum = $dog[7];
        $dogBreed = $dog[9];
        
        $rabbitQuery = "SELECT * FROM `Rabbit` WHERE ID >=".$rabbitID." ORDER BY ID LIMIT 1";
        $rabbitResult = $mysqli->query($rabbitQuery);
        $rabbit = $rabbitResult->fetch_row();
        $rabbitID = $rabbit[0];
        $rabbitDOB = substr($rabbit[1], 0, 10);;
        $rabbitBreed = $rabbit[2];
        $rabbitIsFixed = $rabbit[3];
        $rabbitFee = $rabbit[4];
        $rabbitDateBooked = substr($rabbit[5], 0, 10);
        $rabbitIsAvailable = $rabbit[6];
        $rabbitRoomNum = $rabbit[7];
        $rabbitName = $rabbit[8];
        
        $roomQuery = "SELECT `RoomNum` FROM `Room` WHERE isFull = False";
        $roomResult = $mysqli->query($roomQuery);
        $roomArray = $roomResult->fetch_all();
        ?>

    <center>
        <form class="input-card" method="post" action="UpdateAnimal.php">
            <input id="formSelectedIndicator" type="hidden" name="selectedForm" value="<?php echo isset($_POST["selectedForm"]) ? $_POST["selectedForm"] : "0" ?>">

            <div id="cat-form" class="<?php echo $formSelection == 'Cat' ? '' : 'hide' ?>">
                <h4>Cat ID:</h4>
                <input type="hidden" name="catID" min="0" value="<?php echo $catID?>"/>
                <p><?php echo $catID?></p>
                <h4>Cat Name:</h4>
                <input type="text" name="catName" value="<?php echo $catName?>" />
                <h4>Cat Birthdate:</h4>
                <input type="date" name="catDOB" value="<?php echo $catDOB?>" />
                <h4>Cat is Fixed:</h4>
                <input type="checkbox" name="catIsFixed" <?php echo $catIsFixed == "Yes" ? "checked" : "" ?> />
                <h4>Cat Color:</h4>
                <input type="text" name="catColor" value="<?php echo $catColor?>" />
                <h4>Cat Adoption Fee:</h4>
                <input type="text" name="catFee" value="<?php echo $catFee?>" />
                <h4>Cat Date of Booking:</h4>
                <input type="date" name="catDateBooked" value="<?php echo $catDateBooked?>" />
                <h4>Cat is Available:</h4>
                <input type="checkBox" name="catIsAvailable" value="<?php echo $catIsAvailable?>" />
                <h4>Cat Room Number:</h4>
                <select type="select" name="catRoomNum" >
                <?php if(!in_array($catRoomNum, $roomArray)) { echo "<option selected>".$catRoomNum."</option>"; } ?>
                    <?php foreach($roomArray as $row): ?>
                        <?php if($row[0] == $catRoomNum): ?>
                            <option selected><?php echo $row[0] ?></option>
                        <?php else: ?>
                            <option><?php echo $row[0]?></option>
                        <?php endif; ?>
                    <?php endforeach; ?> 
                    </select>
                    <h4>Cat Breed:</h4>
                    <input type="text" name="catBreed" value="<?php echo $catBreed?>" />
                </div>

                <div id="dog-form" class="<?php echo $formSelection == 'Dog' ? '' : 'hide' ?>">
                    <h4>Dog ID:</h4>
                    <input type="hidden" name="dogID" min="0" value="<?php echo $dogID?>"/>
                    <p><?php echo $dogID?></p>
                    <h4>Dog Name:</h4>
                    <input type="text" name="dogName" value="<?php echo $dogName?>" />
                    <h4>Dog Birthdate:</h4>
                    <input type="date" name="dogDOB" value="<?php echo $dogDOB?>" />
                    <h4>Dog is Fixed:</h4>
                    <input type="checkbox" name="dogIsFixed" <?php echo $dogIsFixed == "Yes" ? "checked" : "" ?> />
                    <h4>Dog Adoption Fee:</h4>
                    <input type="text" name="dogFee" value="<?php echo $dogFee?>" />
                    <h4>Dog Date of Booking:</h4>
                    <input type="date" name="dogDateBooked" value="<?php echo $dogDateBooked ?>" />
                    <h4>Dog is Available:</h4>
                    <input type="checkBox" name="dogIsAvailable" value="<?php echo $dogIsAvailable?>" />
                    <h4>Dog Room Number:</h4>
                    <select type="select" name="dogRoomNum" >
                    <?php if(!in_array($dogRoomNum, $roomArray)) { echo "<option selected>".$dogRoomNum."</option>"; } ?>
                    <?php foreach($roomArray as $row): ?>
                        <?php if($row[0] == $dogRoomNum): ?>
                            <option selected><?php echo $row[0] ?></option>
                        <?php else: ?>
                            <option><?php echo $row[0]?></option>
                        <?php endif; ?>
                    <?php endforeach; ?> 
                    </select>
                    <h4>Dog Breed:</h4>
                    <input type="text" name="dogBreed" value="<?php echo $dogBreed?>" />
                </div>

                <div id="rabbit-form" class="<?php echo $formSelection == 'Rabbit' ? '' : 'hide' ?>">
                    <h4>Rabbit ID:</h4>
                    <input type="hidden" name="rabbitID" min="0" value="<?php echo $rabbitID?>"/>
                    <p><?php echo $rabbitID?></p>
                    <h4>Rabbit Name:</h4>
                    <input type="text" name="rabbitName" value="<?php echo $rabbitName?>" />
                    <h4>Rabbit Birthdate:</h4>
                    <input type="date" name="rabbitDOB" value="<?php echo $rabbitDOB?>" />
                    <h4>Rabbit is Fixed:</h4>
                    <input type="checkbox" name="rabbitIsFixed" <?php echo $rabbitIsFixed== "Yes" ? "checked" : "" ?> />
                    <h4>Rabbit Adoption Fee:</h4>
                    <input type="text" name="rabbitFee" value="<?php echo $rabbitFee?>" />
                    <h4>Rabbit Date of Booking:</h4>
                    <input type="date" name="rabbitDateBooked" value="<?php echo $rabbitDateBooked?>" />
                    <h4>Rabbit is Available:</h4>
                    <input type="checkBox" name="rabbitIsAvailable" value="<?php echo $rabbitIsAvailable?>" />
                    <h4>Rabbit Room Number:</h4>
                    <select type="select" name="rabbitRoomNum" >
                    <?php if(!in_array($rabbitRoomNum, $roomArray)) { echo "<option selected>".$rabbitRoomNum."</option>"; } ?>
                    <?php foreach($roomArray as $row): ?>
                        <?php if($row[0] == $rabbitRoomNum): ?>
                            <option selected><?php echo $row[0] ?></option>
                        <?php else: ?>
                            <option><?php echo $row[0]?></option>
                        <?php endif; ?>
                    <?php endforeach; ?> 
                    </select>
                    <h4>Rabbit Breed:</h4>
                    <input type="text" name="rabbitBreed" value="<?php echo $rabbitBreed?>" />
                </div>

                <input type="submit" name="left" value="<" />
                <input type="submit" name="update" value="Update" />
                <input type="submit" name="right" value=">" />
            </form>
            <?php if($updateSuccess):?>
                <p>Successful Update</p>
            <?php endif;?>
            <?php echo $mysqli->error ?>
        </center>
        <?php $mysqli->close(); ?>
    </body>
    <script src="js/updateAnimal.js" ></script>

</html>