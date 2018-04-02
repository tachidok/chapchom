set terminal wxt size 640,480 enhanced font 'Verdana,10' persist

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.1   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 1 pt 5 ps 0.1   # --- red
set style line 3 lc rgb 'violet' lt 1 lw 1 pt 5 ps 0.1   # --- violet

set xlabel 'Time (s)'
set ylabel 'Radians'
set grid

plot '../RESLT/roll_pitch_yaw.dat' using 1:2 title 'roll' with linespoints ls 1, \
     '../RESLT/roll_pitch_yaw.dat' using 1:3 title 'pitch' with linespoints ls 2, \
     '../RESLT/roll_pitch_yaw.dat' using 1:4 title 'yaw' with linespoints ls 3

#plot '../RESLT/velocity.dat' using 1:2 title 'x-velocity' with linespoints ls 1, \
#'../RESLT/velocity.dat' using 1:3 title 'y-velocity' with linespoints ls 2

set terminal png size 640,480 enhanced font 'Verdana,10'
set output "euler_angles.png"
replot
