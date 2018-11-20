#!/bin/bash                                     
## Badjessa B. Bahoumda                                                      
## CSE 271                                                                     
## Print out the 10 biggest file and delete whichever file the user chooses to

while :
do
    du -ks ~ 2>/dev/null
    if [ $# -eq 0 ];
    then
	cd
        rc=$(find -type f -exec du -khs * 2>/dev/null {} + | sort -rh | head -10)
        echo "$rc"
    else
        directory=$1
        cd directory
        rc=$(find $directory -type f -exec du -khs * 2>/dev/null {} + | sort -rh | head -10)
        echo "$rc"
    fi

    read -p "Enter the number of the file you want to delete(Enter CTRL+D to exit): " number
    if [ $? -ne 0 ];
    then
	echo 'Exiting...'
        exit 0
    fi

    while ! [[ "$number" =~ ^[0-9]+$ ]];
    do
        read -p "Wrong input, please enter a number or CTRL+D to exit: " number
	if [ $? -ne 0 ]
	then 
	    echo 'Exiting...'
	    exit 0
	fi
    done
    values=($rc)
    check=number-1
    file=${values[number+check]}
    cat /dev/null > $file
    rm -f $file
    if [ $? -eq 0 ];
    then
        echo 'File was successfully deleted'
    fi
done
