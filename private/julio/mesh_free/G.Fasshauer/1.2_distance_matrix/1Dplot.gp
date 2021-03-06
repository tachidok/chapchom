# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb 'red' lt 1 lw 2 pt 5 ps 0.3   # --- red
set style line 2 lc rgb 'blue' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 3 lc rgb 'green' lt 1 lw 2 pt 9 ps 0.3   # --- green
set style line 4 lc rgb 'violet' lt 1 lw 2 pt 11 ps 0.3   # --- violet
set style line 5 lc rgb 'orange' lt 1 lw 2 pt 13 ps 0.3   # --- orange
set style line 6 lc rgb 'cyan' lt 1 lw 2 pt 15 ps 0.3   # --- cyan
set style line 7 lc rgb 'yellow' lt 1 lw 2 pt 3 ps 0.3   # --- yellow
set style line 8 lc rgb 'pink' lt 1 lw 2 pt 2 ps 0.3   # --- pink
set style line 9 lc rgb 'black' lt 1 lw 2 pt 1 ps 0.3   # --- black
set style line 10 lc rgb 'dark-green' lt 1 lw 2 pt 64 ps 0.3   # --- dark-green
set style line 11 lc rgb 'brown' lt 1 lw 2 pt 65 ps 0.3   # --- brown

# Legend
set key top right

set grid

set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'Current.png'

set title "My 1D plot"
#set xrange [0:500]
#set yrange [0:40]
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'output.dat' using 1:2 title 'output.dat' w linespoints ls 1

