/*-----------------------------------------------------------------------------
  -- Proyecto      : Lidar PCM
  -------------------------------------------------------------------------------
  -- Archivo       : RxLidarPulsed.cpp
  -- Organizacion  : Fundacion Fulgor
  -- Fecha         : 13 de junio 2023
  -------------------------------------------------------------------------------
  -- Descripcion   : Receptor de Lidar Pulsado
  -------------------------------------------------------------------------------
  -- Autor         : Leandro Borgnino
  -------------------------------------------------------------------------------
  -- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
  -------------------------------------------------------------------------------
  -- $Id$
  -------------------------------------------------------------------------------*/

#include "RxLidarPulsed.h"

/*----------------------------------------------------------------------------*/
RxLidarPulsed::RxLidarPulsed()
{
    
  printf("RxLidarPulsed :: Has been created\n");

};

/*----------------------------------------------------------------------------*/
RxLidarPulsed::~RxLidarPulsed(){};

/*----------------------------------------------------------------------------*/
int  RxLidarPulsed::init(loadSettings *params){
  /*!Se utiliza para realizar la carga de parametros y la configuracion 
    inicial de las variables*/    
  MAX_RANGE = params->getParamAsInt(string("global.MAX_RANGE"));

  FS = params->getParamAsDouble(string("RxLidarPulsed.FS"));
  NOS = params->getParamAsInt(string("RxLidarPulsed.NOS"));
  POWER_RX = params->getParamAsDouble(string("RxLidarPulsed.PRX"));    
  RPD = params->getParamAsDouble(string("RxLidarPulsed.RPD"));    
  NOISE = params->getParamAsDouble(string("RxLidarPulsed.NOISE"));

  noise_power = Q_ELECT/RPD*FS;
  return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> RxLidarPulsed::run(vector<double> input_rx)
{
  vector<double> noise_vector;

  // Generador random
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  const double mean = 0.0;
  const double stddev = 0.1;
  default_random_engine generator(seed);
  normal_distribution<double> dist(mean, stddev);

  out_bits = input_rx;
  for (unsigned int ii = 0; ii < input_rx.size(); ii++)
    out_bits[ii] = input_rx[ii] + sqrt(noise_power)*dist(generator);
  
  return out_bits;
}

/*----------------------------------------------------------------------------*/
void RxLidarPulsed::exposeVar(){

}
