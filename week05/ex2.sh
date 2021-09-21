#!/usr/bin/bash

# Race condition starts instantly and I can see the same numbers appearing multiple times

while [ -f ex2.txt.lock ]; do
    sleep 0.01
done
if [ ! -f ex2.txt ]; then
    touch ex2.txt
    echo 1 > ex2.txt
fi

ln ex2.txt ex2.txt.lock

for i in $(seq 1000); do
    echo $( calc -p $(cat ex2.txt | tail -n 1)+1 ) >> ex2.txt
done

rm ex2.txt.lock
