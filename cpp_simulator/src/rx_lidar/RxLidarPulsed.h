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
#include <random>
#include <chrono>
#include <algorithm>


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
  vector<double> run(vector<double> input_rx_from_tx, vector<double> input_rx_from_channel);    

  // Interfaces
  vector <double> out_bits;

  /*-----------------------------------------------------------------------*/
private:
  void exposeVar();
  std::vector<double> convolucion(const std::vector<double>& signal, const std::vector<double>& kernel);
  // Params
  int MAX_RANGE,NOS;
  double FS, POWER_RX, RPD, NOISE;
  bool DEBUG_RX;
  
  // Variables
  double noise_power;

};
#endif
