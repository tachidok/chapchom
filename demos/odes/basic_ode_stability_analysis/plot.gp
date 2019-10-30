# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3   # --- red
set style line 3 lc rgb 'violet' lt 1 lw 2 pt 9 ps 0.3   # --- violet
set style line 4 lc rgb 'green' lt 1 lw 2 pt 11 ps 0.3   # --- green
set style line 5 lc rgb 'black' lt 1 lw 2 pt 13 ps 0.3   # --- black
set style line 6 lc rgb 'yellow' lt 1 lw 2 pt 13 ps 0.3   # --- yellow
set style line 7 lc rgb 'cyan' lt 1 lw 2 pt 13 ps 0.3   # --- cyan

u(x) = 1/(1+x)

# Legend
set key top right

set grid

set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel 'u'
set tics scale 0.75

plot 'euler_h_0.01.dat' using 1:2 title 'Euler' w linespoints ls 1, \
     'rk4_h_0.01.dat' using 1:2 title 'RK4' w linespoints ls 2, \
     'am2pc_h_0.01.dat' using 1:2 title 'AM2PC' w linespoints ls 3, \
     'bdf1_h_0.01.dat' using 1:2 title 'BDF1' w linespoints ls 4, \
     'am2_h_0.01.dat' using 1:2 title 'AM2' w linespoints ls 5, \
     'bdf2_h_0.01.dat' using 1:2 title 'BDF2' w linespoints ls 6, \
     u(x) title 'u(t)' with lines linestyle 7

set terminal wxt 1 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel 'error'
set tics scale 0.75

plot 'euler_error_h_0.01.dat' using 1:2 title 'Euler' w linespoints ls 1, \
     'rk4_error_h_0.01.dat' using 1:2 title 'RK4' w linespoints ls 2, \
     'am2pc_error_h_0.01.dat' using 1:2 title 'AM2PC' w linespoints ls 3, \
     'bdf1_error_h_0.01.dat' using 1:2 title 'BDF1' w linespoints ls 4, \
     'am2_error_h_0.01.dat' using 1:2 title 'AM2' w linespoints ls 5, \
     'bdf2_error_h_0.01.dat' using 1:2 title 'BDF2' w linespoints ls 6
