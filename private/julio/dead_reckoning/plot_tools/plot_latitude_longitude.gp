set terminal wxt size 640,480 enhanced font 'Verdana,10' persist

# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 lc rgb 'blue' lt 1 lw 1 pt 7 ps 0.1   # --- blue
set style line 2 lc rgb 'red' lt 1 lw 1 pt 5 ps 0.1   # --- red

set xlabel 'Longitude (d)'
set ylabel 'Latitude (d)'
set grid

#plot '../RESLT/latitude_and_longitude.dat' using ($2*pi)/180.0:($3*pi)/180.0 title 'Trajectory' with linespoints ls 1
plot [-98.295:-98.255] [19.03:19.06] '../RESLT/latitude_and_longitude.dat' using 3:2 title 'Trajectory' with linespoints ls 1

set terminal png size 640,480 enhanced font 'Verdana,10'
set output "latitude_and_longitude.png"
replot
