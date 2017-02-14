function [new_lat new_lon]=suma_dist2coord(lat,lon,distancia,angulo)

 %Radio de la tierra
 R=6378137+6378000*0;
 
 lat1= lat*pi/180;
 lon1=lon*pi/180;
 angulo_rad=angulo*pi/180;
 
 %Calculo
 
new_lat = 180/pi*asin( sin(lat1)* cos(distancia / R) + cos(lat1)* sin(distancia/R)* cos(angulo_rad) );
new_lon=  (lon1 + atan2( sin(angulo_rad)* sin(distancia / R)* cos(lat1),cos(distancia/R)- sin(lat1)* sin(new_lat)))*180/pi;


