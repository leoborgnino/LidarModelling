/*-----------------------------------------------------------------------------
-- Proyecto      : Modelo Lidar C++
-------------------------------------------------------------------------------
-- Archivo       : main.cpp
-- Organizacion  : Fundacion Fulgor
-- Fecha         : 24 Octubre 2022
-------------------------------------------------------------------------------
-- Descripcion   : Main
-------------------------------------------------------------------------------
-- Autor         : Leandro Borgnino
-------------------------------------------------------------------------------
-- Copyright (C) 2023 Fundacion Fulgor  All rights reserved
-------------------------------------------------------------------------------
-- $Id: $
-------------------------------------------------------------------------------*/

// Includes common C++
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

// Includes LiDAR System

// Tx
#include "TxLidarPulsed.h"

/****************
  Utils Functions
******************/

void print_start_message()
{
  /*Simulation start message*/
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  printf ("Current local time and date: %s", asctime(timeinfo));
  printf ("Starting simulation with parameters: \n");
}


/****************
  Main Simulation
******************/
int main (int argc, char *argv[])
{
  print_start_message();

  //::::::::::::Lectura de Parametros::::::::::::::::::
  char path_to_settings[] = "../conf/dutConfig.json";
  loadSettings *params = new loadSettings(path_to_settings);

  // Tx LiDAR
  TxLidarPulsed * tx_lidar = new TxLidarPulsed();
  tx_lidar->init             ( params          );

  tx_lidar->run();
  // 

    
}
