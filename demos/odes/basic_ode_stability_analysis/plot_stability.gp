# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb 'red' lt 1 lw 2 pt 5 ps 0.6   # --- red
set style line 2 lc rgb 'blue' lt 1 lw 2 pt 7 ps 0.6   # --- blue
set style line 3 lc rgb 'green' lt 1 lw 2 pt 9 ps 0.6   # --- green
set style line 4 lc rgb 'violet' lt 1 lw 2 pt 11 ps 0.6   # --- violet
set style line 5 lc rgb 'orange' lt 1 lw 2 pt 13 ps 0.6   # --- orange
set style line 6 lc rgb 'cyan' lt 1 lw 2 pt 15 ps 0.6   # --- cyan
set style line 7 lc rgb 'yellow' lt 1 lw 2 pt 3 ps 0.6   # --- yellow
set style line 8 lc rgb 'pink' lt 1 lw 2 pt 2 ps 0.6   # --- pink
set style line 9 lc rgb 'black' lt 1 lw 2 pt 1 ps 0.6   # --- black
set style line 10 lc rgb 'dark-green' lt 2 lw 1 pt 64 ps 0.6   # --- dark-green
set style line 11 lc rgb 'brown' lt 1 lw 2 pt 65 ps 0.6   # --- brown

# Legend
set key bottom right

set grid

set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_current.png'

#set xrange [0:500]
#set yrange [0:40]
set title 'Absolute error as a function of the step size h'
set xlabel 'h'
set ylabel 'e(h)'
set tics scale 0.75
set logscale x
set logscale y

plot 'RESLT/euler_stability.dat' using 1:2 title 'Euler' w linespoints ls 1, \
     'RESLT/rk4_stability.dat' using 1:2 title 'RK4' w linespoints ls 2, \
     'RESLT/am2pc_stability.dat' using 1:2 title 'AM2-PC' w linespoints ls 3, \
     'RESLT/bdf1_stability.dat' using 1:2 title 'BDF1' w linespoints ls 4, \
     'RESLT/am2_stability.dat' using 1:2 title 'AM2' w linespoints ls 5
#'RESLT/bdf2_stability.dat' using 1:2 title 'BDF2' w linespoints ls 6

