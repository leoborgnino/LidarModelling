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
    return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> TxLidarPulsed::run()
{
  int LEN_TOTAL = int((2*MAX_RANGE/LIGHT_SPEED)*FS*NOS); // Tiempo Máximo * Frecuencia de Muestreo * Sobremuestreo
  for (int i = 0; i<LEN_TOTAL; i++)
    if ( i < int(TAU_SIGNAL*FS*NOS) ) // Tiempo del pulso
      out_bits.push_back(POWER_TX);
    else
      out_bits.push_back(0);

  return out_bits;
}

/*----------------------------------------------------------------------------*/
void TxLidarPulsed::exposeVar(){

}
