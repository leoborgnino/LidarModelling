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



1. **Instalar Matlab 2018**


2. **Instalar Python y las dependencias de ros2**


## Uso

1. Generar rosbag con CARLA 

2. Desserializar los datos con el script deserialize_rosbag_data.py

3. Procesar los datos con matlab lanzando el script top_system.m y top_system_pulsed.m

4. Serializar los datos con serialize_rosbag_data.py

5. ros2 bag play -l rosbag_pulsed_11:39:54.db3

6. rviz2 . Fixed frame ego_vehicle/lidar2


### Environment variables




[releases]: https://gitlab.com/leoborgnino/lidar-pcm/releases

