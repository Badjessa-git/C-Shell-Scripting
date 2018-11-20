#!/bin/bash 
## Badjessa B. Bahoumda         
## CSE 271 
## Calculating pi using bc and leibniz formula

echo 'starting...'

scale="scale=1000"
pi=4
divider=3
ch=3
while [ $divider -le 100000000 ]
do
    check=$(echo "$ch%2" | bc);
    if [ $check -ne 0 ]
    then
	pi=$(echo "$scale;$pi-(4.0/$divider)" | bc )
	ch=$(echo "$ch+1" | bc)
    else
	pi=$(echo "$scale;$pi+(4.0/$divider)" | bc )
	ch=$(echo "$ch+1" | bc)
    fi
    divider=$(echo "$divider+2" | bc )
done

echo $pi
