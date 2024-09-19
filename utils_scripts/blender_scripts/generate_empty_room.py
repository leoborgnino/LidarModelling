import math
import bpy

# Cambiar por los materiales de CARLA
wall_material = "WallMaterial"
glass_material = "GlassMaterial"
box_material = "BoxMaterial"

z_start = 0.06
boxes_location = ((0.64+0.39,0.45,z_start), (0.64+0.68+0.23,0.0,z_start),  (0.64+0.68+0.23,0.0,z_start+0.24/2),(0.64+0.68+0.23,0.0,z_start+(0.24/2)*2),(0.64+0.68+0.23,0.0,z_start+(0.24/2)*3),(0.64+0.68+0.23,0.0,z_start+(0.24/2)*4) )

# Función para crear una pared (plano extruido)
def create_wall(location, dimensions):
    bpy.ops.mesh.primitive_plane_add(size=1, enter_editmode=False, align='WORLD', location=location)
    wall = bpy.context.object
    wall.scale = (dimensions[0] / 2, dimensions[1] / 2, 1)
    bpy.ops.object.transform_apply(scale=True)
    bpy.ops.object.mode_set(mode='EDIT')
    bpy.ops.mesh.extrude_region_move(TRANSFORM_OT_translate={"value": (0, 0, dimensions[2])})
    bpy.ops.object.mode_set(mode='OBJECT')
    return wall

# Función para crear y asignar un material
def assign_material(obj, material_name, color_rgb, transparency=False):
    mat = bpy.data.materials.new(name=material_name)
    mat.use_nodes = True  # Usar nodos para materiales avanzados
    bsdf = mat.node_tree.nodes["Principled BSDF"]
    bsdf.inputs['Base Color'].default_value = (*color_rgb, 1)  # Color RGB y alfa
    if transparency:
        #bsdf.inputs['Transmission'].default_value = 1  # Para crear un efecto de vidrio
        bsdf.inputs['Roughness'].default_value = 0.1   # Un poco de rugosidad para el vidrio
    obj.data.materials.append(mat)

# Función para crear el vidrio
def create_glass(location, dimensions):
    bpy.ops.mesh.primitive_plane_add(size=1, enter_editmode=False, align='WORLD', location=location)
    glass = bpy.context.object
    glass.scale = (dimensions[0] / 2, dimensions[1] / 2, 1)
    bpy.ops.object.transform_apply(scale=True)
    bpy.ops.object.mode_set(mode='EDIT')
    bpy.ops.mesh.extrude_region_move(TRANSFORM_OT_translate={"value": (0, 0, dimensions[2])})
    bpy.ops.object.mode_set(mode='OBJECT')
    glass.name = "Glass"
    return glass

# Limpiar la escena actual eliminando todos los objetos
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

# Parámetros de la habitación
room_width = 5    # Ancho de la habitación (5 metros)
room_height = 2.5  # Altura de las paredes (2.5 metros)
wall_thickness = 0.1  # Grosor de las paredes (0.1 metros)

# Crear el piso
bpy.ops.mesh.primitive_plane_add(size=1, enter_editmode=False, align='WORLD', location=(0, 0, 0))
floor = bpy.context.object
floor.scale = (room_width, room_width, 1)
bpy.ops.object.transform_apply(scale=True)
floor.name = "Floor"

color_wall = (0.5,0.5,0.5)
# Crear las cuatro paredes
# Pared 1: Frente
wall_1 = create_wall(location=(0, -room_width / 2, 0), dimensions=(room_width*2, wall_thickness, room_height))
wall_1.name = "Wall_1"
assign_material(wall_1, wall_material, color_wall)  # Color gris claro

# Pared 2: Atrás
wall_2 = create_wall(location=(0, room_width / 2, 0), dimensions=(room_width*2, wall_thickness, room_height))
wall_2.name = "Wall_2"
assign_material(wall_2, wall_material, color_wall)  # Color gris claro

# Pared 3: Izquierda
wall_3 = create_wall(location=(-room_width / 2, 0, 0), dimensions=(wall_thickness, room_width*2, room_height))
wall_3.name = "Wall_3"
assign_material(wall_3, wall_material, color_wall)  # Color gris claro

# Pared 4: Derecha
wall_4 = create_wall(location=(room_width / 2, 0, 0), dimensions=(wall_thickness, room_width*2, room_height))
wall_4.name = "Wall_4"
assign_material(wall_4, wall_material, color_wall)  # Color gris claro

# Crear el techo (opcional, puedes comentar esta parte si no lo necesitas)
#bpy.ops.mesh.primitive_plane_add(size=1, enter_editmode=False, align='WORLD', location=(0, 0, room_height))
#ceiling = bpy.context.object
#ceiling.scale = (room_width / 2, room_width / 2, 1)
#bpy.ops.object.transform_apply(scale=True)
#ceiling.name = "Ceiling"

# Crear un vidrio de 80 cm x 39 cm x 0.1 cm, rotado 90 grados
glass = create_glass(location=(0, 0.2, 0), dimensions=(0.001, 0.39, 0.8))  # Escala en metros (0.001 es el grosor)
glass.rotation_euler = (math.radians(90), 0, 0)  # Rotar 90 grados sobre el eje X
assign_material(glass, glass_material, (0.6, 0.8, 1.0), transparency=True)  # Color celeste y material vidrio


# Crear la cajasss
boxes_array = []

for i,locations in enumerate(boxes_location):
    bpy.ops.mesh.primitive_cube_add(size=1, enter_editmode=False, align='WORLD', location=locations)
    box = bpy.context.object
    box.scale = (0.35 / 2, 0.25 / 2, 0.24 / 2)  # Escalar a 35 cm de largo, 25 cm de ancho, 24 cm de alto
    box.rotation_euler = (0, 0, math.radians(90))  # Rotar 90 grados sobre el eje X
    # Asignar color marrón a la caja
    assign_material(box, box_material, (0.55, 0.27, 0.07))  # Marrón (en RGB)
    bpy.ops.object.transform_apply(scale=True)
    box.name = "Box" + str(i)
    boxes_array.append(box)


# Guardar el archivo .blend
bpy.ops.wm.save_as_mainfile(filepath="models/empty_room.blend")