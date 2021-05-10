<?php
    include 'Cards.php';
?>

<html>
    <head>
        <link href="css/animalCards.css" rel="stylesheet" /> 
        <link href="css/adoptAnimal.css" rel="stylesheet" /> 
        <link href="css/style.css" rel="stylesheet" />
    </head>
    <body>
        <header>
            <div class="main-nav">
                <a class="button" href="index.html">Home</a>
                <a class="button selected" href="AdoptAnimal.php">Adopt</a>
                <a class="button" href="AddAnimal.php">Add</a>
                <a class="button" href="SearchAnimals.php">Search</a>
                <a class="button" href="UpdateAnimal.php">Update</a>
            </div>
            <div class="sub-nav">
                <div class="button selected" id="cat-selector">Cat</div>
                <div class="button" id="dog-selector">Dog</div>
                <div class="button" id="rabbit-selector">Rabbit</div>
            </div>
        </header>
        <center>
            <form class="input-card" method="post" action="AdoptAnimal.php">
                <input id="species-input" type="hidden" name="species" value="Cat" />
                <input type="text" name="id" />
                <input type="submit" value="Adopt this pet" ?>
            </form>
        </center>

        <?php

            $host="services1.cse.sdsmt.edu"; //hostname URL
            $port=3306;						 //default port 3306
            $user="s7416949_f19";				 //DBMS login username
            $password="n8ate123";			 //DBMS login password
            $dbname="db_s7416949_f19";		 //Select DB 


            /* Connect to MySQL */
            $mysqli = new mysqli($host, $user, $password, $dbname, $port);

            /* Check connection error*/
            if ($mysqli->connect_errno) {
                printf("Connect failed: %s\n", $mysqli->connect_error);
                exit();
            }

            if(isset($_POST["id"])) {
                $animal_id = (int)$_POST["id"];
                $animal_species = $_POST["species"];
                if(!$stmt = $mysqli->prepare("DELETE FROM `$animal_species` WHERE ID = ?")) {
                    die("Error in prepare: (".$mysqli->errno .") ".$mysqli->error);
                }

                if(!$stmt->bind_param("i", $animal_id)) {
                    die("Error in bind_param: (".$mysqli->errno .") ".$mysqli->error);
                }
                $stmt->execute();
                $stmt->close();
            }

            /* Access the VIDEOFORRENT table */
            $result = $mysqli->query("Select * from Dog"); 

            ?>

            <?php if($result): ?>
                <div id="dog-display" class="animal-card-wrap hide">
                <?php while($row=$result->fetch_row())
                {
                    echo displayDogCard($row);
                } ?>
                </div>
            <?php
                endif;
                $result->close();
            ?>

            <?php
            /* Access the VIDEOFORRENT table */
            $result = $mysqli->query("Select * from Cat"); 

            ?>
            <?php if($result): ?> 

                <div id="cat-display" class="animal-card-wrap">
                    <?php while($row=$result->fetch_row()) {
                        echo displayCatCard($row);
                    }?>
                </div>

            <?php endif; ?>
            <?php $result->close(); ?>

            <?php
            /* Access the VIDEOFORRENT table */
            $result = $mysqli->query("Select * from Rabbit"); 

            if($result):?>
            <div id="rabbit-display" class="animal-card-wrap hide">
            <?php while($row=$result->fetch_row()) {
                echo displayRabbitCard($row);
            }?>
            </div>
            <?php
            endif;  
            $result->close();
            $mysqli->close();
            ?>

        <script src="js/adoptAnimal.js" type="text/javascript"></script>
    </body>
</html>