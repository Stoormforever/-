#!/bin/bash

sizes=$( cat "progs/sizes.txt" )
count=500
files=5
flag=0

for c in $(seq "$count"); do
    for type in 'key' 'main'; do
        for speed in 'q' 's'; do
            for i in $sizes; do
                echo -n -e "$c/$count \r"
                if [ "$flag" == 1 ]; then
                    ./apps/test.exe in_data/data_"${i}"_in.txt "${type}" "${speed}" > out_data/"${type}"_"${speed}"_"${i}"_out.txt
                else
                    ./apps/test.exe in_data/data_"${i}"_in.txt "${type}" "${speed}" >> out_data/"${type}"_"${speed}"_"${i}"_out.txt
                fi
            done
        done
    done
done
