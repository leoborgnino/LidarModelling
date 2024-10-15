import carla
import random
import logging
import numpy as np
import open3d as o3d

def generate_lidar_bp(blueprint_library,delta,ang_inc,material,reflectance_limit):
    lidar_bp = blueprint_library.find('sensor.lidar.ray_cast')
    lidar_bp.set_attribute('upper_fov', str(2.0))
    lidar_bp.set_attribute('lower_fov', str(-24.8))
    lidar_bp.set_attribute('channels', str(64))
    lidar_bp.set_attribute('range', str(130.0))
    lidar_bp.set_attribute('rotation_frequency', str(1.0 / delta))
    lidar_bp.set_attribute('points_per_second', str(1333330))
    lidar_bp.set_attribute('noise_stddev', str(0.015))
    lidar_bp.set_attribute('dropoff_general_rate',str(0.0))
    lidar_bp.set_attribute('dropoff_intensity_limit',str(0.0))
    lidar_bp.set_attribute('dropoff_zero_intensity',str(0.0))
    #lidar_bp.set_attribute('sensor_tick', str(0.1)) #si es el doble q delta, va a dar un dato cada 2 ticks
    if(ang_inc):
        lidar_bp.set_attribute('model_angle', 'true')
    if(material):
        lidar_bp.set_attribute('model_material', 'true')
    lidar_bp.set_attribute('noise_stddev_intensity',str(0.05))
    lidar_bp.set_attribute('atmosphere_attenuation_rate',str(0.004))
    if(reflectance_limit):
        lidar_bp.set_attribute('model_reflectance_limits_function', 'true')
        lidar_bp.set_attribute('reflectance_limits_function_coeff_a', str(0.0005))
        lidar_bp.set_attribute('reflectance_limits_function_coeff_b', str(0.000054))
    return lidar_bp

def generate_lidar_bp_by_gui(blueprint_library,delta,lidar_all_configs):
    lidar_bp = blueprint_library.find('sensor.lidar.ray_cast_time_resolved')
    #FALTA LAMBDA
    lidar_bp.set_attribute('lambda_laser', lidar_all_configs[0])
    lidar_bp.set_attribute('upper_fov', lidar_all_configs[1])
    lidar_bp.set_attribute('lower_fov', lidar_all_configs[2])
    lidar_bp.set_attribute('channels', lidar_all_configs[3])
    lidar_bp.set_attribute('range', lidar_all_configs[4])
    lidar_bp.set_attribute('rotation_frequency', lidar_all_configs[5]) 
    lidar_bp.set_attribute('horizontal_fov', lidar_all_configs[6])
    lidar_bp.set_attribute('points_per_second', str(int(lidar_all_configs[6])*int(lidar_all_configs[3])*int(lidar_all_configs[5])))
    if(lidar_all_configs[7]):
        lidar_bp.set_attribute('model_intensity', 'true')
    if(lidar_all_configs[8]):
        lidar_bp.set_attribute('model_weather', 'true')
    if(lidar_all_configs[9]):
        print("MODEL TRANSCEPTOR")
        lidar_bp.set_attribute('model_transceptor', 'true')
    else:
        lidar_bp.set_attribute('model_transceptor', 'false')
    
    if (lidar_all_configs[10] == 'Puntual'): 
        lidar_bp.set_attribute('beam_divergence', str(0) )
    elif (lidar_all_configs[10] == 'Gaussiana'):
        lidar_bp.set_attribute('beam_divergence', str(1) )
    else:
        lidar_bp.set_attribute('beam_divergence', str(2) )
    
    if (lidar_all_configs[11] == 'DD Pulsada'):
        lidar_bp.set_attribute('transceptor_arch', str(0) ) 
    else:
        lidar_bp.set_attribute('transceptor_arch', str(1) )

    ### TRANSCEPTOR
    lidar_bp.set_attribute('debug_global',"false")
    #lidar_bp.set_attribute('debug_rx',"true")
    lidar_bp.set_attribute('log_rx',"false")

    lidar_bp.set_attribute("power_tx", lidar_all_configs[12]);
    if (lidar_all_configs[11] == 'DD Pulsada'):
        lidar_bp.set_attribute("tau_signal", lidar_all_configs[13]);
        lidar_bp.set_attribute("tx_fs", lidar_all_configs[14]);
        lidar_bp.set_attribute("tx_nos", lidar_all_configs[15]);
        lidar_bp.set_attribute("tx_pulse_shape", str((lidar_all_configs[16] =='Rectangular')));
        lidar_bp.set_attribute("ch_fs", lidar_all_configs[14]);
        lidar_bp.set_attribute("ch_nos", lidar_all_configs[15]);
    else:
        lidar_bp.set_attribute("tx_f_bw", lidar_all_configs[13]);
        lidar_bp.set_attribute("tx_f_min", lidar_all_configs[14]);
        lidar_bp.set_attribute("tx_fs", lidar_all_configs[15]);
        lidar_bp.set_attribute("tx_nos", lidar_all_configs[16]);
        lidar_bp.set_attribute("ch_fs", lidar_all_configs[15]);
        lidar_bp.set_attribute("ch_nos", lidar_all_configs[16]);

    lidar_bp.set_attribute("power_rx", lidar_all_configs[17]);
    lidar_bp.set_attribute("rpd_rx", lidar_all_configs[18]);
    lidar_bp.set_attribute("rx_fs", lidar_all_configs[19]);
    lidar_bp.set_attribute("rx_nos", lidar_all_configs[20]);
    #lidar_bp.set_attribute('sensor_tick', str(0.1)) #si es el doble q delta, va a dar un dato cada 2 ticks
    lidar_bp.set_attribute('model_reflectance_limits_function', 'true')
    lidar_bp.set_attribute('reflectance_limits_function_coeff_a', str(0.0005))
    lidar_bp.set_attribute('reflectance_limits_function_coeff_b', str(0.000054))
    lidar_bp.set_attribute('reflectance_limits_function_coeff_b', str(0.000054))

    return lidar_bp


