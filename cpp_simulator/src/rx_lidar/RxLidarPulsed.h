/*-----------------------------------------------------------------------------
  -- Proyecto      : Lidar PCM
  -------------------------------------------------------------------------------
  -- Archivo       : RxLidarpulsed.h
  -- Organizacion  : Fundacion Fulgor
  -- Fecha         : 13 de Junio 2023
  -------------------------------------------------------------------------------
  -- Descripcion   : Receptor de Lidar Pulsado
  -------------------------------------------------------------------------------
  -- Autor         : Leandro Borgnino
  -------------------------------------------------------------------------------
  -- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
  -------------------------------------------------------------------------------
  -- $Id$
  -------------------------------------------------------------------------------*/

#ifndef RxLidarPulsed_H
#define RxLidarPulsed_H

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
#include "constants.h"
#include "ffModule/loadSettings.h"

using namespace std;

/*----------------------------------------------------------------------------*/
class RxLidarPulsed
{
  /*-----------------------------------------------------------------------*/
public:
  RxLidarPulsed();
  ~RxLidarPulsed();

  /**El metodo init, utiliza la clase loadSettings para determinar los valores de las
     variables que utiliza. */
  int init(loadSettings *params);
  vector<double> run(vector<double> input_rx);    

  // Interfaces
  vector <double> out_bits;

  /*-----------------------------------------------------------------------*/
private:
  void exposeVar();

  // Params
  int MAX_RANGE,NOS;
  double FS, POWER_RX, RPD, NOISE;
  
  // Variables
  double noise_power;

};
#endif
