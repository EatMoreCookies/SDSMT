#!/bin/bash

OLDIFS=$IFS
IFS=","

while read Player Place Kills Shots Hits AP Radar MaxHealth RemainingHealth MaxAmmo 
do
	echo -e "\t $Player \n
	Role : \t $Place \n\
	Kills : \t $Kills \n\ "  
done < $1
IFS=$OLDIFS
