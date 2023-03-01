from rosbags.rosbag2 import Reader
from rosbags.serde import deserialize_cdr
import matplotlib.pyplot as plt
import numpy as np
import point_cloud2
import math
from datetime import datetime
import os

DEBUG = True

now = datetime.now()
current_time = now.strftime("%H:%M:%S")

# create reader instance and open for reading
with Reader('../data/rosbag2_2023_01_29-17_21_07') as reader:
    # topic and msgtype information is available on .connections list
    for connection in reader.connections:
        print(connection.topic, connection.msgtype)

    # iterate over messages
    datapath = '../data/data_from_ros_'+ current_time +'/'
    os.mkdir(datapath)
    if (DEBUG == True):
        distances = []
        azimuts = []
        elevaciones = []
    for connection, timestamp, rawdata in reader.messages():
        if connection.topic == '/carla/ego_vehicle/lidar2':
            file_lidar = open(datapath + 'data_from_ros2'+str(timestamp)+'.log','w')
            msg = deserialize_cdr(rawdata, connection.msgtype)
            for point in point_cloud2.read_points(msg, skip_nans=True):
                distance = math.sqrt(point[0]**2+point[1]**2+point[2]**2)
                azim = math.atan2(point[0],point[1])
                elev = math.asin(point[2]/distance)
                intensity = point[3]
                if (DEBUG == True):
                    distances.append(distance)
                    azimuts.append(azim)
                    elevaciones.append(elev)
                file_lidar.write("%.7f %.7f %.7f %.7f \n"%(distance,intensity,azim,elev))


            
plt.hist(distances)
plt.show()
plt.hist(azimuts)
plt.show()
plt.hist(elevaciones)
plt.show()
