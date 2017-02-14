function [distancia,angulo] = norma_coordenadas(LATA,LonA,LATB,LonB)
 
 R=6378137*0+6378000; %%radio de la Tierra
 LATA=LATA*pi/180;
 LATB=LATB*pi/180;
 LonA=LonA*pi/180;
 LonB=LonB*pi/180;
 
 %%ecuaciones 
dlon = (LonB - LonA);
dlat = (LATB - LATA);

a = (sin(dlat/2))^2 + cos(LATA) * cos(LATB) * (sin(dlon/2))^2;
c = 2 * atan2( sqrt(a), sqrt(1-a) );
distancia = R * c;
 
X=cos(LATB)*sin(dlon);
Y=cos(LATA)*sin(LATB)-sin(LATA)*cos(LATB)*cos(dlon);

angulo=180/pi*atan2(X,Y);