#!/bin/bash
g++ code/*.cpp -o k -lm -O2
for ((i=0;i<$1;i++))
do
    pkurun-cnlong 1 1 ./k wt $i $2
done
