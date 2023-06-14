<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# Lidar C++ Model for Autonomous Driving Simulation

[![pipeline status](https://gitlab.com/leoborgnino/lidar-pcm/badges/master/pipeline.svg)](https://gitlab.com/leoborgnino/lidar-pcm/-/commits/master)

Lidar C++ Model for UE4 models a LiDAR sensor that can be integrated in UE4 environments(i.e CARLA).

[Introducción](# Introducción) •
[Instalación](# Instalación) •
[Configuración](# Configuración) •
[Integración con UE4](# UE4Integration)

</div>

## Introducción

Este proyecto se desarrolloó en Fundación Fulgor y el objetivo es conectar el desarrollo de algoritmos de procesamiento de señales en sensores LiDAR con un entorno de simulación de navegación autónoma en 3D que produzca datos realistas.


## Instalación



1. **Clonar Repositorio**

   ```bash 
   git clone https://gitlab.com/leoborgnino/lidar-systems-level
   ```
  
2. **Compilar y realizar tests de verificación** <sup>(optional)</sup>

   ```bash
    cd cpp_simulator/src/
    cmake .
    make 
    ./LidarCPP
    ```

## Configuration

[releases]: https://gitlab.com/leoborgnino/lidar-pcm/releases
