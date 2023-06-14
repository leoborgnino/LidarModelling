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

// Channel
#include "ChannelLidar.h"

// Rx
#include "RxLidarPulsed.h"

// Utils
#include "Logger.h"

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

  /////////////////////////////////////////////
  // :::::::: Lectura de Parametros :::::::: //
  /////////////////////////////////////////////

  char path_to_settings[] = "../conf/dutConfig.json";
  loadSettings *params = new loadSettings(path_to_settings);

  print_start_message();
  params->exposeJson();

  ///////////////////////////////////////////
  // :::::::: Objetos de utilidad :::::::: //
  ///////////////////////////////////////////

  Logger * logger = new Logger();

  ///////////////////////////////////////////
  // :::::: Objetos del Transceptor :::::: //
  ///////////////////////////////////////////
    
  TxLidarPulsed * tx_lidar = new TxLidarPulsed();
  tx_lidar->init             (     params      );

  ChannelLidar * channel_lidar = new ChannelLidar();
  channel_lidar->init        (     params      );
    
  RxLidarPulsed * rx_lidar = new RxLidarPulsed();
  rx_lidar->init             (     params      );
  
  ////////////////////////////////
  // :::::::: Tx LiDAR :::::::: //
  ////////////////////////////////

  vector<double> output_tx;
  output_tx = tx_lidar->run();
  if ( params->getParamAsInt(string("global.LOG_TX")))
    logger->logVariable("logs/tx_output.log",output_tx);

  ///////////////////////////////
  // :::::::: Channel :::::::: //
  ///////////////////////////////
  
  vector<double> output_channel;
  output_channel = channel_lidar->run(output_tx,1,1,0); // Warning Data from Simulator
  if ( params->getParamAsInt(string("global.LOG_CHANNEL")))
    logger->logVariable("logs/channel_output.log",output_channel);

  ////////////////////////////////
  // :::::::: Rx LiDAR :::::::: //
  ////////////////////////////////
  
  vector<double> output_rx;  
  output_rx = rx_lidar->run(output_channel);
  if ( params->getParamAsInt(string("global.LOG_RX")))
    logger->logVariable("logs/rx_output.log",output_rx);


  
}
