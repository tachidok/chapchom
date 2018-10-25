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

set terminal wxt 0 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'euler.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'euler.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 1 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'euler.dat' using 2:3 w linespoints ls 1

set terminal wxt 2 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'rk4.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'rk4.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 3 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'rk4.dat' using 2:3 w linespoints ls 1

set terminal wxt 4 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'am2pc.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'am2pc.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 5 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'am2pc.dat' using 2:3 w linespoints ls 1

set terminal wxt 6 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'bdf1.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'bdf1.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 7 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'bdf1.dat' using 2:3 w linespoints ls 1

set terminal wxt 8 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'am2.dat' using 1:2 title 'Prey' w linespoints ls 1, \
     'am2.dat' using 1:3 title 'Predator' w linespoints ls 2

set terminal wxt 9 size 640,480 enhanced font 'Verdana,10' persist
#set terminal pngcairo size 640,480 enhanced font 'Verdana,10'
#set output 'deb.png'

#set xrange [0:500]
#set yrange [0:40]
set xlabel 'Time (t)'
set ylabel '# of individuals'
set tics scale 0.75

plot 'am2.dat' using 2:3 w linespoints ls 1

