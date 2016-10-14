/** \file This file implements the CCNMEADecoder class
 */
#include "cc_nmea_decoder.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor, establish the maximum size of the nmea string and
 // the size of the checksum
 // ===================================================================
 CCNMEADecoder::CCNMEADecoder(const unsigned max_fields,
                              const unsigned max_fields_size,
                              const unsigned checksum_size)
  : Max_fields(max_fields), Max_fields_size(max_fields_size),
    Max_nmea_string_size(max_fields*max_fields_size), Checksum_size(checksum_size)
 {
    
  // Resize the transition matrix
  const unsigned n_states = 6;
  const unsigned n_transitions = 15;
  State_machine_transitions.resize(n_states);
  for (unsigned i = 0; i < n_states; i++)
   {
    // Allocate space for the number of transitions for each state
    State_machine_transitions[i].resize(n_transitions);
   }
  
  // The transition matrix
  unsigned transition_matrix[] =
   {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
  
  // Copy the "transition_matrix" into the "State_machine_transitions"
  // structure
  unsigned k = 0;
  for (unsigned i = 0; i < n_states; i++)
   {
    for (unsigned j = 0; j < n_transitions; j++)
     {
      State_machine_transitions[i][j] = transition_matrix[k++];
     } // for (j < n_transitions)
    
   } // for (i < n_states)

  // Resize to the maximum number of allowed fields
  Fields.resize(max_fields);
  // Allocate memory for entries in the Fields matrix
  for (unsigned i = 0; i < max_fields; i++)
   {
    Fields[i] = new char[max_fields_size];
   }
  
  // Initialise/reset state machine
  reset_state_machine();
  // Establish the final state
  Final_state = 5;
  
 }

 // ===================================================================
 // Destructor (release allocated memory)
 // ===================================================================
 CCNMEADecoder::~CCNMEADecoder()
 {
  // Free memory allocated for entries in the Fields matrix
  for (unsigned i = 0; i < Max_fields; i++)
   {
    delete Fields[i];
   }
  
  // Clear all entries in the vector
  Fields.clear();
  
 }

 // ===================================================================
 // Initialise any variables (of the state machine). This method is
 // called any time a non-valid nmea string is identified
 // ===================================================================
 void CCNMEADecoder::reset_state_machine()
 {
  // Reset number of fields variables
  Total_number_of_fields = 0;
  Counter_n_current_fields = 0;
  // Reset state information of the state machine
  Current_state = 0;
  Last_state = 0;
  // Initialise the number of read characters
  Counter_n_read_characters = 0;
  // Reset checksum
  Computed_checksum = 0;
  
  // Clean fields
  clean_fields_matrix();
  
 }

 // ===================================================================
 // Clean-up any info. stored in the Fields matrix
 // ===================================================================
 void CCNMEADecoder::clean_fields_matrix()
 {
  // Loop over the fields and fill with zeroes
  for (unsigned i = 0; i < Max_fields; i++)
   {
    memset(Fields[i], 0, Max_fields_size);
   }
  
  // Clean the stored checksum as well
  Input_checksum.clear();
  
 }
 
 // ===================================================================
 // Eats a character, validates the character as part of an nmea
 // string and stores its entry in a matrix structure containing the
 // parsed information
 // ===================================================================
 void CCNMEADecoder::parse(const unsigned char character)
 {
  
 }
 
 // ===================================================================
 // Fill the corresponding data structure based on the parsed nmea
 // string
 // ===================================================================
 void CCNMEADecoder::fill_structure()
 {
  
 }

}
 
#if 0
 
 
 
#include "CNmeaParser.h"
 
