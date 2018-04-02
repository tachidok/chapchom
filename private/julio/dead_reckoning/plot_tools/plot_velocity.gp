set terminal wxt size 640,480 enhanced font 'Verdana,10' persist

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.1   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 1 pt 5 ps 0.1   # --- red

set xlabel 'Time (s)'
set ylabel 'Velocity km/h'
set grid

plot '../RESLT/velocity.dat' using 1:($2*3.6) title 'x-velocity' with linespoints ls 1, \
     '../RESLT/velocity.dat' using 1:($3*3.6) title 'y-velocity' with linespoints ls 2

#plot '../RESLT/velocity.dat' using 1:2 title 'x-velocity' with linespoints ls 1, \
#'../RESLT/velocity.dat' using 1:3 title 'y-velocity' with linespoints ls 2

set terminal png size 640,480 enhanced font 'Verdana,10'
set output "velocity.png"
replot
