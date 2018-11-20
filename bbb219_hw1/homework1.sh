#!/bin/ksh

echo
echo "Romeo Bahoumda"
echo "CSE271- Homework1"
echo
### Pring the number of words in the linux dictionary
VAL=$(wc -w /usr/share/dict/words)
echo "How many words are in the Linux dictionary?"
echo "Answer: $VAL"
echo
### Print the number of characters in the linux dictionary
CHAR=$(wc -c /usr/share/dict/words)
echo "How many characters are in the Linux dictionary?"
echo "Answer: $CHAR"
echo

### Determing the number of executables in /usr/bin have 2 p characters
cd /usr/bin
#PWD=$(pwd) 
#echo "$PWD"
NUM=$(find -type f -perm +111 | wc -l)
echo "Number of executable in /usr/bin/ with 2 'p' characters in their name"
echo "Answer: $NUM "
echo

### List all of the environment variables which contains my user name
echo "Username = bbb219"
LIST=$(printenv | grep bbb219)
echo "List of all environment containing bbb219"
for i in $LIST; do
    echo "     $i"
done
echo


### Using the cut program to list the user name and user ID fields found etc/passwd
### UserName - 1     UID - 3
LIST2=$(cut -f 1,3 -d ':' /etc/passwd)
echo "List of User Names and User ID fields in etc/passwd"
for i in $LIST2; do
    echo "      $i"
done
echo

### List all of the processes not owned by root or user and have a parent process ID=1
LIST3=$(ps -ef | grep -v root | grep -v bbb219 | awk '$3==1')
echo "Processes not owned by root or bbb219 and having PPID 1"
echo "$LIST3"
    
