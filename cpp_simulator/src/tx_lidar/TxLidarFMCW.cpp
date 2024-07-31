/*-----------------------------------------------------------------------------
-- Proyecto      : Lidar PCM
-------------------------------------------------------------------------------
-- Archivo       : TxLidarFMCW.cpp
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

#include "TxLidarFMCW.h"

/*----------------------------------------------------------------------------*/
TxLidarFMCW::TxLidarFMCW()
{
    
    printf("TxLidarFMCW :: Has been created\n");

};

/*----------------------------------------------------------------------------*/
TxLidarFMCW::~TxLidarFMCW(){};

/*----------------------------------------------------------------------------*/
int  TxLidarFMCW::init(loadSettings *params){
    /*!Se utiliza para realizar la carga de parametros y la configuracion 
      inicial de las variables*/    
    MAX_RANGE = params->getParamAsInt(string("global.MAX_RANGE"));
    FS = params->getParamAsDouble(string("TxLidarFMCW.FS"));
    NOS = params->getParamAsInt(string("TxLidarFMCW.NOS"));
    POWER_TX = params->getParamAsDouble(string("TxLidarFMCW.PTX"));
    F_BW = params->getParamAsDouble(string("TxLidarFMCW.F_BW"));
    F_MIN = params->getParamAsDouble(string("TxLidarFMCW.F_MIN"));
    T_MOD = params->getParamAsDouble(string("TxLidarFMCW.T_MOD"));
    return 0;
};

/*----------------------------------------------------------------------------*/
vector<double> TxLidarFMCW::run()
{
  out_bits.clear();
  //int LEN_TOTAL = int((2*MAX_RANGE/LIGHT_SPEED)*FS*NOS); // Tiempo Máximo * Frecuencia de Muestreo * Sobremuestreo

  out_bits = generate_chirp(POWER_TX, F_MIN, F_BW, T_MOD, FS, NOS);
  
  return out_bits;
}

/*----------------------------------------------------------------------------*/
void TxLidarFMCW::exposeVar(){

}

// Función para generar una señal FMCW chirp
vector<double> TxLidarFMCW::generate_chirp(double POWER_TX, double f0, double B, double T, double fs, int NOS) {
    int N = static_cast<int>(T * fs*NOS); // Número de muestras
    vector<double> chirp_signal(N);

    for (int n = 0; n < N; ++n) {
      double t = n / (fs*NOS);
        if (t < T / 2) {
            // Subida de frecuencia en la primera mitad del tiempo
            chirp_signal[n] = POWER_TX * cos(2 * PI * (f0 * t + (B / (2 * (T / 2))) * t * t));
        } else {
            // Bajada de frecuencia en la segunda mitad del tiempo
            double t_rel = t - T / 2;
            chirp_signal[n] = POWER_TX * cos(2 * PI * (f0 * (T / 2) + B / 2 + f0 * t_rel - (B / (2 * (T / 2))) * t_rel * t_rel));
        }
    }

    return chirp_signal;
}

