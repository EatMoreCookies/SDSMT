Insert into `Shelter` ( `Location`, `PhoneNumber`, `shelterID` ) 
		Values( 4, '564-684-3960', 1 ),
			  ( 24540, '372-686-9105', 2 ),
              ( 852, '337-262-9045', 3 ),
              (47680,	'113-839-6767',	4 ),
              (463,	'618-411-1250',	5);

Insert into `Room`( `RoomNum`, `Capacity`, `isFull`, `Shelter_ShelterID` )
		Values( 577, 	2,	False,	4 ),
			  ( 988,		3,	False,	4 ),
			  ( 575,		2,	True,	5 ),
			  ( 316,		3,	False,	2 ),
			  ( 877,		2,	False,	2 ),
			  ( 728,		2,	False,	2 ),
			  ( 224,		3,	False,	2 ),
			  (	223,		1,	False,	5 ),
			  ( 865,		1,	False,	3 ),
			  ( 905,		1,	False,	1 ),
			  ( 509,		1,	False,	2 ),
			  ( 879,		2,	True,	3 ),
			  ( 558,		2,	True,	4 ),
			  ( 570,		2,	True,	3 ),
			  ( 645,		3,	True,	1 ),
			  ( 559,		2,	False,	4 ),
			  ( 309,		2,	True,	3 ),
			  ( 948,		3, False,	2 ),
			  ( 903,		3,	True,	4 ),
			  ( 533,		2,	True,	4 );
              
Insert into `Dog`( `ID`, `Name`, `DOB`, `isFixed`, `Fee`, `DateBooked`, `isAvailable`, `RoomNum`, `isGoodBoy`, `Breed` )
		 values (8030, 'Amberly', '2018-11-09', 'No', 184.4, '2019-11-18', 'Yes', 577, 'Yes', 'german shepherd' ),
		  (9550, 'Elijah', '2018-11-10', 'No', 254.3, '2019-08-27', 'Yes', 988, 'Yes', 'golden Retriever'),
		  (8202, 'Huntington', '2017-02-20', 'Yes', 345.0, '2018-04-13', 'Yes', 575, 'Yes', 'pit Bull'),
		  (1134, 'Ola', '2015-03-30', 'No', 430.8, '2019-12-13', 'No', 316, 'Yes', 'pug' ),
		  (4056, 'Roxane', '2019-08-24', 'No', 247.0, '2018-07-21', 'Yes', 877, 'Yes', 'husky' ),
		  (2716, 'Jsandye', '2018-01-20', 'Yes', 202.1, '2019-07-07', 'No', 728, 'Yes', 'labrador' ),
		  (7339, 'Merrill', '2017-12-25', 'No', 321.7, '2019-05-23', 'Yes', 224, 'Yes', 'terrier'),
		  (7343, 'Artie', '2015-06-25', 'No', 384.6, '2019-11-28', 'No', 223, 'Yes', 'pug' ),
		  (5816, 'Humbert', '2017-01-23', 'Yes', 459.9, '2018-07-29', 'No', 865, 'Yes', 'german shepherd' ),
		  (3797, 'Juli', '2015-04-07', 'No', 147.5, '2018-01-27', 'Yes', 905, 'Yes', 'husky' );

Insert into `Cat` ( `ID`, `Name`, `DOB`, `isFixed`, `Color`, `Breed`, `Fee`, `DateBooked`, `isAvailable`, `RoomNum` )
 values (5063, 'Bertram', '2016-02-13', 'Yes', 'Green', 'Burmese', 284.0, '2019-12-20', 'Yes', 509 ),
 (6209, 'Lezlie', '2016-11-02', 'No', 'Maroon', 'Havana', 80.4, '2018-07-13', 'Yes', 879 ), 
 (5712, 'Bar', '2017-01-07', 'No', 'Yellow', 'Manx', 190.9, '2019-09-29', 'No', 558 ),
 (9890, 'Nelie', '2017-03-31', 'No', 'Red', 'Main Coon', 338.6, '2018-01-26', 'No', 570 ),
 (5515, 'Marika', '2019-01-07', 'No', 'Purple', 'Oriental', 271.9, '2019-08-29', 'No', 645 );


Insert into `Rabbit` ( `ID`, `DOB`, `Breed`, `isFixed`, `Fee`, `DateBooked`, `isAvailable`, `RoomNum`, `Name` )
	 values (5258, '2018-06-13', 'American', 'No', 376.0, '2018-05-31', 'Yes', 559,'Clarance'),
			 (3578, '2015-09-23', 'Belgian', 'Yes', 363.1, '2018-03-14', 'No', 309, 'Marna'),
			 (7247, '2015-12-13', 'Cavies', 'Yes', 180.2, '2018-05-09', 'Yes', 948, 'Ranna'),
			 (7998, '2019-07-07', 'Cinnamon', 'Yes', 169.9, '2019-05-02', 'No', 903, 'Salvador'),
			 (7130, '2016-08-07', 'Dutch', 'No', 373.6, '2019-01-31', 'No', 533, 'Perla');



              





              

        

