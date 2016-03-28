#!/bin/bash

LIST_NEW=eventList__diLepton_CR__data.dat
LIST_OLD=eventList__diLepton_CR__data__old.dat


echo ""
echo ""
echo "COMPARING EVENT LISTS"
echo "  LIST_NEW=$LIST_NEW"
echo "  LIST_OLD=$LIST_OLD"
echo ""
echo ""
echo ""
echo "     CHECKING FOR EVENTS IN BOTH OLD AND NEW FILES"
echo ""
echo ""

# Read new file, print events that are in both
DIFF_MET=0
DIFF_MT2W=0
NSAME=0
while read lineNew
do
    EVENT_NEW=`echo $lineNew | awk '{ print $3 }'`
    
    EVENT_OLD=''
    foundLineOld=''
    while read lineOld
    do
	EVENT_OLD=`echo $lineOld | awk '{ print $3 }'`
	if [ "$EVENT_NEW" == "$EVENT_OLD" ] 
	then 
	    foundLineOld=$lineOld; 
	    break
	fi
    done < $LIST_OLD
    
    if [ ! -z "$foundLineOld" ]
    then 
	echo "FOUND SAME EVENT: "
	echo "  OLD_SAME: $foundLineOld"
	echo "  NEW_SAME: $lineNew"
	if [ "$NSAME" != "0" ] 
	then
	    NEW_MET=`echo $lineNew | awk '{ print $5 }' | sed 's/met=//g'`
	    NEW_MT2W=`echo $lineNew | awk '{ print $9 }' | sed 's/MT2W=//g'`
	    OLD_MET=`echo $foundLineOld | awk '{ print $5 }' | sed 's/met=//g'`
	    OLD_MT2W=`echo $foundLineOld | awk '{ print $9 }' | sed 's/MT2W=//g'`
	    DIFF_MET=`echo "$DIFF_MET + $NEW_MET - $OLD_MET" | bc -l`
	    DIFF_MT2W=`echo "$DIFF_MT2W + $NEW_MT2W - $OLD_MT2W" | bc -l`
	    DIFF_MET_TEMP=`echo "$NEW_MET - $OLD_MET" | bc -l`
	    DIFF_MT2W_TEMP=`echo "$NEW_MT2W - $OLD_MT2W" | bc -l`
	    echo "  DIFF_MET  = $DIFF_MET_TEMP"
	    echo "  DIFF_MT2W = $DIFF_MT2W_TEMP"
	fi
	echo ""
	NSAME=$((NSAME+1))
    fi
done < $LIST_NEW
NSAME=$((NSAME+1))

AVG_DIFF_MET=`echo "$DIFF_MET / $NSAME" | bc -l`
AVG_DIFF_MT2W=`echo "$DIFF_MT2W / $NSAME" | bc -l`

echo ""
echo " AVG DIFF MET  = $AVG_DIFF_MET"
echo " AVG DIFF MT2W = $AVG_DIFF_MT2W"



echo ""
echo ""
echo ""
echo " HEEEEEEEEEEEEEYYYYYYYYYYYYYYYYYYYY"
echo ""
echo ""
echo ""
echo "     CHECKING FOR EVENTS IN THE NEW FILE NOT IN THE OLD"
echo ""
echo ""

N_GAIN_EVENTS_MET_BIN_1=0
N_GAIN_EVENTS_MET_BIN_2=0
N_GAIN_EVENTS_MET_BIN_3=0

