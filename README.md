<h1 align="center">
  <br>
  <a href="https://www.fundacionfulgor.org.ar/sitio/index.php"><img src="https://eamta.ar/wp-content/uploads/2021/10/fulgor_edited_medium.jpg" alt="Time Resolved LiDAR Model" width="500"></a>
  <br>
  Time Resolved LiDAR Model
  <br>
</h1>

<h4 align="center"> Lidar C++ Model that can be integrated in UE4 3D environments. </h4>

<p align="center">
  <a href="#Introduction">Introduction</a> •
  <a href="#key-features">Key Features</a> •
  <a href="#instalation">Install on CARLA Driving Simulator</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#configuration">Configuration</a>
</p>



-----
## Introduction

This project was developed by Fundación Fulgor as final work for Leandro Borgnino's Master Degree Thesis.  The objective of this project is connect the development of digital signal processing algorithms in LiDAR sensors to autonomous driving through an open source enviroment that allows to generate data and desing architectures to test in 3D generated cities.

-----
## Key Features
* Open Source
* Beam Divergence
* Atmosferic Attenuation
* Weather (Sunny, Rain, Fog)
* Objects Material
* Incidence angle
* Multiple Reflections
* Time resolved output
* Electric Transceptor Model
* FMCW and Pulsed Architectures
-----

## Install on CARLA Driving Simulator

1. **Clone Repo**

   ```bash 
   git clone git@github.com:leoborgnino/LidarModelling.git
   ```
  
2. **Compile and initial tests** <sup>(optional)</sup>

   ```bash
    cd cpp_simulator/src/
    cmake .
    make 
    ./LidarCPP
    ```
3. ** [Install CARLA UE4](https://carla.readthedocs.io/en/latest/build_windows/) until Part Two **
4. ** Follow Part Two of Build CARLA but using carla submodule from this repository**


-----

## How To Use

### Data Generation
1. **Compile and launch modified CARLA:** Open x64 Native Tools Prompt for VS 2019.
   ```bash
	cd carla
    make launch
    ```
2. **Use the gui to run simulations**
   ```bash
	cd CARLA_scripts
    python3 carla_data_collector_gui.py
    ```
    
### Install API in python3.8 (other versions fail)
   ```bash
	cd carla
    make PythonAPI
    cd PythonAPI\carla\dist
    pip install carla-0.9.15-cp38-cp38-win_amd64.whl
    ```


-----

## Configuration

Work in progress