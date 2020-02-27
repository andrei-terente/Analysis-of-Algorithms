#!/bin/bash
COUNTER=0
STRINGLEN=10
if [[ ! -d aux ]]; then
	mkdir aux
fi
if [[ ! -d aux/in ]]; then
	mkdir aux/in
fi
while [[ $COUNTER -lt 15 ]]; do
	FILE=aux/in/input$COUNTER.txt
	if [[ ! -e $FILE ]]; then
		touch $FILE
	fi
	TEXT=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $STRINGLEN | head -n 1)
	SINDEX=$(( RANDOM % STRINGLEN ))
	PSIZE=$(( RANDOM % ( ( STRINGLEN - SINDEX ) + 1 ) ))
	LINDEX=$(( SINDEX + PSIZE  ))
	PATTERN=$(echo $TEXT | cut -c $SINDEX-$LINDEX)
	echo $TEXT > $FILE
	echo $PATTERN >> $FILE
	STRINGLEN=$(( STRINGLEN + 2 ))
	let COUNTER=COUNTER+1
done
