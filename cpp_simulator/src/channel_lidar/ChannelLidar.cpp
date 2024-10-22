/*-----------------------------------------------------------------------------
-- Proyecto      : Lidar PCM
-------------------------------------------------------------------------------
-- Archivo       : ChannelLidar.cpp
-- Organizacion  : Fundacion Fulgor
-- Fecha         : 13 de junio 2023
-------------------------------------------------------------------------------
-- Descripcion   : Canal de LiDAR Pulsado
-------------------------------------------------------------------------------
-- Autor         : Leandro Borgnino
-------------------------------------------------------------------------------
-- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
-------------------------------------------------------------------------------
-- $Id$
-------------------------------------------------------------------------------*/

#include "ChannelLidar.h"

/*----------------------------------------------------------------------------*/
ChannelLidar::ChannelLidar()
{
    
    printf("ChannelLidar :: Has been created\n");

};

/*----------------------------------------------------------------------------*/
ChannelLidar::~ChannelLidar(){};

/*----------------------------------------------------------------------------*/
int  ChannelLidar::init(loadSettings *params){
    /*!Se utiliza para realizar la carga de parametros y la configuracion 
      inicial de las variables*/
    LAMBDA0 = params->getParamAsDouble(string("global.LAMBDA0"));
    DEBUG_CH = params->getParamAsInt(string("global.DEBUG"));
    FS = params->getParamAsDouble(string("ChannelLidar.FS"));
    NOS = params->getParamAsInt(string("ChannelLidar.NOS"));
    ARX = params->getParamAsDouble(string("ChannelLidar.ARX"));
    
    return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> ChannelLidar::run(vector<double> channel_input, double range, double rho, double angle_inc)
{
  double delay = 2*range/LIGHT_SPEED;
  int delay_samples = delay*FS*NOS;

  double meas_delay = delay_samples/FS;
  double meas_range = meas_delay*LIGHT_SPEED/2;

  double power_gain  = cos(angle_inc)*rho*ARX/(4*PI*pow(meas_range,2));
  //double delta_phase = LIGHT_SPEED/LAMBDA0*meas_delay;

  if (DEBUG)
    {
      cout << "************************" << endl;
      cout << "*** Datos del Canal   **" << endl;
      cout << "************************" << endl;
      cout << "Channel Power Gain: " << power_gain << endl;
    }

  vector<double> channel_output = channel_input;
  
  // Multiplicación del vector por la ganancia del canal
  transform(channel_output.begin(), channel_output.end(), channel_output.begin(),
	    [&power_gain](double element) { return element *= sqrt(power_gain); });

  // Desplazamiento según el retardo
  // Warning: Posible bug porque es un shift circular
  //rotate(channel_output.begin(), channel_output.begin()+channel_output.size()-delay_samples, channel_output.end());
  channel_output.insert(channel_output.begin(), delay_samples, 0);
  channel_output.erase(channel_output.end() - delay_samples, channel_output.end());

  // Warning: Faltaría el desplazamiento de la fase por ahora solo real
  
  return channel_output;
}


/*----------------------------------------------------------------------------*/
vector<double> ChannelLidar::run(vector<double> channel_input, vector<double> range, vector<double> rho, double angle_inc)
{

  // Crear un vector de tamaño 'size' e inicializar todos los elementos a 0.0
  vector<double> channel_output(channel_input.size(), 0.0);

  for (unsigned int jj = 0; jj < range.size(); jj++)
    {

      vector<double> noise_vector;
      
      // Generador random
      unsigned seed = chrono::system_clock::now().time_since_epoch().count();
      const double mean = 0.0;
      const double stddev = 0.00000005;
      default_random_engine generator(seed);
      normal_distribution<double> dist(mean, stddev);
  
      double delay = 2*range[jj]/LIGHT_SPEED;
      int delay_samples = delay*FS*NOS;

      double meas_delay = delay_samples/FS;
      double meas_range = meas_delay*LIGHT_SPEED/2;

      double power_gain  = cos(angle_inc)*rho[jj]*ARX/(4*PI*pow(meas_range,2));
      //double delta_phase = LIGHT_SPEED/LAMBDA0*meas_delay;

      if (DEBUG)
	{
	  cout << "************************" << endl;
	  cout << "*** Datos del Canal   **" << endl;
	  cout << "************************" << endl;
	  cout << "Channel Power Gain: " << power_gain << endl;
	}

      vector<double> channel_tmp = channel_input;
  
      // Multiplicación del vector por la ganancia del canal
      transform(channel_tmp.begin(), channel_tmp.end(), channel_tmp.begin(),
		[&power_gain](double element) { return element *= sqrt(power_gain); });

      // Desplazamiento según el retardo
      // Warning: Posible bug porque es un shift circular
      //rotate(channel_tmp.begin(), channel_tmp.begin()+channel_tmp.size()-delay_samples, channel_tmp.end());
      channel_tmp.insert(channel_tmp.begin(), delay_samples, 0);
      channel_tmp.erase(channel_tmp.end() - delay_samples, channel_tmp.end());

      for (unsigned int ii = 0; ii < channel_output.size(); ii++)
	channel_output[ii] = channel_output[ii] + channel_tmp[ii] + dist(generator);
    }

  
  return channel_output;
}

/*----------------------------------------------------------------------------*/
void ChannelLidar::exposeVar(){

}
