/*-----------------------------------------------------------------------------
-- Proyecto      : Lidar PCM
-------------------------------------------------------------------------------
-- Archivo       : TxLidarPulsed.cpp
-- Organizacion  : Fundacion Fulgor
-- Fecha         : 13 de junio 2023
-------------------------------------------------------------------------------
-- Descripcion   : Transmisor de LiDAR Pulsado
-------------------------------------------------------------------------------
-- Autor         : Leandro Borgnino
-------------------------------------------------------------------------------
-- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
-------------------------------------------------------------------------------
-- $Id$
-------------------------------------------------------------------------------*/

#include "TxLidarPulsed.h"

/*----------------------------------------------------------------------------*/
TxLidarPulsed::TxLidarPulsed()
{
    
    printf("TxLidarPulsed :: Has been created\n");

};

/*----------------------------------------------------------------------------*/
TxLidarPulsed::~TxLidarPulsed(){};

/*----------------------------------------------------------------------------*/
int  TxLidarPulsed::init(loadSettings *params){
    /*!Se utiliza para realizar la carga de parametros y la configuracion 
      inicial de las variables*/    
    MAX_RANGE = params->getParamAsInt(string("global.MAX_RANGE"));
    TAU_SIGNAL = params->getParamAsDouble(string("TxLidarPulsed.TAU_SIGNAL"));
    FS = params->getParamAsDouble(string("TxLidarPulsed.FS"));
    NOS = params->getParamAsInt(string("TxLidarPulsed.NOS"));
    POWER_TX = params->getParamAsDouble(string("TxLidarPulsed.PTX"));
    PULSE_SHAPE = params->getParamAsInt(string("TxLidarPulsed.PULSE_SHAPE"));
    return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> TxLidarPulsed::run()
{
  out_bits.clear();
  int LEN_TOTAL = int((2*MAX_RANGE/LIGHT_SPEED)*FS*NOS); // Tiempo Máximo * Frecuencia de Muestreo * Sobremuestreo

  if (PULSE_SHAPE == 0)
    out_bits = gaussian_pulse(POWER_TX, TAU_SIGNAL, LEN_TOTAL);
  else
    out_bits = rectangular_pulse(POWER_TX, TAU_SIGNAL, LEN_TOTAL, FS, NOS);
  
  return out_bits;
}

/*----------------------------------------------------------------------------*/
void TxLidarPulsed::exposeVar(){

}

std::vector<double> TxLidarPulsed::gaussian_pulse(double I_max, double T_pulso, int LEN_TOTAL) {
    // Calcular sigma a partir de T_pulso
    double sigma = T_pulso / 2.355;

    // Vector para almacenar los valores de la signal
    std::vector<double> signal;

    // Calcular la signal para cada punto de tiempo t
    for (double t = 0; t <= LEN_TOTAL; t++) {
        double s_t = I_max * std::exp(-std::pow(t, 2) / (2 * std::pow(sigma, 2)));
        signal.push_back(s_t);
    }

    return signal;
}


std::vector<double> TxLidarPulsed::rectangular_pulse(double I_max, double T_pulso, double LEN_TOTAL, double FS, double NOS ) {

    // Vector para almacenar los valores de la signal
    std::vector<double> signal;

    // Calcular la signal para cada punto de tiempo t
    for (int i = 0; i<LEN_TOTAL; i++)
      if ( i < int(T_pulso*FS*NOS) ) // Tiempo del pulso
	signal.push_back(I_max);
      else
	signal.push_back(0);

    return signal;
}
