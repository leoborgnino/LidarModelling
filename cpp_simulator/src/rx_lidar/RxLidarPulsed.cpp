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

    noise_power = Q_ELEC/RPD*FS;
    return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> RxLidarPulsed::run(vector<double> input_rx)
{

  out_bits = input_rx;
  
  return out_bits;
}

/*----------------------------------------------------------------------------*/
void RxLidarPulsed::exposeVar(){

}
