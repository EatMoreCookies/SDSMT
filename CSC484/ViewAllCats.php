<?php include "Cards.php"?>
<HTML>
<HEAD>
<TITLE>View Cats</TITLE>
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
      <H2><CENTER>Show all Cats Available for Adoption</CENTER></H2>
   <FORM METHOD="post" action="ViewAllCats.php">
   <P>
   <CENTER>

   <?php

      $host="services1.cse.sdsmt.edu"; //hostname URL
      $port=3306;						 //default port 3306
      $user="s7416949_f19";			 //DBMS login usernames
      $password="n8ate123";			 //DBMS login password
      $dbname="db_s7416949_f19";		 //Select DB 


      /* Connect to MySQL */
      $mysqli = new mysqli($host, $user, $password, $dbname, $port);


      /* Check connection error*/
      if ($mysqli->connect_errno) {
         printf("Connect failed: %s\n", $mysqli->connect_error);
         exit();
      }

      $var = 0;

      $statement = $mysqli->prepare( "SELECT * From Cat Where ID >= ? " );
      $statement->bind_param( "i", $var );
      $statement->execute();
      $result = $statement->get_result();
   ?>

   <?php
      /* Fetch and displays each row of $result */ 
      if( $result )
      {
         echo'<div class="animal-card-wrap">';
         while( $row = $result->fetch_row() )
         {
            echo displayCatCard( $row );
         }
         echo'</div>';
      }
      $statement->close();
      $result->close();
      $mysqli->close();
   ?>

   <BR>
   <BR>

   </BODY>
</HTML>