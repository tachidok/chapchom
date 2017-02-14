function [new_lat, new_lon, Error]=calc_nav(lat,lon,distancia,rumbo_inicial,var_rumbo)

%var_rumbo variacion relativa de rumbo

L=length(lat);


lat_origen =lat(1);  %Inicialización de navegación primera coordenada 
lon_origen =lon(1);  %desde la cual comenzará el cálculo

Error=zeros(L,1);
new_lat=zeros(L,1);
new_lon=zeros(L,1);

for i=1:length(distancia)

 %%calcula nuevo punto a partir de distancia y rumbo   
[new_lat(i),new_lon(i)]=suma_dist2coord(lat_origen,lon_origen,distancia(i),rumbo_inicial+var_rumbo(i));

lat_origen=new_lat(i); %reinicia el punto origen
lon_origen=new_lon(i);

% calcula distancia y rumbo entre dos coordenadas para estimación de error
[Error(i) angulo]= norma_coordenadas(lat(i),lon(i),new_lat(i),new_lon(i));


end

