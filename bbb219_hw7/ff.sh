#!/bin/bash                                                                  
## Badjessa B. Bahoumda        
## CSE 271          
## Returns all the files whos names or contents contains the strings passed as an argument
## First define the options that will be expected 
## ?t -> help
## x -> Extension
## -- <String> -> add the name of the string with a hyphen
## i -> makes the search case insensitive
## n -> the search is non-hierarchical
## d -> adds the directory in which to search

insensitive=0      #Flag to make search case insensitive 
extension=".*"     #extension name
hierarchical=0     #Flag to make search hierarchical=0 or not hierarchical=1
directory="/home/$USER"      #Default directory

usage() {
        echo "Usage:"
	echo "    ff.sh -- <filename>                     if file contains hypens (after all args)"
        echo "    ff.sh <filename> -x <extension>         Search using the extension, (include '.')"
        echo "    ff.sh <filename> -i                     Makes the search case insensitive"
        echo "    ff.sh <filename> -n                     Search is non-hierarchical"
        echo "    ff.sh <filename> -d <directory>         Search in specified Directory"
        echo "    ff.sh -t or ff.sh -?                    Show Usage"
}


## Parses the arguments using getopts
while getopts ":?tx:ind:h(help)" opt; do
    case ${opt} in
	i)
	  insensitive=1
	  ;;
	x)
	  extension="$OPTARG"
	  ;;
	n)
	  hierarchical=1
	  ;;
	d)
	  directory="$OPTARG"
	  ;;
	? | h)
	    usage
	    exit 100
	    ;;
      \? )
	  echo "Invalid Option: $OPTARG" 1>&2
	  usage
	  exit 102
	  ;;
    esac
done
shift $((OPTIND - 1))
OPTINS=1

## Check that the -- end of arguement delimiter is used
if [[ "$1" == '--' ]];
then 
    shift #remove '--' to get actual input name
    stringname=$1
elif [ "$1" == "" ];then
    echo "No string is given as input" 1>&2
    echo ""
    usage
    exit 101
else
## Name of the strings that we will use for search                                                  
    stringname=$1
    shift
fi


## If the search is non-hierarcical and case-insensitive
if [ $hierarchical == 1 ] && [ $insensitive == 1 ];
then 
    ret=$(find $directory -maxdepth 1 -type f -iname "$stringname$extension" -print 2>/dev/null)
    ret2=$(grep -IHnwi $stringname $(echo "$directory/*") 2>/dev/null | awk -F ':' '{ printf "%s\\n\\tLine-%s:%s\\n",$1,$2,$3 }' 2>/dev/null)
## if the search is non-hierarchical and case-sensitive
elif [ $hierarchical == 1 ] && [ $insensitive == 0 ];
then
    ret=$(find $directory -maxdepth 1 -type f "$stringname$extension" -print 2/dev/null)
    ret2=$(grep -IHnw $stringname $(echo "$directory/*") 2>/dev/null | awk -F ':' '{ printf "%s\\n\\tLine-%s:%s\\n",$1,$2,$3 }' 2>/dev/null)
## if the search is hierarchical and case-insensitive
elif [ $hierarchical == 0 ] && [ $insensitive == 1 ];
then
    ret=$(find $directory -type f -iname "$stringname$extension" -print 2>/dev/null)
    ret2=$(grep -Hrnwi -e $stringname $(echo "$directory") 2>/dev/null | awk -F ':' '{ printf "%s\\n\\tLine-%s:%s\\n",$1,$2,$3 }' 2>/dev/null)
## if the search is heararchical and case-sensitive
else 
    ret=$(find $directory -type f -name "$stringname$extension" -print 2>/dev/null)
    ret2=$(grep -IHrnw -e $stringname $(echo "$directory") 2>/dev/null | awk -F ':' '{ printf "%s\\n\\tLine-%s:%s\\n",$1,$2,$3 }' 2>/dev/null)
fi

count=0;
## Update a  counter to make sure that the output does not become greater than 99
if [ ! -z "$ret" ];
then
    for i in $ret:
    do
	if [[ $count -lt 99 ]];
	then
	    echo "$i"
	    count=$((count+1))
	else
	    exit $count
        fi
    done
fi

check=0;
if [ ! -z "$ret2" ];
then
    echo ""
    for j in $ret2:
    do
	if [[ $count -lt 99 ]];
	then
	    printf "$j" 2>/dev/null
	    count=$((count+1))
	else
	    echo ##Making sure prompt is on a new line
	    exit $count
	fi
    done
fi
echo
exit $count
