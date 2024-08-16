import tkinter as tk
from tkinter import *
from lidar_json import *
from PIL import Image, ImageTk  # Importar Pillow para manejar imágenes

#clase para almacenar la configuracion 
class ConfigGui:
    def __init__(self):
        self.ventana = tk.Tk()
        #labels a mostrar en interfaz, e inputs del usuario
        self.sim_configs_texts = ['Cantidad de datos: ','Datos por segundo: ']
        self.sim_config_default_values = ['20','1']
        self.sim_config_inputs = []

        self.data_output_type_texts = ["KITTI","RX RT","RX REF","PCD"]
        self.data_output_type_selected = tk.StringVar(value="KITTI")

        self.sim_maps_texts = ["Town01", "Town02", "Town03", "Town04","Town05","Town06","Town07","Town10","Town11","Town12"]
        self.sim_map_selected = tk.StringVar(value="Town01")

        self.sim_clima_texts = ["Soleado", "Niebla", "Lluvia"]
        self.sim_clima_selected = tk.StringVar(value="Soleado")

        self.sim_objects_texts = ['Automoviles: ','Cilistas: ', 'Peatones: ']
        self.sim_objects_default_values = ['60','8','30']
        self.sim_objects_inputs = []

        self.lidar_configs_texts = ['FOV Vertical superior: ', 'FOV Vertical inferior: ', 'Canales: ', 'Rango: ', 'Frecuencia', 'FOV Horizonal', 'FOV Horizontal Step' ]
        self.lidar_config_inputs = []
        
        self.lidar_models_texts = ['Modelado de Efectos de Reflexión', 'Modelado de Efectos Climáticos', 'Modelado Transceptor']
        self.lidar_models_selected = []

        #self.lidar_limit_coeff_texts = ['Coeficiente a: ','Coeficiente b: ']
        #self.lidar_limit_coeff_inputs = []

        #configuraciones de lidars
        self.HDL_64e_config = ['2.0', '-24.8', '64', '120.0']
        self.HDL_64e_models = [True,True,False] 
        #self.HDL_64e_limit_coeff = ['0.0005','0.000054']

        #configuraciones almacenadas
        self.lidar_configs = self.HDL_64e_config
        self.lidar_models = self.HDL_64e_models
        #self.lidar_limit_coeff = self.HDL_64e_limit_coeff
 
        self.sim_configs = []
        self.sim_map = []
        self.sim_objects = []

        
    
    def set_lidar_config(self, new_lidar_config):
        self.lidar_configs = new_lidar_config
    
    def set_simulation_config(self, new_sim_config):
        self.sim_configs = new_sim_config

    def create_text_boxs(self,ventana,fila_inicial,columna_inicial,texts,saved_inputs,default_values=None):

        text_labels = []
        fila_actual=fila_inicial

        for i in range(len(texts)):
            texto = tk.Label(ventana, text=texts[i])
            texto.grid(row=fila_actual,column=columna_inicial)
            text_labels.append(texto)

            input = tk.Entry(ventana, width=10)
            if default_values is not None:
                input.insert(0, default_values[i])
            input.grid(row=fila_actual,column=columna_inicial+1)
            saved_inputs.append(input)
            fila_actual += 1

        return fila_actual
    
    def create_multiple_choice_vertical(self,ventana,fila_inicial,columna_inicial,texts,saved_option,columns=1):

        for j in range(columns):
            fila_actual = fila_inicial
            for i, opcion in enumerate(texts[j*int(len(texts)/columns):(j+1)*int(len(texts)/columns)]):
                radiobutton = tk.Radiobutton(ventana, text=opcion, variable=saved_option, value=opcion, padx=0, pady=0)
                radiobutton.grid(row=fila_actual, column=columna_inicial+1+j,padx=0, pady=0)
                fila_actual += 1

        return fila_actual

    def create_multiple_choice_horizontal(self,ventana,fila_inicial,columna_inicial,texts,saved_option):

        columna_actual = columna_inicial

        for i, opcion in enumerate(texts):
            radiobutton = tk.Radiobutton(ventana, text=opcion, variable=saved_option, value=opcion, padx=0, pady=0)
            radiobutton.grid(row=fila_inicial, column=columna_actual+1,padx=0, pady=0)
            columna_actual += 1

        return columna_actual

    def create_checks(self,ventana,fila_inicial,columna_inicial,texts,check_values):
        fila_actual = fila_inicial

        for text in texts:
            value = tk.BooleanVar()
            check_values.append(value)
            check = tk.Checkbutton(ventana, text=text, variable=value)
            check.grid(row=fila_actual,column=columna_inicial)
            fila_actual+=1
        
        return fila_actual

    
    def boton_comenzar(self,ventana):
        sim_objects = []
        
        self.sim_map.append(self.sim_map_selected.get())

        for input in self.sim_objects_inputs:
            sim_objects.append(input.get())
        self.sim_objects = sim_objects

        print(self.sim_configs)
        print(self.sim_map)
        print(self.sim_objects)

        ventana.destroy()
    
    def boton_config_lidar(self):
        lidar_configs = []
        lidar_models = []
        #lidar_limit_coeff = []

        for input in self.lidar_config_inputs:
            lidar_configs.append(input.get())
        self.lidar_configs = lidar_configs

        for input in self.lidar_models_selected:
            lidar_models.append(input.get())
        self.lidar_models = lidar_models

        #for input in self.lidar_limit_coeff_inputs:
        #    lidar_limit_coeff.append(input.get())
        #self.lidar_limit_coeff = lidar_limit_coeff

        print(self.lidar_configs)
        print(self.lidar_models)
        #print(self.lidar_limit_coeff)

    def boton_config_datos(self):
        datos_configs = []

        for input in self.sim_config_inputs:
            datos_configs.append(input.get())

        datos_configs.append(self.data_output_type_selected.get())
            
        self.sim_configs = datos_configs

        print(datos_configs)
    
    #completar los campos de configuracion del lidar
    def set_lidar_config(self,lidar_config,lidar_models):
        for i,input in enumerate(self.lidar_config_inputs):
            input.insert(0,lidar_config[i])
        for i,value in enumerate(self.lidar_models_selected):
            value.set(lidar_models[i])
        #for i,input in enumerate(self.lidar_limit_coeff_inputs):
        #    input.insert(0,lidar_limit_coeff[i])

    #limpiar los campos de configuracion del lidar
    def reset_lidar_config(self):
        for input in self.lidar_config_inputs:
            input.delete(0,END)
        for value in self.lidar_models_selected:
            value.set(False)
        #for input in self.lidar_limit_coeff_inputs:
        #    input.delete(0,END)
    
    def boton_set_lidar_config(self,lidar_configs,lidar_models):
        self.reset_lidar_config()
        self.set_lidar_config(lidar_configs,lidar_models)

    def save_config(self,input_name):
        print(input_name.get())
        name = input_name.get()
        lidar_configs = []
        lidar_models = []
        #lidar_limit_coeff = []

        for input in self.lidar_config_inputs:
            lidar_configs.append(input.get())

        for input in self.lidar_models_selected:
            lidar_models.append(input.get())

        #for input in self.lidar_limit_coeff_inputs:
        #    lidar_limit_coeff.append(input.get())

        lidar_all_configs = lidar_configs + lidar_models

        save_lidar_config_json(name,lidar_all_configs)

    def crear_ventana_save_config(self):
        ventana_save_config = tk.Toplevel()

        fila_actual = 0
        columna_inicial = 0

        texto = tk.Label(ventana_save_config, text='Nombre')
        texto.grid(row=fila_actual,column=columna_inicial)

        input = tk.Entry(ventana_save_config)
        input.grid(row=fila_actual,column=columna_inicial+1)

        fila_actual += 1

        boton_configs = tk.Button(ventana_save_config, text="Guardar", command=lambda: self.save_config(input))
        boton_configs.grid(row=fila_actual, column=columna_inicial+1)
        fila_actual += 1 


    def crear_ventana_config_lidar(self):
        ventana_config_lidar = tk.Toplevel()
        ventana_config_lidar.title('Configuración Lidar - Fundación Fulgor')
        #crear los campos de texto para configurar el lidar
        fila_actual = 0
        columna_inicial = 0

        boton_configs = tk.Button(ventana_config_lidar, text="Configs guardadas", command=self.crear_ventana_configs_lidar)
        boton_configs.grid(row=fila_actual, column=columna_inicial+1)
        fila_actual += 1 

        fila_actual = self.create_text_boxs(ventana_config_lidar,fila_actual,columna_inicial,self.lidar_configs_texts,self.lidar_config_inputs)

        #checkbuttons para habilitar modelados
        fila_actual = self.create_checks(ventana_config_lidar,fila_actual,columna_inicial,self.lidar_models_texts,self.lidar_models_selected)
        
        #Campos para funcion de limites de reflectance
        #fila_actual = self.create_text_boxs(ventana_config_lidar,fila_actual,columna_inicial,self.lidar_limit_coeff_texts,self.lidar_limit_coeff_inputs)

        boton_save_config_lidar = tk.Button(ventana_config_lidar, text="Confirmar configuracion", command=self.boton_config_lidar)
        boton_save_config_lidar.grid(row=fila_actual, column=columna_inicial)
        boton_configs = tk.Button(ventana_config_lidar, text="Guardar configuracion", command=self.crear_ventana_save_config)
        boton_configs.grid(row=fila_actual, column=columna_inicial+1)
        
        #config por defecto (HDL 64e)
        self.set_lidar_config(self.HDL_64e_config,self.HDL_64e_models)

        ventana_config_lidar.mainloop()

    def crear_ventana_config_datos(self):
        ventana_config_datos = tk.Toplevel()
        ventana_config_datos.title('Configuración Datos - Fundación Fulgor')
        #crear los campos de texto para configurar el lidar
        fila_actual = 0
        columna_inicial = 0

        #OPCIONES A CONFIGURAR
        fila_actual = self.create_text_boxs(ventana_config_datos,fila_actual,columna_inicial,self.sim_configs_texts,self.sim_config_inputs,self.sim_config_default_values)

        texto = tk.Label(ventana_config_datos, text='Tipo de Datos de Salida:')
        texto.grid(row=fila_actual,column=columna_inicial)
        fila_actual = self.create_multiple_choice_vertical(ventana_config_datos,fila_actual,columna_inicial, \
                                                           self.data_output_type_texts,self.data_output_type_selected, 1)


        boton_save_config_datos = tk.Button(ventana_config_datos, text="Confirmar configuracion", command=self.boton_config_datos)
        boton_save_config_datos.grid(row=fila_actual, column=columna_inicial)
        #boton_configs = tk.Button(ventana_config_datos, text="Guardar configuracion", command=self.crear_ventana_save_config)
        #boton_configs.grid(row=fila_actual, column=columna_inicial+1)
        

        #config por defecto (HDL 64e)
        #self.set_lidar_config(self.HDL_64e_config,self.HDL_64e_models,self.HDL_64e_limit_coeff)

        ventana_config_datos.mainloop()

    def split_lidar_config(self,config):
        lidar_configs = []
        lidar_models = []
        #lidar_limit_coeff = []

        configs = len(self.lidar_configs) # 11
        models = len(self.lidar_models) # 4
        #limit_coeff = len(self.lidar_limit_coeff) # 2

        for p in config[0:configs]:
            lidar_configs.append(p)
        for p in config[configs:configs+models]:
            lidar_models.append(p)
        #for p in config[configs+models:configs+models+limit_coeff]:
        #    lidar_limit_coeff.append(p)

        return lidar_configs,lidar_models


    def boton_configs(self,text):

        config = lidar_config_to_array(text)

        lidar_configs,lidar_models = self.split_lidar_config(config)

        self.boton_set_lidar_config(lidar_configs,lidar_models)

    def create_config_buttons(self,ventana,fila_inicial,columna_inicial,texts):
        fila_actual=fila_inicial
        for text in texts:
            button= tk.Button(ventana, text=text, command=lambda t=text: self.boton_configs(t))
            button.grid(row=fila_actual, column=columna_inicial)
            fila_actual+=1
        

    def crear_ventana_configs_lidar(self):
        ventana_configs = tk.Toplevel()

        configs = read_lidar_configs_names_json()

        fila_actual = 0
        columna_inicial = 0

        self.create_config_buttons(ventana_configs,fila_actual,columna_inicial,configs)


    def ventana_principal(self):
        self.ventana.title('Configuración Simulador - Fundación Fulgor')

        # Cargar la imagen usando PIL (esto es necesario para manejar formatos como JPG, PNG, etc.)
        imagen = Image.open("fulgor_edited_medium.jpg")  # Reemplaza con la ruta de tu imagen
        imagen = imagen.resize((166*2, 62*2))  # Redimensionar la imagen si es necesario
        imagen_tk = ImageTk.PhotoImage(imagen)

        # Crear un Label para mostrar la imagen
        label_imagen = tk.Label(self.ventana, image=imagen_tk)
        label_imagen.grid(row=0, column=0, columnspan=4)  # Colocar la imagen en la parte superior

        fila_actual = 1
        columna_inicial = 0

        #SELECCION DE MAPA
        print(fila_actual)
        texto = tk.Label(self.ventana, text='Mapa:')
        texto.grid(row=fila_actual,column=columna_inicial)

        fila_actual = self.create_multiple_choice_vertical(self.ventana,fila_actual,columna_inicial, \
                                                  self.sim_maps_texts,self.sim_map_selected, 2)

        #SELECCION DE CLIMA
        texto = tk.Label(self.ventana, text='Clima:')
        texto.grid(row=fila_actual,column=columna_inicial)

        self.create_multiple_choice_horizontal(self.ventana,fila_actual,columna_inicial, \
                                                  self.sim_clima_texts,self.sim_clima_selected)
        fila_actual += 2

        #CANTIDAD DE CADA OBJETO
        texto = tk.Label(self.ventana, text='Actores')
        texto.grid(row=fila_actual,column=columna_inicial+1)
        fila_actual += 1

        fila_actual = self.create_text_boxs(self.ventana,fila_actual,columna_inicial, \
                                            self.sim_objects_texts,self.sim_objects_inputs,self.sim_objects_default_values)
        


        #BOTONES
        # boton comenzar
        boton_comenzar = tk.Button(self.ventana, text="Comenzar", command=lambda: self.boton_comenzar(self.ventana))
        boton_comenzar.grid(row=fila_actual+2, column=columna_inicial+1)
        # boton para configurar lidar, abre nueva self.ventana
        boton_configs_lidar = tk.Button(self.ventana, text="Configurar LiDAR", command=self.crear_ventana_config_lidar)
        boton_configs_lidar.grid(row=fila_actual, column=columna_inicial)
        # boton para configurar lidar, abre nueva ventana
        boton_configs_datos = tk.Button(self.ventana, text="Configurar Datos", command=self.crear_ventana_config_datos)
        boton_configs_datos.grid(row=fila_actual, column=columna_inicial+1)

        # Iniciar el bucle de eventos de la ventana
        self.ventana.mainloop()

        sim_all_configs = self.sim_configs + self.sim_map + self.sim_objects
        print(sim_all_configs)
        lidar_all_configs = self.lidar_configs + self.lidar_models

        return sim_all_configs,lidar_all_configs

if __name__ == "__main__":
    interfaz = ConfigGui()

    print(interfaz.ventana_principal())