def generate_camera_bp(blueprint_library):
    camera_bp = blueprint_library.filter("sensor.camera.rgb")[0]
    camera_bp.set_attribute("image_size_x", str(1242)) #Resolucion de las imagenes de Kitti
    camera_bp.set_attribute("image_size_y", str(375))

    return camera_bp

def spawn_vehicles(spawn_points,number_of_vehicles,vehicles_bp,traffic_manager,client):
    SpawnActor = carla.command.SpawnActor
    SetAutopilot = carla.command.SetAutopilot
    FutureActor = carla.command.FutureActor
    vehicles_list = []

    batch = []
    for n, transform in enumerate(spawn_points):
        if n >= number_of_vehicles:
            break
        blueprint = random.choice(vehicles_bp)
        if blueprint.has_attribute('color'):
            color = random.choice(blueprint.get_attribute('color').recommended_values)
            blueprint.set_attribute('color', color)
        if blueprint.has_attribute('driver_id'):
            driver_id = random.choice(blueprint.get_attribute('driver_id').recommended_values)
            blueprint.set_attribute('driver_id', driver_id)
        blueprint.set_attribute('role_name', 'autopilot')

        batch.append(SpawnActor(blueprint, transform)
            .then(SetAutopilot(FutureActor, True, traffic_manager.get_port())))

    for response in client.apply_batch_sync(batch, True):
        if response.error:
            logging.error(response.error)
        else:
            vehicles_list.append(response.actor_id)

    return vehicles_list

def save_image(images_path, image_data,frame):
    image_path =  './%s/%.6d.png' % (images_path, frame)
    image_data.save_to_disk(image_path)
    #print('imagen %.6d.bin guardada' % image_data.frame)

def save_pointcloud(pointclouds_path,pointcloud,frame):
    # print("RAW DATA:")
    # print(pointcloud.raw_data[0:100])
    print("DATA RAW SHAPE: ", pointcloud.raw_data.shape)

    data = np.copy(np.frombuffer(pointcloud.raw_data, dtype=np.dtype('f4')))

    total_points = 0
    for i in range(pointcloud.channels):
        #print("Channel ",i, " Count ", pointcloud.get_point_count(i))
        total_points += pointcloud.get_point_count(i)

    print("Total Points: ", total_points)
    points = data[0:total_points*4]
    time_resolved_signals = data[(total_points*4)::]

    # print("Point Cloud")
    # POINTS_N = 10
    # for i in range(len(points[0:POINTS_N*4])):
    #     print("x: ", points[i*4])
    #     print("y: ", points[(i+1)*4])
    #     print("z: ", points[(i+2)*4])
    #     print("i: ", points[(i+3)*4])

    # print("Time Resolved")
    # POINTS_N = 10
    # for i in range(len(time_resolved_signals[0:POINTS_N*2])):
    #     print("t1: ", time_resolved_signals[i*2])
    #     print("t2: ", time_resolved_signals[(i+1)*2])

    data = np.reshape(points, (int(points.shape[0] / 4), 4))

    #print(min(data[:,1]))
    #print(len_signal)
    #print(data)
    #print(data2)

    len_signal = int(len(time_resolved_signals)/(total_points))
    print(total_points)
    print(len(time_resolved_signals))
    print(len_signal)
    print(len(time_resolved_signals)/(total_points))
    if(len_signal != 0):
        data2 = np.reshape(time_resolved_signals[0:len_signal*int( time_resolved_signals.shape[0] /  len_signal )], (int( time_resolved_signals.shape[0] /  len_signal ), len_signal))
        np.savetxt('./logs/time_signal.txt', data2, delimiter=" ", fmt="%s")

    #UNREAL Y EL LIDAR INTERNO UTILIZA EL SISTEMA X: Foward, Y:Right, Z: Up
    #PERO EL LIDAR EN KITTI UTILIZA X: Foward, Y:Left, Z: Up
    #Por lo que hay que invertir las coordenas y

    # Extraemos las coordenadas x, y, z
    xyz_points = data[:, :3]

    #print(min(xyz_points[:,1]))

    # Creamos un objeto PointCloud
    pcd = o3d.geometry.PointCloud()

    # Añadimos los puntos (x, y, z) al PointCloud
    pcd.points = o3d.utility.Vector3dVector(xyz_points)

    points_np = np.asarray(pcd.points)
    #print(min(points_np[:,1]))

    # Si deseas almacenar la intensidad como un atributo de color o canal adicional, podrías
    # mapear la intensidad a un valor de color (esto es opcional).
    # Aquí mapeamos la intensidad al canal de colores (r, g, b), en este caso como escala de grises.
    intensity = data[:, 3]
    #print(intensity)
    colors = np.tile(intensity[:, np.newaxis], (1, 3))  # Escala de grises
    pcd.colors = o3d.utility.Vector3dVector(colors)

    # Guardamos el archivo .pcd
    o3d.io.write_point_cloud('./%s/%.6d.pcd' % (pointclouds_path, frame), pcd)

    print("Archivo .pcd guardado exitosamente.")

    data_reshape = np.copy(data)
    data_reshape[:,1] = -data[:,1]
    pointcloud_path = './%s/%.6d.bin' % (pointclouds_path, frame) 
    data_reshape.tofile(pointcloud_path)
    #print('point cloud %.6d.bin guardada' % lidar_data.frame)

