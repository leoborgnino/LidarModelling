from rosbags.rosbag2 import Reader
from rosbags.serde import deserialize_cdr
import numpy as np
import point_cloud2
import math


# create reader instance and open for reading
with Reader('./rosbag2_2023_01_29-17_21_07') as reader:
    # topic and msgtype information is available on .connections list
    for connection in reader.connections:
        print(connection.topic, connection.msgtype)

    # iterate over messages
    file_lidar = open('data_from_ros2.log','w')
    
    for connection, timestamp, rawdata in reader.messages():
        if connection.topic == '/carla/ego_vehicle/lidar2':
            msg = deserialize_cdr(rawdata, connection.msgtype)
            for point in point_cloud2.read_points(msg, skip_nans=True):
                distance = math.sqrt(point[0]**2+point[1]**2+point[2]**2)
                azim = math.atan2(point[0],point[1])
                elev = math.asin(point[2]/distance)
                #print(elev*180/math.pi)
                #print(azim*180/math.pi)
                intensity = point[3]
                file_lidar.write("%.7f %.7f %.7f %.7f \n"%(distance,intensity,azim,elev))
                #X = Math.round( dist * ( Math.cos( elev ) * Math.sin( azim ) ) );
                #Y = Math.round( dist * ( Math.cos( elev ) * Math.cos( azim ) ) );
                #Z = Math.round( dist * Math.sin( elev ) );
                #print(msg.fields)
                #print(msg.row_step)
                #print(msg.height)
                #print(msg.point_step)
                #print(msg.width)
                #print(len(msg.data)/16)
                #print(len(msg.data))
                #break
            exit()
                
            
