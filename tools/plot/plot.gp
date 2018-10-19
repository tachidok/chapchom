set terminal wxt size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.0   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.0   # --- red

# Legend
set key top right

set grid
#set xrange [0:500]
#set yrange [0:40]
set xlabel 'x'
set ylabel 'f(x)'
set tics scale 0.75

plot 'plot_data.dat' using 1:2 title 'Original' w linespoints ls 1, \
     'plot_data.dat' using 1:3 title 'Cubix approximation' w linespoints ls 2
