#! /bin/sh

#for i in 1 5 10 50 100 500 1000 5000 10000;
for i in 1 5 10 50 100 500 1000
do
	for j in `seq 1 5`
	do
		time -f "%E\t%M" simulations/bin/scale $i > /dev/null
	done
	echo Done set for $i
done
