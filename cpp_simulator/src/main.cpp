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
#include "constants.h"

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
//int main (int argc, char *argv[])
int main ()
{

  /////////////////////////////////////////////
  // :::::::: Lectura de Parametros :::::::: //
  /////////////////////////////////////////////

  char path_to_settings[] = "../conf/dutConfig.json";
  loadSettings *params = new loadSettings(path_to_settings);

  double FS_RX = params->getParamAsDouble(string("RxLidarPulsed.FS"));
  int NOS_RX = params->getParamAsInt(string("RxLidarPulsed.NOS"));
  bool DEBUG_FLAG = params->getParamAsInt(string("global.DEBUG"));

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
  
  ///////////////////////////////////////////
  // ::: Procesamiento del Transceptor ::: //
  ///////////////////////////////////////////

  vector<vector<double>> ranges{
				{20,40,60},
				}; // From Simulator
  vector<vector<double>> intensities{
				     {0.1,0.3,0.5},
				     };

  cout << ranges.size() << endl;

  for (unsigned int ii = 0; ii<ranges.size(); ii++)
    {

      cout << ii << endl;
      ////////////////////////////////
      // :::::::: Tx LiDAR :::::::: //
      ////////////////////////////////

      vector<double> output_tx;
      output_tx = tx_lidar->run();
      if ( params->getParamAsInt(string("global.LOG_TX")))
	logger->logVariable("logs/tx_output"+to_string(ii)+".log",output_tx);
      
      ///////////////////////////////
      // :::::::: Channel :::::::: //
      ///////////////////////////////

      vector<double> output_channel;
      output_channel = channel_lidar->run(output_tx,ranges[ii],intensities[ii],0); // Warning Data from Simulator
      if ( params->getParamAsInt(string("global.LOG_CHANNEL")))
	logger->logVariable("logs/channel_output"+to_string(ii)+".log",output_channel);

      ////////////////////////////////
      // :::::::: Rx LiDAR :::::::: //
      ////////////////////////////////
  
      vector<double> output_rx;  
      output_rx = rx_lidar->run(output_tx,output_channel);
      if ( params->getParamAsInt(string("global.LOG_RX")))
	logger->logVariable("logs/rx_output"+to_string(ii)+".log",output_rx);

      // Calculo de la distancia
      auto it = max_element(output_rx.begin(),output_rx.end());
      int max_idx = distance(output_rx.begin(),it);
      double max_value = *it;
      double distance = ((max_idx+1-output_tx.size())/(FS_RX*NOS_RX))*LIGHT_SPEED/2;

      if (DEBUG_FLAG)
	{
	  cout << "************************" << endl;
	  cout << "** Resultados Finales **" << endl;
	  cout << "************************" << endl;
	  cout << "Distance Expected: " << ranges[ii][0] << endl;
	  cout << "Distance Measured: " << distance << endl;
	  cout << "Power Detected: " << max_value << endl;
	}
    }  
}
