#!/bin/bash

gnuplot go.gpi -persist

gnuplot err.gpi -persist

gnuplot mstch.gpi -persist

./table.exe postproc/data_t_q.txt

./table.exe postproc/data_t_s.txt