NLINE=0
while read lineNew
do
    EVENT_NEW=`echo $lineNew | awk '{ print $3 }'`
    MET_NEW=`echo $lineNew | awk '{ print $5 }' | sed 's/met=//g'`
    NJETS_NEW=`echo $lineNew | awk '{ print $18 }' | sed 's/nJets=//g'`

    if [ ! "$NLINE" -eq "0" ]
    then
	IS_MET_BIN_1_NEW=false
	if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 249.99" | bc) -eq 1 ] && [ $(echo "$MET_NEW < 275.0" | bc) -eq 1 ]; then IS_MET_BIN_1_NEW=true; fi
	IS_MET_BIN_2_NEW=false
	if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 275.0" | bc) -eq 1 ] && [ $(echo "$MET_NEW < 325.0" | bc) -eq 1 ]; then IS_MET_BIN_2_NEW=true; fi
	IS_MET_BIN_3_NEW=false
	if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 325.0" | bc) -eq 1 ]; then IS_MET_BIN_3_NEW=true; fi
    fi


    EVENT_OLD=""
    foundLineOld=""
    while read lineOld
    do
	EVENT_OLD=`echo $lineOld | awk '{ print $3 }'`
	if [ "$EVENT_NEW" == "$EVENT_OLD" ]
	then 
	    foundLineOld=$lineOld
	    
	    MET_OLD=`echo $lineOld | awk '{ print $5 }' | sed 's/met=//g'`
	    NJETS_OLD=`echo $lineOld | awk '{ print $18 }' | sed 's/nJets=//g'`
	    
	    if [ ! "$NLINE" -eq "0" ]
	    then
		IS_MET_BIN_1_OLD=false
		if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 249.99" | bc) -eq 1 ] && [ $(echo "$MET_OLD < 275.0" | bc) -eq 1 ]; then IS_MET_BIN_1_OLD=true; fi
		IS_MET_BIN_2_OLD=false
		if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 275.0" | bc) -eq 1 ] && [ $(echo "$MET_OLD < 325.0" | bc) -eq 1 ]; then IS_MET_BIN_2_OLD=true; fi
		IS_MET_BIN_3_OLD=false
		if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 325.0" | bc) -eq 1 ]; then IS_MET_BIN_3_OLD=true; fi
	    fi

	    if [ "$IS_MET_BIN_1_NEW" == "true" ] && [ "$IS_MET_BIN_1_OLD" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 1, 250<MET<275: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi
	    if [ "$IS_MET_BIN_2_NEW" == "true" ] && [ "$IS_MET_BIN_2_OLD" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 2, 275<MET<325: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi
	    if [ "$IS_MET_BIN_3_NEW" == "true" ] && [ "$IS_MET_BIN_3_OLD" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 3, MET>325: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi

	    break;
	fi
    done < $LIST_OLD
    
    if [ -z "$foundLineOld" ]
    then 
	echo "FOUND EVENT IN THE NEW FILE NOT IN THE OLD: $lineNew"
	if [ "$IS_MET_BIN_1_NEW" == "true" ]; then echo "   EVENT ENTERED IN MET BIN 1"; N_GAIN_EVENTS_MET_BIN_1=$((N_GAIN_EVENTS_MET_BIN_1+1)); fi
	if [ "$IS_MET_BIN_2_NEW" == "true" ]; then echo "   EVENT ENTERED IN MET BIN 2"; N_GAIN_EVENTS_MET_BIN_2=$((N_GAIN_EVENTS_MET_BIN_2+1)); fi
	if [ "$IS_MET_BIN_3_NEW" == "true" ]; then echo "   EVENT ENTERED IN MET BIN 3"; N_GAIN_EVENTS_MET_BIN_3=$((N_GAIN_EVENTS_MET_BIN_3+1)); fi
	echo ""
    fi

    NLINE=$((NLINE+1))

done < $LIST_NEW

echo ""
echo "NUMBER OF EVENTS GAINED IN MET BIN 1 = $N_GAIN_EVENTS_MET_BIN_1"
echo "NUMBER OF EVENTS GAINED IN MET BIN 2 = $N_GAIN_EVENTS_MET_BIN_2"
echo "NUMBER OF EVENTS GAINED IN MET BIN 3 = $N_GAIN_EVENTS_MET_BIN_3"



echo ""
echo ""
echo ""
echo " HEEEEEEEEEEEEEYYYYYYYYYYYYYYYYYYYY"
echo ""
echo ""
echo ""
echo "     CHECKING FOR EVENTS IN THE OLD FILE NOT IN THE NEW"
echo ""
echo ""



N_LOST_EVENTS_MET_BIN_1=0
N_LOST_EVENTS_MET_BIN_2=0
N_LOST_EVENTS_MET_BIN_3=0

NLINE=0
while read lineOld
do
    EVENT_OLD=`echo $lineOld | awk '{ print $3 }'`
    MET_OLD=`echo $lineOld | awk '{ print $5 }' | sed 's/met=//g'`
    NJETS_OLD=`echo $lineOld | awk '{ print $18 }' | sed 's/nJets=//g'`

    if [ ! "$NLINE" -eq "0" ]
    then
	IS_MET_BIN_1_OLD=false
	if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 249.99" | bc) -eq 1 ] && [ $(echo "$MET_OLD < 275.0" | bc) -eq 1 ]; then IS_MET_BIN_1_OLD=true; fi
	IS_MET_BIN_2_OLD=false
	if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 275.0" | bc) -eq 1 ] && [ $(echo "$MET_OLD < 325.0" | bc) -eq 1 ]; then IS_MET_BIN_2_OLD=true; fi
	IS_MET_BIN_3_OLD=false
	if [ "$NJETS_OLD" -ge "3" ] && [ $(echo "$MET_OLD > 325.0" | bc) -eq 1 ]; then IS_MET_BIN_3_OLD=true; fi
    fi
    
    EVENT_NEW=""
    foundLineNew=""
    while read lineNew
    do
	EVENT_NEW=`echo $lineNew | awk '{ print $3 }'`
	if [ "$EVENT_OLD" == "$EVENT_NEW" ]
	then 
	    foundLineNew=$lineNew

	    MET_NEW=`echo $lineNew | awk '{ print $5 }' | sed 's/met=//g'`
	    NJETS_NEW=`echo $lineNew | awk '{ print $18 }' | sed 's/nJets=//g'`
	    if [ ! "$NLINE" -eq "0" ]
	    then
		IS_MET_BIN_1_NEW=false
		if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 249.99" | bc) -eq 1 ] && [ $(echo "$MET_NEW < 275.0" | bc) -eq 1 ]; then IS_MET_BIN_1_NEW=true; fi
		IS_MET_BIN_2_NEW=false
		if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 275.0" | bc) -eq 1 ] && [ $(echo "$MET_NEW < 325.0" | bc) -eq 1 ]; then IS_MET_BIN_2_NEW=true; fi
		IS_MET_BIN_3_NEW=false
		if [ "$NJETS_NEW" -ge "3" ] && [ $(echo "$MET_NEW > 325.0" | bc) -eq 1 ]; then IS_MET_BIN_3_NEW=true; fi
	    fi
	    
	    if [ "$IS_MET_BIN_1_OLD" == "true" ] && [ "$IS_MET_BIN_1_NEW" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 1, 250<MET<275: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi
	    if [ "$IS_MET_BIN_2_OLD" == "true" ] && [ "$IS_MET_BIN_2_NEW" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 2, 275<MET<325: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi
	    if [ "$IS_MET_BIN_3_OLD" == "true" ] && [ "$IS_MET_BIN_3_NEW" == "false" ]
	    then
		echo "FOUND EVENT THAT LEFT MET BIN 3, MET>325: "
		echo "  OLD_EVENT: $lineOld"
		echo "  NEW_EVENT: $lineNew"
		echo ""
	    fi

	    break;

	fi

        NLINE=$((NLINE+1))

    done < $LIST_NEW

    if [ -z "$foundLineNew" ]
    then 
	echo "FOUND EVENT IN THE OLD FILE NOT IN THE NEW: $lineOld"
	if [ "$IS_MET_BIN_1_OLD" == "true" ]; then echo "   LOST EVENT IN MET BIN 1"; N_LOST_EVENTS_MET_BIN_1=$((N_LOST_EVENTS_MET_BIN_1+1)); fi
	if [ "$IS_MET_BIN_2_OLD" == "true" ]; then echo "   LOST EVENT IN MET BIN 2"; N_LOST_EVENTS_MET_BIN_2=$((N_LOST_EVENTS_MET_BIN_2+1)); fi
	if [ "$IS_MET_BIN_3_OLD" == "true" ]; then echo "   LOST EVENT IN MET BIN 3"; N_LOST_EVENTS_MET_BIN_3=$((N_LOST_EVENTS_MET_BIN_3+1)); fi
	echo ""
    fi
done < $LIST_OLD

echo ""
echo "NUMBER OF LOST EVENTS FROM MET BIN 1 = $N_LOST_EVENTS_MET_BIN_1"
echo "NUMBER OF LOST EVENTS FROM MET BIN 2 = $N_LOST_EVENTS_MET_BIN_2"
echo "NUMBER OF LOST EVENTS FROM MET BIN 3 = $N_LOST_EVENTS_MET_BIN_3"


DELTA_MET_BIN_1=`echo "$N_GAIN_EVENTS_MET_BIN_1 - $N_LOST_EVENTS_MET_BIN_1" | bc`
DELTA_MET_BIN_2=`echo "$N_GAIN_EVENTS_MET_BIN_2 - $N_LOST_EVENTS_MET_BIN_2" | bc`
DELTA_MET_BIN_3=`echo "$N_GAIN_EVENTS_MET_BIN_3 - $N_LOST_EVENTS_MET_BIN_3" | bc`
echo ""
echo ""
echo ""
echo "TOTAL DELTA EVENTS IN MET BIN 1 = $DELTA_MET_BIN_1"
echo "TOTAL DELTA EVENTS IN MET BIN 2 = $DELTA_MET_BIN_2"
echo "TOTAL DELTA EVENTS IN MET BIN 3 = $DELTA_MET_BIN_3"