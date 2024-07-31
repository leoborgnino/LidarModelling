/*-----------------------------------------------------------------------------
  -- Proyecto      : Lidar PCM
  -------------------------------------------------------------------------------
  -- Archivo       : TxLidarFMCW.h
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

#ifndef TxLidarFMCW_H
#define TxLidarFMCW_H

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
class TxLidarFMCW
{
  /*-----------------------------------------------------------------------*/
public:
  TxLidarFMCW();
  ~TxLidarFMCW();

  /**El metodo init, utiliza la clase loadSettings para determinar los valores de las
     variables que utiliza. */
  int init(loadSettings *params);
  vector<double> run();    

  // Interfaces
  vector <double> out_bits;

  /*-----------------------------------------------------------------------*/
private:
  void exposeVar();

  vector<double> generate_chirp(double POWER_TX, double f0, double B, double T, double fs, int NOS);

  // Params
  int MAX_RANGE,NOS;
  double FS, POWER_TX, F_BW,F_MIN,T_MOD;
  
  // Variables

};
#endif
