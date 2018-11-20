#!/bin/bash                                                                    

## Badjessa B. Bahoumda  
## CSE 271
## Look for a file recursively through the system if no directory is specified or the specfied 
## directory


if [ $# -eq 0 ];
then 
    read -p 'Enter the fileName(including extension): ' fileName
else 
    fileName=$1
fi

if [ -z "$2" ];
   then
   cd
   echo 'looking for file'
   rc=$(find . -type f -name $fileName -printf "%Tc %k KB %p" 2>/dev/null)
   if [ -z "$rc" ];
   then
       echo 'File not found now checking zfs'
       cd ~/.zfs/snapshot
       rc=$(find . -type f -name $fileName -printf "%Tc %k KB %p" 2>/dev/null)
   fi
else
    directory=$2
    rc=$(find $directory -type f -name $fileName -printf "%Tc %k KB %p" 2>/dev/null)
fi

if [ -z "$rc" ]; 
    then
    echo 'File not found'
    exit 1
else 
    echo $rc
fi
