<?php
function displayCatCard($row, $isEditable = false) {
    $ID = $row[0];
    $name = $row[1];
    $DOB = $row[2];
    $isFixed = $row[3];
    $color = $row[4];
    $breed = $row[5];
    $fee = $row[6];
    $dateBooked = $row[7];
    $isAvailable = $row[8];
    $roomNum = $row[9];
    ob_start(); ?>

    <div class="animal-card cat">
        <div class="content-wrap">
            <h3>Name: <?php echo $name ?></h3>
            <p><strong>ID: </strong><?php echo $ID ?></p>
            <p><strong>Date of Birth: </strong><?php echo substr($DOB, 0, 10) ?></p>
            <p><strong>Is Fixed: </strong><?php echo $isFixed ?></p>
            <p><strong>Color: </strong><?php echo $color ?></p>
            <p><strong>Breed: </strong><?php echo $breed ?></p>
            <p><strong>Fee: </strong><?php echo $fee ?></p>
            <p><strong>Date Booked: </strong><?php echo substr($dateBooked, 0, 10) ?></p>
            <p><strong>Is Available: </strong><?php echo $isAvailable ?></p>
            <p><strong>Room Number: </strong><?php echo $roomNum ?></p>
        </div>
    </div>

<?php 
    $html = ob_get_clean();
    return $html;
}
?>

<?php
function displayDogCard($row, $isEditable = false) {
    $ID = $row[0];
    $name = $row[1];
    $DOB = $row[2];
    $isFixed = $row[3];
    $fee = $row[4];
    $dateBooked = $row[5];
    $isAvailable = $row[6];
    $roomNum = $row[7];
    $isGoodBoy = $row[8];
    $breed = $row[9];
    ob_start(); ?>

    <div class="animal-card dog">
        <div class="content-wrap">
        <h3>Name: <?php echo $name ?></h3>
            <p><strong>ID: </strong><?php echo $ID ?></p>
            <p><strong>Date of Birth: </strong><?php echo substr($DOB, 0, 10) ?></p>
            <p><strong>Is Fixed: </strong><?php echo $isFixed ?></p>
            <p><strong>Is Good Boy: </strong><?php echo $isGoodBoy ?></p>
            <p><strong>Breed: </strong><?php echo $breed ?></p>
            <p><strong>Fee: </strong><?php echo $fee ?></p>
            <p><strong>Date Booked: </strong><?php echo substr($dateBooked, 0, 10) ?></p>
            <p><strong>Is Available: </strong><?php echo $isAvailable ?></p>
            <p><strong>Room Number: </strong><?php echo $roomNum ?></p>
        </div>
    </div>

<?php 
    $html = ob_get_clean();
    return $html;
}
?>

<?php
function displayRabbitCard($row, $isEditable = false) {
    $ID = $row[0];
    $DOB = $row[1];
    $breed = $row[2];
    $isFixed = $row[3];
    $fee = $row[4];
    $dateBooked = $row[5];
    $isAvailable = $row[6];
    $roomNum = $row[7];
    $name = $row[8];
    ob_start(); ?>

    <div class="animal-card rabbit">
        <div class="content-wrap">
        <h3>Name: <?php echo $name ?></h3>
            <p><strong>ID: </strong><?php echo $ID ?></p>
            <p><strong>Date of Birth: </strong><?php echo substr($DOB, 0, 10) ?></p>
            <p><strong>Is Fixed: </strong><?php echo $isFixed ?></p>
            <p><strong>Breed: </strong><?php echo $breed ?></p>
            <p><strong>Fee: </strong><?php echo $fee ?></p>
            <p><strong>Date Booked: </strong><?php echo substr($dateBooked, 0, 10) ?></p>
            <p><strong>Is Available: </strong><?php echo $isAvailable ?></p>
            <p><strong>Room Number: </strong><?php echo $roomNum ?></p>
        </div>
    </div>

<?php 
    $html = ob_get_clean();
    return $html;
}
?>