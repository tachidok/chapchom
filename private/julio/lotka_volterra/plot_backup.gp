set terminal wxt size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3   # --- red
set style line 3 lc rgb 'violet' lt 1 lw 2 pt 9 ps 0.3   # --- violet
set style line 4 lc rgb 'green' lt 1 lw 2 pt 11 ps 0.3   # --- green
set style line 5 lc rgb 'black' lt 1 lw 2 pt 13 ps 0.3   # --- black

# Legend
set key top right

set grid
#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'RESLT/soln0.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'RESLT/soln0.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 1 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3   # --- red

# Legend
set key top right

set grid
#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'RESLT/soln0.dat' using 2:3 w linespoints ls 1, \
     'RESLT/soln1.dat' using 2:3 w linespoints ls 2, \
     'RESLT/soln2.dat' using 2:3 w linespoints ls 3, \
     'RESLT/soln3.dat' using 2:3 w linespoints ls 4, \
     'RESLT/soln4.dat' using 2:3 w linespoints ls 5

set terminal wxt 2 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3   # --- red

# Legend
set key top right

set grid
#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'RK4/soln0.dat' using 2:3 w linespoints ls 1, \
     'RK4/soln1.dat' using 2:3 w linespoints ls 2, \
     'RK4/soln2.dat' using 2:3 w linespoints ls 3, \
     'RK4/soln3.dat' using 2:3 w linespoints ls 4, \
     'RK4/soln4.dat' using 2:3 w linespoints ls 5
