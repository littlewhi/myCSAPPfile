#!/bin/bash

echo 'c1'
./csim -s 1 -E 1 -b 1 -t traces/yi2.trace >> ansA
echo 'c2'
./csim -s 4 -E 2 -b 4 -t traces/yi.trace >> ansA
echo 'c3'
./csim -s 2 -E 1 -b 4 -t traces/dave.trace >> ansA
echo 'c4'
./csim -s 2 -E 1 -b 3 -t traces/trans.trace >> ansA
echo 'c5'
./csim -s 2 -E 2 -b 3 -t traces/trans.trace >> ansA
echo 'c6'
./csim -s 2 -E 4 -b 3 -t traces/trans.trace >> ansA
echo 'c7'
./csim -s 5 -E 1 -b 5 -t traces/trans.trace >> ansA
echo 'c8'
./csim -s 5 -E 1 -b 5 -t traces/long.trace >> ansA
