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

    bit_valid                   = 0;
    counter                     = 1;
};

/*----------------------------------------------------------------------------*/
TxLidarPulsed::~TxLidarPulsed(){};

/*----------------------------------------------------------------------------*/
int  TxLidarPulsed::init(loadSettings *params){
    /*!Se utiliza para realizar la carga de parametros y la configuracion 
      inicial de las variables*/
    
    //code_rate           = params->getParamAsString(string("global.CODE_RATE"));

    len_total = params->getParamAsInt(string("TxLidarPulsed.LEN_TOTAL"));
    //Registra sus variables en la refTable
    exposeVar();
    
    return 0;
};

/*----------------------------------------------------------------------------*/
void TxLidarPulsed::run()
{
  bit_valid = 1;
  for (int i = 0; i<len_total; i++)
    out_bits.push_back(0);
  cout << out_bits.size() << endl;
  out_bit_valid = bit_valid;
}

/*----------------------------------------------------------------------------*/
void TxLidarPulsed::exposeVar(){

}
