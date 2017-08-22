set terminal wxt size 640,480 enhanced font 'Verdana,10' persist

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5   # --- red

plot 'deb_file.dat' using 1:2 w linespoints ls 1
