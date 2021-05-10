<?php include "Cards.php"?>
<HTML>
    <HEAD>
    <TITLE>Search Dogs</TITLE>
        <link href="css/animalCards.css" rel="stylesheet" /> 
        <link href="css/style.css" rel="stylesheet" />
    </HEAD>

    <header>
            <div class="main-nav">
                <a class="button" href="index.html">Home</a>
                <a class="button" href="AdoptAnimal.php">Adopt</a>
                <a class="button" href="AddAnimal.php">Add</a>
                <a class="button selected" href="SearchAnimals.php">Search</a>
                <a class="button" href="UpdateAnimal.php">Update</a>
            </div>
        </header>

    <BODY bgcolor = #B2F4FD>
    <H2><CENTER>Search Dogs
    </CENTER></H2>
        <FORM METHOD="post" action="SearchDogs.php">
        <P>
        <HR>
        <CENTER>

        <?php


        $host="services1.cse.sdsmt.edu"; //hostname URL
        $port=3306;						 //default port 3306
        $user="s7416949_f19";		     //DBMS login username
        $password="n8ate123";			 //DBMS login password
        $dbname="db_s7416949_f19";		 //Select DB 


        /* Connect to MySQL */
        $mysqli = new mysqli($host, $user, $password, $dbname, $port);


        /* Check connection error*/
        if ($mysqli->connect_errno) {
            printf("Connect failed: %s\n", $mysqli->connect_error);
            exit();
        }

        $id = 0;                
        $name = Null;
        $isFixed = Null;
        $fee = 0;
        $isAvailable = Null;
        $breed = Null;

        if( isset($_POST['search'] ) )
        {
            $isFixed = $_POST[ 'isFixed' ] ? 'Yes' : 'No'; 
            $isAvailable = $_POST[ 'isAvailable'] ? 'Yes' : 'No'; 
            $id = $_POST['ID'];                  
            $fee = $_POST['Fee'];
            $breed = $_POST['Breed'];
            
            $validQuery = FALSE;

            if( $id != 0)
            {   
                $validQuery = TRUE;
                $query = "SELECT * FROM Dog Where ID = $id";            
            }

            else
            {    
                $query = "SELECT * FROM Dog WHERE";
    
                if( $fee != 0 )
                {
                    $validQuery = TRUE;
                    $query .= " Fee <= '$fee'";
                }
                
                if( $isFixed != NULL )
                {   
                    $validQuery = TRUE;
                    if( $fee != 0 )
                        $query .= " AND";
                    $query .= " isFixed LIKE '$isFixed'";
                }

                if( $isAvailable != NULL )
                {
                    $validQuery = TRUE;
                    if( $isFixed != NULL || $fee != 0 )
                        $query .= " AND";
                    
                    $query .= " isAvailable LIKE '$isAvailable'";
                }

                if( $breed != NULL )
                {
                    $validQuery = TRUE;
                    if( $isFixed != NULL || $fee != 0 || $isAvailable != NULL )
                        $query .= " AND";

                    $query .= " Breed LIKE '$breed'";
                }
                
                if( !$validQuery )
                    $query = "SELECT * FROM Dog";
            }
            
            $statement = $mysqli->prepare( $query );
            $statement->execute();
            $result = $statement->get_result();
        }

        $mysqli->close();

        ?>

        <BR> Pet ID:
            <BR><INPUT TYPE="TEXT" NAME="ID">
        <BR>
        <BR> Max Price:
            <BR><INPUT TYPE="TEXT" NAME="Fee">
        <BR>
        <BR> Breed:
            <BR><INPUT TYPE="TEXT" NAME="Breed">
        <BR>
        <BR> Fixed?   
                <INPUT TYPE="checkbox" NAME='isFixed'>
        <BR> 
        <BR> Available?
            <INPUT TYPE="checkbox" NAME='isAvailable'> 
        <BR>
        <BR>
       
            <INPUT TYPE="SUBMIT" NAME="search"   VALUE="Search">
        <BR>        
        <BR>
                <?php
                    
                    if( isset($_POST['search'] ) )
                    {
                        /* Fetch and displays each row of $result */ 
                        if( $result )
                            {
                                echo'<div class="animal-card-wrap">';
                                
                                while( $row = $result->fetch_row() )
                                {
                                    echo displayDogCard( $row );
                                }
                                 
                                echo'</div>';
                        }

                        $statement->close();
                        $result->close();
                        $mysqli->close();
                    }
                ?>
            </CENTER>
        </FORM>
    </BODY>
</HTML>