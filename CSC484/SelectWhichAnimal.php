<html>
	<head>
		<title>Test PHP-MySQL-2018</title>
	</head>

	<body bgcolor = #B2F4FD>
		<h2>
			<center>
				What Kind of Animal Do You Want To Adopt??
			</center>
		</h2>

		<form method="post" action="AdoptADog.php">
			<center>
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

				/* Execute Query */
				$res = $mysqli->query("SELECT * FROM Dog" );

				?>
				
				<table>
					<tr>
						<th><strong> Select Animal to Adopt </strong></th>
					</tr>
					<tr>
						<td valign = top>
							<select size=<?php echo $num;?> id=isAvailable name=isAvailable>
								<option>Cat</option>
								<option>Dog</option>
								<option>Rabbit</option>
							</select>
						</td>
					</tr>
				</table>
				
				<div id="dog-listing">
					<?php 
						//$result = $mysqli->query("Select * from Dog"); 
					?>

					<table Border="1">
						<tr>
							<?php while ($field=$result->fetch_field()):?>
							<th>
								<?php //echo "$field->name"; ?>
							</th>
							<?php endwhile; ?>
						</tr>

						<?php /* Fetch and displays each row of $result */  ?>
						<?php if($result): ?>
							<?php while($row=$result->fetch_row()): ?>
							
								<tr>
								<?php for ($i=0; $i < $result->field_count; $i++): ?>
									<td> 
										<?php //echo $row[$i] ?>
									</td>
								<?php endfor; ?>
								</tr>
							<?php endwhile; ?>
						<?php endif;?>
						<?php
							$result->close();
							$mysqli->close();
						?>

					</table>
				</div>
				<input type="SUBMIT" value="Execute SQL statement...">
				<input type="RESET"  value="Clear...">

				</form>
		</center>
	</body>
</html>