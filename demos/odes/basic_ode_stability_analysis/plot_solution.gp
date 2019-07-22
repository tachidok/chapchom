# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb 'red' lt 1 lw 1 pt 5 ps 0.1   # --- red
set style line 2 lc rgb 'blue' lt 1 lw 1 pt 7 ps 0.1   # --- blue
set style line 3 lc rgb 'green' lt 1 lw 1 pt 9 ps 0.1   # --- green
set style line 4 lc rgb 'violet' lt 1 lw 1 pt 11 ps 0.1   # --- violet
set style line 5 lc rgb 'orange' lt 1 lw 1 pt 13 ps 0.1   # --- orange
set style line 6 lc rgb 'cyan' lt 1 lw 1 pt 15 ps 0.3   # --- cyan
set style line 7 lc rgb 'yellow' lt 1 lw 1 pt 3 ps 0.3   # --- yellow
set style line 8 lc rgb 'pink' lt 1 lw 1 pt 2 ps 0.3   # --- pink
set style line 9 lc rgb 'black' lt 1 lw 1 pt 1 ps 0.3   # --- black
set style line 10 lc rgb 'dark-green' lt 1 lw 1 pt 64 ps 0.3   # --- dark-green
set style line 11 lc rgb 'brown' lt 1 lw 1 pt 65 ps 0.3   # --- brown

# Legend
set key top right

set grid

set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_current.png'

#set xrange [0:500]
#set yrange [0:40]
set title 'Euler solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/euler_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/euler_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/euler_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/euler_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/euler_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5

set terminal wxt 1 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_velocity.png'

set key top right
#set xrange [0:500]
#set yrange [0:40]
set title 'Runge-Kutta 4 solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/rk4_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/rk4_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/rk4_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/rk4_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/rk4_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5

set terminal wxt 2 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_density.png'

set key top right
#set xrange [0:500]
#set yrange [0:40]
set title 'Adams-Moulton 2 - Predictor-Corrector solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/am2pc_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/am2pc_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/am2pc_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/am2pc_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/am2pc_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5

set terminal wxt 3 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_current.png'

#set xrange [0:500]
#set yrange [0:40]
set title 'BDF1 solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/bdf1_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/bdf1_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/bdf1_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/bdf1_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/bdf1_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5

set terminal wxt 4 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_current.png'

#set xrange [0:500]
#set yrange [0:40]
set title 'Adams-Moulton 2 solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/am2_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/am2_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/am2_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/am2_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/am2_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5

set terminal wxt 5 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'alpha_vs_current.png'

#set xrange [0:500]
#set yrange [0:40]
set title 'BDF2 solution'
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'RESLT/bdf2_h_0.1.dat' using 1:2 title 'h = 1.0e-1' w linespoints ls 1, \
     'RESLT/bdf2_h_0.01.dat' using 1:2 title 'h = 1.0e-2' w linespoints ls 2, \
     'RESLT/bdf2_h_0.001.dat' using 1:2 title 'h = 1.0e-3' w linespoints ls 3, \
     'RESLT/bdf2_h_0.0001.dat' using 1:2 title 'h = 1.0e-4' w linespoints ls 4, \
     'RESLT/bdf2_h_1e-05.dat' using 1:2 title 'h = 1.0e-5' w linespoints ls 5
