#!/usr/bin/env bash
if [[ $1 ]]; then
	MOVES=$1
else
	echo "Usage: $0 [# OF MOVES]"
	exit 1
fi
FILE="chess.txt"
echo $FILE
if [[ -f /tmp/$FILE ]]; then
	rm /tmp/$FILE
fi
for I in {0..7}; do
	for J in {0..7}; do
		./a.out "$I" "$J" "$MOVES" >> /tmp/$FILE
	done
done
echo "Output redirected to /tmp/$FILE"
echo "Done"
