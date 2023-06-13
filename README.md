<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# Lidar Matlab Model for Autonomous Driving Simulation

[![pipeline status](https://gitlab.com/leoborgnino/lidar-systems-level/badges/master/pipeline.svg)](https://gitlab.com/leoborgnino/lidar-systems-level/-/commits/master)

Lidar Matlab Model for Carla data processing.

[Introducción](# Introducción) •
[Instalación](# Instalación) •
[Uso](# Uso) •

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