def sensor_callback(data,queue):
    queue.put(data)

def spawn_pedestrians(seed,world,client,number_of_walkers,blueprintsWalkers):
    SpawnActor = carla.command.SpawnActor
    walkers_list = []
    all_id = []

    percentagePedestriansRunning = 0.0      # how many pedestrians will run
    percentagePedestriansCrossing = 0.0     # how many pedestrians will walk through the road
    if seed:
        world.set_pedestrians_seed(seed)
        random.seed(seed)
    # 1. take all the random locations to spawn
    spawn_points = []
    for i in range(number_of_walkers):
        spawn_point = carla.Transform()
        loc = world.get_random_location_from_navigation()
        if (loc != None):
            spawn_point.location = loc
            spawn_points.append(spawn_point)
    # 2. we spawn the walker object
    batch = []
    walker_speed = []
    for spawn_point in spawn_points:
        walker_bp = random.choice(blueprintsWalkers)
        # set as not invincible
        if walker_bp.has_attribute('is_invincible'):
            walker_bp.set_attribute('is_invincible', 'false')
        # set the max speed
        if walker_bp.has_attribute('speed'):
            if (random.random() > percentagePedestriansRunning):
                # walking
                walker_speed.append(walker_bp.get_attribute('speed').recommended_values[1])
            else:
                # running
                walker_speed.append(walker_bp.get_attribute('speed').recommended_values[2])
        else:
            print("Walker has no speed")
            walker_speed.append(0.0)
        batch.append(SpawnActor(walker_bp, spawn_point))
    results = client.apply_batch_sync(batch, True)
    walker_speed2 = []
    for i in range(len(results)):
        if results[i].error:
            pass
            logging.error(results[i].error)
        else:
            walkers_list.append({"id": results[i].actor_id})
            walker_speed2.append(walker_speed[i])
    walker_speed = walker_speed2
    #print(len(walkers_list))
    # 3. we spawn the walker controller
    batch = []
    walker_controller_bp = world.get_blueprint_library().find('controller.ai.walker')
    for i in range(len(walkers_list)):
        batch.append(SpawnActor(walker_controller_bp, carla.Transform(), walkers_list[i]["id"]))
    results = client.apply_batch_sync(batch, True)
    for i in range(len(results)):
        if results[i].error:
            logging.error(results[i].error)
        else:
            walkers_list[i]["con"] = results[i].actor_id
    # 4. we put together the walkers and controllers id to get the objects from their id
    for i in range(len(walkers_list)):
        all_id.append(walkers_list[i]["con"])
        all_id.append(walkers_list[i]["id"])
    all_actors = world.get_actors(all_id)

    # wait for a tick to ensure client receives the last transform of the walkers we have just created

    world.tick()

    # 5. initialize each controller and set target to walk to (list is [controler, actor, controller, actor ...])
    # set how many pedestrians can cross the road
    world.set_pedestrians_cross_factor(percentagePedestriansCrossing)
    for i in range(0, len(all_id), 2):
        # start walker
        all_actors[i].start()
        # set walk to random point
        all_actors[i].go_to_location(world.get_random_location_from_navigation())
        # max speed
        all_actors[i].set_max_speed(float(walker_speed[int(i/2)]))
    
    return all_actors, all_id
    
