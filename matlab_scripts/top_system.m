clear all;
close all;

config

import TxTop;
import RxTop;
import ChannelTop;

%%%% Transmisor
Transmitter = TxTop(SettingsTx);

%%%% Canal
Channel = ChannelTop(SettingsRx.ARX,SettingsRx.FS,SettingsRx.LAMBDA0,false,SettingsTx.MAX_RANGE);

%%%% Receptor
Receptor = RxTop(SettingsRx, SettingsTx.T_MEAS, Transmitter.T_WAIT);

%%  Parámetros Simulacion
T_SIM = ceil(Transmitter.T_0*SettingsRx.FS); % Tiempo total de la simulación
tline = (1/SettingsRx.FS).*(0:T_SIM-1)';     % Vector de tiempo del tiempo total de la simulacion

%%% TX
PLOT_TX = false;                             % Plotear señales del TX
LOG_TX = false;                              % Loguear señales del TX

%%% Channel
PLOT_CH = false;
LOG_CH = false;
READ_FROM_FILE = true;                             % Leer de la base de datos del simulador 3D
DATAPATH_CARLA = '../data/data_from_ros_15:30:42'; % path a los datos del simulador 3D
N_FRAMES = 5;                                    % Número de frames a procesar (end para todos)

%%% RX
WRITE_TO_FILE = false;                       % Escribir datos procesados
PLOT_RX = false;
PLOT_LOG = true;
LOG_RX = false;

%%%%%%%%
%% TX  %
%%%%%%%%

tx_signal = Transmitter.ProcessTx(tline, PLOT_TX); % Generación de datos del tx

%%%%%%%%%%%%%%%%%%%%%
%% Canal: Lee datos %
%%%%%%%%%%%%%%%%%%%%%

if (READ_FROM_FILE)
    %%%% Archivos en el datapath del simulador
    Files = dir(strcat(DATAPATH_CARLA,'/*.log'));
    
    %%%% Recorre los datos del simulador
    for k=1:min(length(Files),N_FRAMES)
        %%%% Progreso de frames
        fprintf('Cloud %i/%i\n', k,min(length(Files),N_FRAMES))
        fprintf('%.2f %% \n', (k/min(length(Files),N_FRAMES))*100 )
        %%%% Nombre del archivo
        FileNames=Files(k).name;
        fileID = fopen(strcat(DATAPATH_CARLA,'/',FileNames));
        %%%% Lee los 4 parámetros de cada punto:
        %%%% Scan es una matriz de Nx4, donde cada fila es un punto
        %%%% scan(:,1) Distancia
        %%%% scan(:,2) Reflectividad
        %%%% scan(:,3) Azimuth
        %%%% scan(:,4) Elevacion
        formatSpec = "%f %f %f %f";
        scan = textscan(fileID,formatSpec);
        scan = cell2mat(scan);
        range = scan(:,1);
        rho = scan(:,2);
        
        max_fft = [];
        max_freq = [];
        new_dist = [];
        
        %%% Recorre cada uno de los rangos
        for i=1:size(range)
            %%% Procesamiento del canal
            ch_out = Channel.ProcessChannel(tline,tx_signal,range(i),rho(i),PLOT_CH);
            %%% Receptor
            [output_rx,f_vec] = Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);
            [max_value,max_idx] = max(output_rx);
            %%% Post Procesamiento datos del Receptor
            max_fft = [max_fft max_idx];
            max_freq = [max_freq f_vec(max_idx)];
            dist = f_vec(max_idx)*(1/Transmitter.CHIRP_SLOPE)*3e8/2;
            new_dist = [new_dist dist];
        end
        
        %%% Guardar frecuencias para detectar problemas
        if(PLOT_LOG)
            figure('visible','off')
            stem(max_freq);
            ax = gca;
            name = strcat('./images/fft_',sprintf('%d',k),'.jpg')
            saveas(ax,name)
        end

        %%%% Escribir nuevo archivo con datos procesados
        if (WRITE_TO_FILE)
            datapath_out = strcat(datapath,'_matlab/')
            name_folder = split(datapath_out,"/")
            name_folder = char(name_folder(3))
            mkdir('../data/',name_folder)
            fileID_out = fopen(strcat(datapath_out,FileNames),'w');
            formatSpec = '%f %f %f %f %f\n';

            for i=1:size(range)
                fprintf(fileID_out,formatSpec,new_dist(i), range(i),rho(i),scan(i,3),scan(i,4));
            end
            fclose(fileID_out);
        end
    end
else
    range = [1]; % m Rango
    rho = [1];   % Reflectividad                         
    
    max_fft = [];
    max_freq = [];
    new_dist = [];
    for i=1:size(range)
        ch_out = Channel.ProcessChannel(tline,tx_signal,range(i),rho(i),PLOT_CH);
        Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);
        [output_rx,f_vec] = Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);
        [max_value,max_idx] = max(output_rx);
        max_fft = [max_fft max_idx];
        max_freq = [max_freq f_vec(max_idx)];
        dist = f_vec(max_idx)*(1/Transmitter.CHIRP_SLOPE)*3e8/2;
        new_dist = [new_dist dist];
    end
end