CNmeaParser::CNmeaParser(): dqBlock(dqBlock_Z) {

	int i, j;
        contradar=0;
	//////////////////////////////////////////////////////////////////////////////

	numeroCampos = 0;
	checksum = 0;
	contadorCampo = 0;
	contadorEntrada = 0;
	
	ttm_state = false;
	ttm_prev_state = false;
	block_received = false;
	switch_deque = true;

	for (i = 0;i < CNMEA_MAX_CAMPOS;i++)
		memset(campos[i],'\0',CNMEA_CAMPO_SIZE); //limpiar los campos almacenados

	memset(cadenaChecksum,'\0',CNMEA_CHECKSUM_SIZE); //limpiar la cadena de checksum

	//////////////////////////////////////////////////////////////////////////////

	estadoActual = 0;
	estadosFinales[0] = 5;
	int datosMatrizAutomata[] = {	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,
			0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,
			0, 0, 1, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int contadorMatriz = 0;

	for (i = 0;i < 6;i++)
		for (j = 0;j < 15;j++){
			matrizAutomata[i][j] = datosMatrizAutomata[contadorMatriz];
			contadorMatriz++;
		}

        emva.state_man_rum_barco = true;
        emva.state_man_dir_viento = true;
        emva.state_man_Vel_viento = true;
        emva.state_man_humedad = true;
        emva.state_man_Vel_barco = true;
        inf.tempValido = true;
        inf.humedadValido = true;
        emva.temperatura=32;
        emva.presion= 1500;
        this->pesoProyectil = 2.8;
        velProyectil = 950;
        cadencia = 1;
	nuevoDatoLaser=0;
/*
        SInfoTargets tempRadar;

        tempRadar.bearing=30;
        tempRadar.distancia=15;
        tempRadar.velocidad=5;
        dqBlock.push_back(tempRadar);

        tempRadar.bearing=60;
        tempRadar.distancia=15;
        tempRadar.velocidad=10;
        dqBlock.push_back(tempRadar);

        tempRadar.bearing=90;
        tempRadar.distancia=15;
        tempRadar.velocidad=15;
        dqBlock.push_back(tempRadar);


        tempRadar.bearing=120;
        tempRadar.distancia=15;
        tempRadar.velocidad=20;
        dqBlock.push_back(tempRadar);

        tempRadar.bearing=150;
        tempRadar.distancia=15;
        tempRadar.velocidad=25;
        dqBlock.push_back(tempRadar);

        tempRadar.bearing=180;
        tempRadar.distancia=15;
        tempRadar.velocidad=35;
        tempRadar.curso=8;
        dqBlock.push_back(tempRadar);*/
}

CNmeaParser::~CNmeaParser() {
	// TODO Auto-generated destructor stub
}

void CNmeaParser::iniciarVariables()
{

	int i;

	numeroCampos = 0;
	checksum = 0;
	contadorCampo = 0;
	contadorEntrada = 0;

	for (i = 0;i < CNMEA_MAX_CAMPOS;i++)
		memset(campos[i],'\0',CNMEA_CAMPO_SIZE); //limpiar los campos almacenados

	memset(cadenaChecksum,'\0',CNMEA_CHECKSUM_SIZE); //limpiar la cadena de checksum

}

int CNmeaParser::parse(unsigned char caracter)
{

	estadoAnterior = estadoActual;
	contadorEntrada++;
        //fprintf(stderr, "%c", caracter);
	if (contadorEntrada >= CNMEA_MAX_STR_SIZE){
		iniciarVariables();
		estadoActual = 0;
		return 1;
	}

	if (caracter <= 0x1F) //(unit separator)
		estadoActual = matrizAutomata[estadoActual][0];
	else if ((0x20 <= caracter) && (caracter <= 0x23)){ //(space), !, ", #
		estadoActual = matrizAutomata[estadoActual][1];
	}
	else if (caracter == 0x24){//$
		if (estadoActual != 0)
			iniciarVariables(); //limpiar todas las variables
		estadoActual = matrizAutomata[estadoActual][2];
	}
	else if ((0x25 <= caracter) && (caracter <= 0x29))//%, &, ', (, )
		estadoActual = matrizAutomata[estadoActual][3];
	else if (caracter == 0x2A)//*
		estadoActual = matrizAutomata[estadoActual][4];
	else if (caracter == 0x2B)//+
		estadoActual = matrizAutomata[estadoActual][5];
	else if (caracter == 0x2C)//, (coma)
		estadoActual = matrizAutomata[estadoActual][6];
	else if ((0x2D <= caracter) && (caracter <= 0x2F))//-,.,/
		estadoActual = matrizAutomata[estadoActual][7];
	else if ((0x30 <= caracter) && (caracter <= 0x39))//0,1,...,9
		estadoActual = matrizAutomata[estadoActual][8];
	else if ((0x3A <= caracter) && (caracter <= 0x40))//:, ;, <, =, >, ?, @
		estadoActual = matrizAutomata[estadoActual][9];
	else if ((0x41 <= caracter ) && (caracter <= 0x46))//A, B, C, D, E, F
		estadoActual = matrizAutomata[estadoActual][10];
	else if ((0x47 <= caracter ) && (caracter <= 0x60))//G, H, I,..., X, Y, Z, [, \, ], ^, _, `
		estadoActual = matrizAutomata[estadoActual][11];
	else if ((0x61 <= caracter ) && (caracter <= 0x66))//a, b, c, d, e, f
		estadoActual = matrizAutomata[estadoActual][12];
	else if ((0x67 <= caracter) && (caracter <= 0x7E))//g, h, i,...,x, y, z, {, |, }, ~
		estadoActual = matrizAutomata[estadoActual][13];
	else if ((0x7F <= caracter ) && (caracter <= 0xFF))//(extended ASCII)
		estadoActual = matrizAutomata[estadoActual][14];


	if (estadoActual == 0)
		iniciarVariables();

	if (estadoActual == 2){ //se termino un campo, empezar a avanzar al siguiente
		campos[numeroCampos][contadorCampo] = 0;
		numeroCampos++;
		contadorCampo = 0;


                if ((strcmp(campos[0],"WIMWV") == 0)&&(numeroCampos==5))
                {
                    strcpy(campos[5],"R");
                    //fprintf(stderr, "%s-%s-%s-%s-%s-%s*\n", campos[0], campos[1],campos[2], campos[3], campos[4], campos[5]);
                    //inf.numeroCampos = numeroCampos;
                    //inf.decodifica(campos);
                        //inf.print();
                    mwv.numeroCampos = numeroCampos;
                    mwv.decodifica(campos);

                }

	}

	if (estadoActual == 4){ //se obtuvo el primer caracter del checksum
		numeroCampos++;
		cadenaChecksum[0] = caracter;
	}
	if (estadoActual == 5) //se obtuvo el segundo caracter del checksum
		cadenaChecksum[1] = caracter;

	if ((estadoActual == 1) && (caracter != 0x24)){//$
		campos[numeroCampos][contadorCampo] = caracter;
		contadorCampo++;
	}

	if ((caracter != 0x24) && ((estadoActual == 1) || (estadoActual == 2)))//$
		checksum ^= caracter;

	if (estadoActual == estadosFinales[0]){ //Si el estado actual es un estado final
		//verificar el checksum obtenido
		char cadenaChecksumCalculado[CNMEA_CHECKSUM_SIZE];
		sprintf(cadenaChecksumCalculado,"%02X",checksum);

		//if (stricmp(cadenaChecksumCalculado,cadenaChecksum)!=0){
                if (strcmp(cadenaChecksumCalculado,cadenaChecksum)!=0){
			estadoActual = 0;
			iniciarVariables();//checksum INCORRECTO, regresar al estado inicial
			return 1;
                }

		verificarMensaje(numeroCampos);


	}


	return 1;
}
//TODO:zapo corrige!!! aqui
int CNmeaParser::verificarMensaje(int dummy)
{

		ttm_state = false;
                //fprintf (stderr, "NMEA: %s\n", campos[0]);
		//verificar cual fue el tipo de mensaje que se obtuvo
		if (strcmp(campos[0],"GMINF") == 0){
		    inf.numeroCampos = numeroCampos;
			inf.decodifica(campos);
			//inf.print();
		}
		else if (strcmp(&(campos[0][2]),"TTM") == 0){
			ttm.numeroCampos = numeroCampos;
			ttm.decodifica(campos);
			//ttm.print();
			ttm_state = true;
		}
		else if (strcmp(&(campos[0][2]),"VTG") == 0){
			vtg.numeroCampos = numeroCampos;
			vtg.decodifica(campos);
			//vtg.print();
		}
		else if (strcmp(&(campos[0][2]),"VHW") == 0){
			vhw.numeroCampos = numeroCampos;
			vhw.decodifica(campos);
			//vhw.print();
		}
		else if (strcmp(&(campos[0][2]),"HDT") == 0){
			hdt.numeroCampos = numeroCampos;
			hdt.decodifica(campos);
			//hdt.print();
		}
		else if (strcmp(&(campos[0][2]),"GLL") == 0){
			gll.numeroCampos = numeroCampos;
			gll.decodifica(campos);
			//gll.print();
		}
		else if (strcmp(&(campos[0][2]),"GGA") == 0){
			gga.decodifica(campos);
			//gga.print();
		}
		else if (strcmp(&(campos[0][2]),"VBW") == 0){
			vbw.numeroCampos = numeroCampos;
			vbw.decodifica(campos);
			//vbw.print();
		}
		else if (strcmp(&(campos[0][2]),"RMC") == 0){
			rmc.numeroCampos = numeroCampos;
			rmc.decodifica(campos);
			//rmc.print();
		}
		else if (strcmp(&(campos[0][2]),"MWV") == 0){
			mwv.numeroCampos = numeroCampos;
			mwv.decodifica(campos);
			//mwv.print();
		}
		else if (strcmp(&(campos[0][2]),"MWD") == 0){
			mwd.numeroCampos = numeroCampos;
			mwd.decodifica(campos);
			//mwd.print();
		}
		else if (strcmp(&(campos[0][2]),"XDR") == 0){
			xdr.numeroCampos = numeroCampos;
			xdr.decodifica(campos);
			//xdr.print();
		}
				
		saveInformationTargets();
		ttm_prev_state = ttm_state;

		return 1;

}

void CNmeaParser::saveInformationTargets()
{

	block_received = false;

	if (ttm_state == false && ttm_prev_state == true){

		block_received = true;
                contradar=0;

		if (switch_deque == true)
			dqBlock = dqBlock_A;
		else
			dqBlock = dqBlock_Z;

		switch_deque = !switch_deque;

	}
	else if (ttm_state == true && ttm_prev_state == false){

		if (switch_deque == true)
		  dqBlock_A.clear();
		else
		  dqBlock_Z.clear();

	}

	if (ttm_state == true){

		SInfoTargets tempRadar;

		tempRadar.bearing = 0;
		tempRadar.distancia = 0;
		tempRadar.unidadesBearing = 0;
		tempRadar.estadoObjetivo = 0;
		tempRadar.numeroObjetivo = 0;
		tempRadar.tipoAdquisicion = 0;

		if (ttm.bearingValido == true)
			tempRadar.bearing = ttm.bearing;
		if (ttm.distanciaValido == true)
			tempRadar.distancia = ttm.distancia;
		if (ttm.unidadesBearingValido == true)
			tempRadar.unidadesBearing = ttm.unidadesBearing;
		if (ttm.estadoObjetivoValido == true)
			tempRadar.estadoObjetivo = ttm.estadoObjetivo;
		if (ttm.numeroObjetivoValido == true)
			tempRadar.numeroObjetivo = ttm.numeroObjetivo;
		if (ttm.tipoAdquisicionValido == true)
			tempRadar.tipoAdquisicion = ttm.tipoAdquisicion;
	    if (ttm.velocidadValido == true)
            tempRadar.velocidad = ttm.velocidad;
        if (ttm.cursoValido == true)
            tempRadar.curso = ttm.curso;
            
		//tempRadar.heading = heading;


		if (switch_deque == true)
			dqBlock_A.push_back(tempRadar);
		else
			dqBlock_Z.push_back(tempRadar);

	}

}

/* Nuevo */
double CNmeaParser::getvelocidadViento()
{

    if( emva.state_man_Vel_viento == true ) {
        if ( inf.velVientoValido == true )
               return inf.velViento;
        else if( mwd.valid_wind_speedK == true )
               return (mwd.wind_speedK  / 1.852);
        else if( mwd.valid_wind_speedM == true )
               return (mwd.wind_speedM / 0.514444);
        else if( mwv.valid_wind_speed == true ) {

                if( mwv.valid_speed_units == true ) {

                        switch( mwv.speed_units ){
                                case 0: // K
                                        return (mwv.wind_speed / 1.852);
                                        break;
                                case 1: // M
                                        return (mwv.wind_speed / 0.514444);
                                        break;
                                case 2: // N
                                        return (mwv.wind_speed);
                                        break;
                                default: // valor por omision
                                        return 120;
                                break;

                        }
            }
        }
       else
            return 0.0;
    }
    else
        return emva.velocidadViento;

}

double CNmeaParser::getDireccionViento()
{
    if( emva.state_man_dir_viento == true ){
         if( inf.dirVientoValido == true )
                 return (inf.dirViento);
         else if(mwd.valid_wind_directionT == true)
                return (mwd.wind_directionT);
         else  if(mwv.valid_wind_angle == true){
                        if(mwv.valid_reference == true)
                        {
                                if( mwv.reference == 1 )
                                        return (mwv.wind_angle);
                                else if ( hdt.headingValido )
                                        return (mwv.wind_angle + hdt.heading);
                        }
         }
         else if( mwd.valid_wind_directionM == true )
                return (mwd.wind_directionM);

         else
              return 0.0;
    }
    else
        return emva.direccionViento;
}

double CNmeaParser::getTemperatura()
{
    if( emva.state_man_temperatura == true ){
        if( inf.tempValido == true )
               return (inf.temp);
        else if( xdr.valid_temperature == true )
               return ( xdr.temperature );
        else
             return 0.0;
    }
    else
        return emva.temperatura;
}

double CNmeaParser::getPresion()
{
    if( emva.state_man_presion == true ){
        if( inf.presionValido == true)
                  return (inf.presion);
        else if(xdr.valid_pressure == true)
                  return (xdr.pressure);
        else
             return 0.0;
    }
    else
        return emva.presion;
}

double CNmeaParser::getHumedad()
{
    if( emva.state_man_humedad == true){

        if( inf.humedadValido == true )
                return ( inf.humedad );
        else if( xdr.valid_humidity == true )
                return ( xdr.humidity);
        else
             return 0.0;
    }
    else
        return emva.humedad;
}

double CNmeaParser::getLatitud()
{
    
        if(gga.latitudValido == true )
            return (gga.latitud);
        else if( gll.latitudValido == true )
            return (gll.latitud);
        else if( rmc.latitudValido == true )
            return (rmc.latitud);
        else
             return 0.0;
}


int CNmeaParser::getNS()
{
       if ( gga.latitudDireccionValido ==  true ){
		return gga.latitudDireccion;
	  }
       else if ( gll.dirLatitudValido == true ){
		return gll.dirLatitud;
	  }
       else if( rmc.dirLatitudValido == true ){
		return rmc.dirLatitud;
	 }
}

double CNmeaParser::getLongitud()
{
    
        if( gga.longitudValido == true )
            return (gga.longitud);
        else if( gll.longitudValido == true )
            return (gll.longitud);
        else if( rmc.longitudValido == true )
            return (rmc.longitud);
        else
             return 0.0;
}

int CNmeaParser::getEO()
{
	if ( gga.longitudDireccionValido == true ){
		return gga.longitudDireccion;
	}
	else if ( gll.dirLongitudValido == true ){
		return gll.dirLongitud;
	}
	else if ( rmc.dirLongitudValido == true){
		return rmc.dirLongitud;
	}
}



double CNmeaParser::getRumboBarco()
{

        //emva.rumboBarco+=.015;
        //if (emva.rumboBarco>360) emva.rumboBarco=0;

    if( emva.state_man_rum_barco == true ){
        if( hdt.headingValido == true )
            return (-hdt.heading);
        else if ( vhw.rumboVerdaderoValido == true)
            return (-vhw.rumboVerdadero);
        else if( vtg.cursoVerdaderoValido == true )
            return (-vtg.cursoVerdadero);
        else
             return 0.0;
    }
   else
        return -emva.rumboBarco;
}

double CNmeaParser::getVelocidadBarco()
{
    if( emva.state_man_Vel_barco == true ){
        if( inf.sogValido == true )
            return ( inf.sog );
        else if( vtg.velocidadNudosValido == true )
            return ( vtg.velocidadNudos );
        else if ( vhw.velocidadNudosValido == true )
            return ( vhw.velocidadNudos );
        else if ( vtg.velocidadKmHValido == true )
            return ( vtg.velocidadKmH / 1.852 );
        else if ( vhw.velocidadKmHValido == true )
            return( vhw.velocidadKmH / 1.852 );
        else if( rmc.velLongAguaValido == true )
            return ( rmc.velLongAgua );
        else
             return 0.0;
    }
    else
        return emva.velocidadBarco;
}

double CNmeaParser::medirLaser( )
{
	//printf("apoco si?\n");
	laser.getDistance(&distanciaLaser, &nuevoDatoLaser);
}

string CNmeaParser::gethora()
{

	string hora;
	if(gll.horasValido==true && gll.minutosValido==true)
	{
		         
        ostringstream convert;
        ostringstream convert2;

        convert << gll.horas;
        convert2 << gll.minutos;  
           
		string Result; 
		string Result2;
		
        Result = convert.str();
        Result2 = convert2.str();

        hora = Result + ":" + Result2;
        
        return hora;

	}
	else if(gga.horasValido==true && gga.minutosValido==true)
	{
		ostringstream convert;
        ostringstream convert2;

        convert << gga.horas;
        convert2 << gga.minutos;  
           
		string Result; 
		string Result2;
		
        Result = convert.str();
        Result2 = convert2.str();

        hora = Result + ":" + Result2;
        
        return hora;
	}
	else if(rmc.horasValido==true && rmc.minutosValido==true)
	{
		ostringstream convert;
        ostringstream convert2;

        convert << rmc.horas;
        convert2 << rmc.minutos;  
           
		string Result; 
		string Result2;
		
        Result = convert.str();
        Result2 = convert2.str();

        hora = Result + ":" + Result2;
        
        return hora;
	}
	
}

void CNmeaParser::gethoraGTM(int *horas, int *minutos)
{

    *horas = 0;
    *minutos = 0;

    if(gll.horasValido==true && gll.minutosValido==true){
		       
        *horas = gll.horas;
        *minutos = gll.minutos;  
        
	}
	else if(gga.horasValido==true && gga.minutosValido==true)
	{
        *horas = gga.horas;
        *minutos = gga.minutos;  
           
	}
	else if(rmc.horasValido==true && rmc.minutosValido==true)
	{
        *horas = rmc.horas;
        *minutos = rmc.minutos;  
    }
}

#endif // #if 0
