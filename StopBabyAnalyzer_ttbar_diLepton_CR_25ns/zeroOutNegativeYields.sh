#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "You must enter exactly 1 command line argument: the/input/directory/relative/path/"
fi

DIR=$1

for x in `/bin/ls $DIR/*.root`; do
    
    test=`echo $x | grep "_noNegYield.root"`
    if [ ! -z $test ]; then continue; fi

    test=`echo $x | grep "amcnlo"`
    if [ ! -z $test ];
    then
	echo "Checking for zeros in: $x"
	root -l -b -q zeroOutNegativeYields.C++'("'$x'")'
    fi

done

