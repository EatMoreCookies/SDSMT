<html>
    <head>
        <link rel="stylesheet" type="text/css" href="css/addAnimal.css">
        <link href="css/style.css" rel="stylesheet">

    </head>
    <body>
        <header>
            <div class="main-nav">
                <a class="button" href="index.html">Home</a>
                <a class="button" href="AdoptAnimal.php">Adopt</a>
                <a class="button selected" href="AddAnimal.php">Add</a>
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

                $roomQuery = "SELECT `RoomNum` FROM `Room` WHERE isFull = False";
                $roomResult = $mysqli->query($roomQuery);
        ?>
            <form class="input-card" name="addAnimal" method="post" action="AddAnimal.php">
                <input id="species-input" type="hidden" name="species" value="0"></input>

                <input type="hidden" name="isGoodBoy" value="true" />
                <div id="pet-id">
                    <h4>Pet ID:</h4>
                    <input type="number" name="id" min="0"/>
                </div>

                <div id="pet-name">
                    <h4>Pet Name:</h4>
                    <input type="text" name="name" />
                </div>

                <div id="pet-dob">
                    <h4>Pet Birthdate:</h4>
                    <input type="date" name="dob" />
                </div>

                <div id="pet-fixed">
                    <h4>Pet is Fixed:</h4>
                    <input type="checkbox" name="isFixed" />
                </div>

                <div id="pet-color" class="hide">
                    <h4>Pet Color:</h4>
                    <input type="text" name="color" />
                </div>

                <div id="pet-fee">
                    <h4>Pet Adoption Fee:</h4>
                    <input type="text" name="fee" />
                </div>

                <div id="pet-booking">
                    <h4>Date of Booking:</h4>
                    <input type="date" name="dateBooked" />
                </div>

                <div id="pet-available">
                    <h4>Pet is Available:</h4>
                    <input type="checkBox" name="isAvailable" />
                </div>

                <div id="pet-room">
                    <h4>Pet Room Number:</h4>
                    <select type="select" name="roomNumber" >
                    <?php while($row = $roomResult->fetch_row()): ?>
                        <option><?php echo $row[0]?></option>
                    <?php endwhile; ?>    
                    </select>
                </div>

                <div id="pet-breed">
                    <h4>Pet Breed:</h4>
                    <input type="text" name="breed" />
                </div>
                <input type="submit" value="Add Animal" />

            </form>

            <?php 
            if(isset($_POST["id"])) {                

                $species = $animals[(int)$_POST["species"]];
                $id = $_POST['id'];
                $name = $_POST['name'];
                $dob = $_POST['dob'];
                $isFixed = $_POST['isFixed'] ? "Yes" : "No";
                $fee = (float)$_POST['fee'];
                $dateBooked = $_POST['dateBooked'];
                $isAvailable = $_POST['isAvailable'] ? "Yes" : "No";
                $roomNum = $_POST['roomNumber'];
                $isGoodBoy = $_POST["isGoodBoy"] ? "Yes" : "No";
                $breed = $_POST['breed'];
                
                //Dogs have an additional isGoodBoy column
                if($species == "Dog") {
                    if(!$stmt = $mysqli->prepare("INSERT INTO `$species` VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")) {
                        die("Error in dog prepare: (".$mysqli->errno .") ".$mysqli->error);
                    }

                    if(!$stmt->bind_param("isssdssiss", $id, $name, $dob, $isFixed, $fee, $dateBooked, $isAvailable, $roomNum, $isGoodBoy, $breed)) {
                        die("Error in dog bind_param: (".$mysqli->errno .") ".$mysqli->error);
                    }
                }
                if ($species == "Rabbit"){
                    if(!$stmt = $mysqli->prepare("INSERT INTO `$species` VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)")) {
                        die("Error in dog prepare: (".$mysqli->errno .") ".$mysqli->error);
                    }

                    if(!$stmt->bind_param("isssdssis", $id, $dob, $breed, $isFixed, $fee, $dateBooked, $isAvailable, $roomNum, $name )) {
                        die("Error in dog bind_param: (".$mysqli->errno .") ".$mysqli->error);
                    }
                }
                if ($species == "Cat"){
                    if(!$stmt = $mysqli->prepare("INSERT INTO `$species` VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")) {
                        die("Error in dog prepare: (".$mysqli->errno .") ".$mysqli->error);
                    }

                    if(!$stmt->bind_param("isssssdssi", $id, $name, $dob, $isFixed, $color, $breed, $fee, $dateBooked, $isAvailable, $roomNum)) {
                        die("Error in dog bind_param: (".$mysqli->errno .") ".$mysqli->error);
                    }
                }

                $stmt->execute();

                if($stmt->affected_rows != 1)
                {
                    echo "<p>Error Adding Pet. Error in execute (".$mysqli->errno.") : ".$mysqli->error."</p>";
                } else {
                    echo "<p>Successfully added ".$name."</p>";
                }

                $stmt->close();
                $mysqli->close();
            }
            ?>
        </center>
    </body>
    <script src="js/addAnimal.js" ></script>
</html>