reset
set size 1,1
set multiplot
#set terminal wxt size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.3   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 0.3   # --- red

# First plot -------------------------------------------------------

# Legend
set key top right
# Set size for first plot (width and height, normalised)
set size 0.5,1
# The position of the plot
set origin 0,0

set grid
set xrange [0:40]
set yrange [0:6]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75
set title 'Runge-Kutta time plot'

plot 'soln0_runge_kutta.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'soln0_runge_kutta.dat' using 1:3 title 'Predator' w linespoints ls 2

# Second plot
unset key
# Set size for first plot (width and height, normalised)
set size 0.5,1
# The position of the plot
set origin 0.5,0

set grid
set xrange [0:6]
set yrange [0:4]
set xlabel '# of prey'
set ylabel '# of predators'
set tics scale 0.75
set title 'Runge-Kutta phase plot'

plot 'soln0_runge_kutta.dat' using 2:3 w linespoints ls 1

unset multiplot
