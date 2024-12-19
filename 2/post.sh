#!/bin/bash

rm ./postproc/*.txt

sizes=$( cat "progs/sizes.txt" )

flag=1
for type in "main" "key"; do
    for speed in "q" "s"; do
        for size in $sizes; do
            string=$( cat "preproc/${type}_${speed}_${size}.txt" )
            read -r -a array <<< "$string"
            avg="${array[2]}"
            if [ "$flag" == 1 ]; then
                echo "$size $avg" > "./postproc/data_${type}_${speed}.txt"
                flag=0
            else
                echo "$size $avg" >> "./postproc/data_${type}_${speed}.txt"
            fi
        done
    done
done

flag=1
for type in "main" "key"; do
    for speed in "q" "s"; do
        for size in $sizes; do
            string=$( cat "preproc/${type}_${speed}_${size}.txt" )
            read -r -a array <<< "$string"
            min="${array[1]}"
            max="${array[0]}"
            avg="${array[2]}"
            if [ "$flag" == 1 ]; then
                echo "$size $avg $min $max" > "./postproc/data_err_${type}_${speed}.txt"
                flag=0
            else
                echo "$size $avg $min $max" >> "./postproc/data_err_${type}_${speed}.txt"
            fi
        done
    done
done

flag=1
for type in "main" "key"; do
    for speed in "q" "s"; do
        for size in $sizes; do
            string=$( cat "preproc/${type}_${speed}_${size}.txt" )
            read -r -a array <<< "$string"
            min="${array[1]}"
            max="${array[0]}"
            avr="${array[2]}"
            hq="${array[4]}"
            lq="${array[5]}"
            if [ "$flag" == 1 ]; then
                echo "$size $min $lq $avr $hq $max" > "./postproc/data_mstch_${type}_${speed}.txt"
                flag=0
            else
                echo "$size $min $lq $avr $hq $max" >> "./postproc/data_mstch_${type}_${speed}.txt"
            fi
        done
    done
done

flag=1
for speed in "q" "s"; do
    for type in "main" "key"; do
        for size in $sizes; do
            string=$( cat "preproc/${type}_${speed}_${size}.txt" )
            read -r -a array <<< "$string"
            avr="${array[2]}"
            if [ "$flag" == 1 ]; then
                echo "$avr" > "./postproc/data_t_${speed}.txt"
                flag=0
            else
                echo "$avr" >> "./postproc/data_t_${speed}.txt"
            fi
        done
    done
done