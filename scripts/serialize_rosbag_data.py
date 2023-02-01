from rosbags.rosbag2 import Writer
from rosbags.serde import serialize_cdr
from rosbags.rosbag2 import Reader
from rosbags.serde import deserialize_cdr
import numpy as np
import point_cloud2
from rosbags.typesys.types import sensor_msgs__msg__PointCloud2 as PointCloud2_rosbags
from rosbags.typesys.types import sensor_msgs__msg__PointField as PointField_rosbags
from rosbags.typesys.types import std_msgs__msg__Header as Header_rosbags
from rosbags.typesys.types import builtin_interfaces__msg__Time as Time_rosbags
from sensor_msgs.msg import PointCloud2, PointField
from std_msgs.msg import Header
from builtin_interfaces.msg import Time
import math
from datetime import datetime

# create reader instance and open for reading
with Reader('../data/rosbag2_2023_01_29-17_21_07') as reader:
    # topic and msgtype information is available on .connections list
    for connection in reader.connections:
        print(connection.topic, connection.msgtype)

    # iterate over messages
    file_lidar_processed = open('../data/data_from_matlab.log','r')
    lines_lidar_processed = file_lidar_processed.readlines()
    matrix_data_from_matlab = []
    for i in lines_lidar_processed:
        matrix_data_from_matlab.append(i.replace('\n','').split(' '))

    timestamp_rosbag = []
    msgs_processed = []
    msgs_rosbag = []
    flag = 0
    for connection, timestamp, rawdata in reader.messages():
        if connection.topic == '/carla/ego_vehicle/lidar2':
            msg = deserialize_cdr(rawdata, connection.msgtype)                
            header_rosbag = msg.header
            header = Header()
            timestamp2 = Time()
            timestamp2.sec = header_rosbag.stamp.sec
            timestamp2.nanosec = header_rosbag.stamp.nanosec
            header.stamp = timestamp2
            header.frame_id = header_rosbag.frame_id
            points = []
            for i in matrix_data_from_matlab:
                dist = float(i[0])
                elev = float(i[3])
                azim = float(i[4])
                x = dist * ( math.cos( elev ) * math.sin( azim ) )
                y = dist * ( math.cos( elev ) * math.cos( azim ) )
                z = dist * math.sin( elev )
                points.append([x,y,z])

            msgs_processed.append(point_cloud2.create_cloud_xyz32(header,points))
            timestamp_rosbag.append(timestamp)
                
# create reader instance and open for writting
now = datetime.now()
current_time = now.strftime("%H:%M:%S")
with Writer('../data/rosbag_'+current_time) as writer:
    topic_write = '/carla/ego_vehicle/lidar2_processed'
    msgtype = PointCloud2_rosbags.__msgtype__
    conection = writer.add_connection(topic_write, msgtype, 'cdr', '')
    for i in range(len(msgs_processed)):
        message       = msgs_processed[i]
        stamp_rosbag  = Time_rosbags(sec=message.header.stamp.sec,nanosec=message.header.stamp.nanosec)
        header_rosbag = Header_rosbags(stamp=stamp_rosbag,frame_id=message.header.frame_id)
        pointfield_rosbags = []
        for j in message.fields:
            pointfield_rosbags.append(PointField_rosbags(name=j.name , offset=j.offset, datatype=j.datatype,count=j.count))
        #print(message.data)
        
        message_rosbag = PointCloud2_rosbags(header=header_rosbag,height=message.height,width=message.width,fields=pointfield_rosbags,is_bigendian=message.is_bigendian,point_step=message.point_step,row_step=message.row_step,data=np.array(message.data),is_dense=message.is_dense)
        timestamp = timestamp_rosbag[i]
        #print(timestamp)
        serialized = serialize_cdr(message_rosbag, msgtype)
        writer.write(conection, timestamp, serialized)

