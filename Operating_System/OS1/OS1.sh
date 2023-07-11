#Gamze Nur Madan - 260201084
#Halil İbrahim Buğday - 280201094

#!/bin/bash

read -p "Enter the name of the directory: " directory
read -p "Enter the keyword: " keyword

#first function
function search_and_copy {
#creating Found folder if there is no Found folder
	if [ ! -d "Found" ]
	then
		mkdir Found
	fi
#searching for keyword in given directory and taking output as the list of the file names with -l command, since it is a keyword it can be case insensitive so we used -i command.
	grep -r -l -i $1 $2 | while read file;
	do
	#copying the file while changing its name
		cp "$file" "Found/found_$(basename "$file")"
	done
#checking if the found folder has any file in it	
	if [ "$(ls -A Found)" ]
	then
		echo "Files were copied to the Found directory!" && ls Found
	else
		echo "Keyword not found in files!"
	fi
}

#second function
function modification_details {
	LC_TIME=en_US.UTF-8 #To make a month's name always in English
	if [ "$(ls -A Found)" ]
	then
		count=0
		for file in Found/*
		do
		((count++))
		echo "File $count: $(basename "$file") $(stat -c "was modified by %U" $file) $(date -r $file +"on %B %d, %Y at %H.%M")" >> Found/modification_details.txt
		done
		cat Found/modification_details.txt
	fi
}

search_and_copy $keyword $directory && modification_details



