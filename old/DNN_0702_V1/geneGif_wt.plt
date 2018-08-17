set term gif animate
set yrange [0:1.1]
set output 'geneProfile.gif'
do for [i=1:55]{
set title sprintf("%d",i)
plot \
'geneExpression_P.txt' u i w l lw 2 lc -1 t 'Gene',\
'../../../../data_P/wt/kni_P.txt'  u i w l lw 1 lt 0 lc 7  t 'kni data',\
'../../../../data_P/wt/hb_P.txt'   u i w l lw 1 lt 0 lc 22  t 'hb data',\
'../../../../data_P/wt/kr_P.txt'   u i w l lw 1 lt 0 lc 26 t ' kr data',\
'../../../../data_P/wt/gt_P.txt'   u i w l lw 1 lt 0 lc 27 t ' gt data',\
'../../../../data_P/wt/bcd_P.txt'  u i w l lw 1 lt 0 lc -1 t 'bcd data' ,\
'../../../../data_P/wt/cad_P.txt'  u i w l lw 1 lt 0 lc 0  t 'cad data' ,\
'../../../../data_P/wt/tll_P.txt'  u i w l lw 1 lt 0 lc 24 t 'tll data'  
}




