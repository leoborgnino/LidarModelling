/*-----------------------------------------------------------------------------
  -- Proyecto      : Lidar PCM
  -------------------------------------------------------------------------------
  -- Archivo       : RxLidarFMCW.cpp
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

#include "RxLidarFMCW.h"

/*----------------------------------------------------------------------------*/
RxLidarFMCW::RxLidarFMCW()
{
    
  printf("RxLidarFMCW :: Has been created\n");

};

/*----------------------------------------------------------------------------*/
RxLidarFMCW::~RxLidarFMCW(){};

/*----------------------------------------------------------------------------*/
int  RxLidarFMCW::init(loadSettings *params){
  /*!Se utiliza para realizar la carga de parametros y la configuracion 
    inicial de las variables*/    
  MAX_RANGE = params->getParamAsInt(string("global.MAX_RANGE"));

  DEBUG_RX = params->getParamAsInt(string("global.DEBUG"));
  FS = params->getParamAsDouble(string("RxLidarFMCW.FS"));
  NOS = params->getParamAsInt(string("RxLidarFMCW.NOS"));
  POWER_RX = params->getParamAsDouble(string("RxLidarFMCW.PRX"));    
  RPD = params->getParamAsDouble(string("RxLidarFMCW.RPD"));    

  noise_power = Q_ELECT/RPD*FS;
  return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> RxLidarFMCW::run(vector<double> input_rx_from_tx, vector<double> input_rx_from_channel)
{
  vector<double> noise_vector;

  // Generador random
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  const double mean = 0.0;
  const double stddev = 0.1;
  default_random_engine generator(seed);
  normal_distribution<double> dist(mean, stddev);

  if (DEBUG)
    {
      cout << "************************" << endl;
      cout << "** Datos del Receptor **" << endl;
      cout << "************************" << endl;
      cout << "Noise Power Gain: " << noise_power << endl;
    }
  
  // AFE
  out_bits = input_rx_from_channel;
  for (unsigned int ii = 0; ii < input_rx_from_channel.size(); ii++)
    out_bits[ii] = input_rx_from_channel[ii] + sqrt(noise_power)*dist(generator);

  // MF
  vector<double> matched_filter = input_rx_from_tx;
  reverse(matched_filter.begin(), matched_filter.end());
  out_bits = convolucion(matched_filter,out_bits);
  
  return out_bits;
}

/*----------------------------------------------------------------------------*/
void RxLidarFMCW::exposeVar(){

}

std::vector<double> RxLidarFMCW::convolucion(const std::vector<double>& signal, const std::vector<double>& kernel) {
    std::vector<double> result(signal.size() + kernel.size() - 1, 0.0);

    for (size_t i = 0; i < signal.size(); ++i) {
        for (size_t j = 0; j < kernel.size(); ++j) {
            result[i + j] += signal[i] * kernel[j];
        }
    }

    return result;
}

//std::vector<double> RxLidarFMCW::convolucion(const std::vector<double>& signal, const std::vector<double>& kernel) {
//    std::vector<double> result(signal.size(), 0.0);
//    int kernelRadius = kernel.size() / 2;
//
//    for (int i = 0; i < int(signal.size()); ++i) {
//        for (int j = -kernelRadius; j <= kernelRadius; ++j) {
//            int index = i + j;
//            if (index >= 0 && index < signal.size()) {
//                result[i] += signal[index] * kernel[j + kernelRadius];
//            }
//        }
//    }
//
//    return result;
//}