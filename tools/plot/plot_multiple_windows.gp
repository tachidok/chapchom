set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
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

plot 'data_plot_multiple_windows.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'data_plot_multiple_windows.dat' using 1:3 title 'Predator' w linespoints ls 2

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

plot 'data_plot_multiple_windows.dat' using 2:3 w linespoints ls 1
