#!/bin/bash

##for
#for i in $(ls /home/qinz18)
for i in `ls /home/qinz18`
do
    echo $i
done

##while
num=1
DIR="testDir"
while (($num<5))
do
    if [ -d $Dir$num ]
    then
        echo "$Dir$num exist!!"
    else
        mkdir $Dir$num
    fi
    let num+=1
done
