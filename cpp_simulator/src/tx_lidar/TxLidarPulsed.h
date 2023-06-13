/*-----------------------------------------------------------------------------
-- Proyecto      : Lidar PCM
-------------------------------------------------------------------------------
-- Archivo       : TxLidarPulsed.h
-- Organizacion  : Fundacion Fulgor
-- Fecha         : 13 de Junio 2023
-------------------------------------------------------------------------------
-- Descripcion   : Transmisor de LiDAR Pulsado
-------------------------------------------------------------------------------
-- Autor         : Leandro Borgnino
-------------------------------------------------------------------------------
-- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
-------------------------------------------------------------------------------
-- $Id$
-------------------------------------------------------------------------------*/

#ifndef TxLidarPulsed_H
#define TxLidarPulsed_H

// Includes common C++
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h> 
#include <ctime>
#include <math.h>
#include <map>
#include <complex>

// Includes Propios
#include "ffModule/loadSettings.h"

using namespace std;

/*----------------------------------------------------------------------------*/
class TxLidarPulsed
{
 /*-----------------------------------------------------------------------*/
 public:
    TxLidarPulsed();
    ~TxLidarPulsed();

    /**El metodo init, utiliza la clase loadSettings para determinar los valores de las
       variables que utiliza. */
    int init(loadSettings *params);
    void run();    
    
    int out_bit_valid;
    vector <double> out_bits;

 /*-----------------------------------------------------------------------*/
 private:
    void exposeVar();

    int len_total;
    int bit_valid;
    int counter;
};
#endif
