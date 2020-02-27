#!/bin/bash

CURRENT_SET=1
CURRENT_BIG_SET=1

make clean
if [ $# -eq 0 ]
  then
     make build_best
     ALGO="Algorithm used: Knuth-Morris-Pratt"
else
	if [[ "$1" = "naive" ]]; then
		make build_naive
		ALGO="Algorithm used: Naive method"
	fi
	if [[ "$1" = "kmp" ]]; then
		make build_best
		ALGO="Algorithm used: Knuth-Morris-Pratt"
	fi
	if [[ "$1" = "rk" ]]; then
		ALGO="Algorithm used: Rabin-Karp"
		make build_snd_best
	fi
fi


./tester | tee tmp.txt
grep 'execution time' < tmp.txt > tmp2.txt
cat tmp2.txt | cut -d " " -f3 > tmp3.txt

if [[ ! -d splits ]]; then
	mkdir splits
fi

cd splits
split -l 15 ../tmp3.txt split_set
cd ..
if [[ ! -e execution_times.txt ]]; then
	touch execution_times.txt
fi
> execution_times.txt
for filename in splits/*; do
	if [[ $CURRENT_SET -lt 7 ]]; then
		echo "SET $CURRENT_SET" >> execution_times.txt
		echo $(paste -sd+ $filename | bc) ms >> execution_times.txt
		let CURRENT_SET=CURRENT_SET+1
	else
	echo "BIG SET $CURRENT_BIG_SET" >> execution_times.txt
	echo $(paste -sd+ $filename | bc) ms >> execution_times.txt
	let CURRENT_BIG_SET=CURRENT_BIG_SET+1
	fi
done
echo $ALGO >> execution_times.txt
cat execution_times.txt
make clean
rm tmp*
rm -rf splits
