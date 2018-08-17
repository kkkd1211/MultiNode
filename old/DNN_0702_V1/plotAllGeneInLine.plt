set term gif animate
set yrange [0:1]
set output 'O.gif'
do for [i=1:55]{
set title sprintf("%d",i)
plot \
'gene0_P.txt'  u i w l lw 2 lt -1 lc 7  t 'kni',\
'gene1_P.txt'   u i w l lw 2 lt -1 lc 22 t 'hb',\
'gene2_P.txt'   u i w l lw 2 lt -1 lc 26 t 'kr',\
'gene3_P.txt'   u i w l lw 2 lt -1 lc 27 t 'gt',\
'bcd_P.txt'  u 1 w l lw 1 lt -1 lc -1 t 'bcd data' ,\
'cad_P.txt'  u 1 w l lw 1 lt -1 lc 0  t 'cad data' ,\
'tll_P.txt'  u 1 w l lw 1 lt -1 lc 24 t 'tll data'  
}




