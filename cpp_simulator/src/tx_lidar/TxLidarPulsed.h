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
#include "constants.h"
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
  vector<double> run();    

  // Interfaces
  vector <double> out_bits;

  /*-----------------------------------------------------------------------*/
private:
  void exposeVar();

  std::vector<double> rectangular_pulse(double I_max, double T_pulso, double LEN_TOTAL, double FS, double NOS );
  std::vector<double> gaussian_pulse(double I_max, double T_pulso, int LEN_TOTAL);

  // Params
  int MAX_RANGE,NOS, PULSE_SHAPE;
  double TAU_SIGNAL, FS, POWER_TX;
  
  // Variables

};
#endif
