#!/bin/bash
for ty in wt w1 B+ B- N+ N- T-
do
    if [ -d ./singleExpression/$ty ];then
        for file in ./singleExpression/$ty/*
        do
            if [ -d $file ];then
                cd $file
                cp ../../../data_P/wt/bcd_P.txt ./
                cp ../../../data_P/wt/cad_P.txt ./
                cp ../../../data_P/wt/tll_P.txt ./
                gnuplot ../../../plotAllGeneInLine.plt
                cd ../../..
            fi
        done
    fi
done
