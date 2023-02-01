clear all;
close all;

config

import TxTop;
import RxTop;
import ChannelTop;

Transmitter = TxTop(SettingsTx);
Receptor = RxTop(SettingsRx, SettingsTx.T_MEAS, Transmitter.T_WAIT);
Channel = ChannelTop(SettingsRx.ARX,SettingsRx.FS,SettingsRx.LAMBDA0);

%% Simulacion
T_SIM = ceil(Transmitter.T_0*SettingsRx.FS); % Tiempo total de la simulación
tline = (1/SettingsRx.FS).*(0:T_SIM-1)'; % Vector de tiempo del tiempo total de la simulacion

%% TX
PLOT_TX = false;
LOG_TX = false;
tx_signal = Transmitter.ProcessTx(tline, PLOT_TX);

%% Canal: Lee datos
READ_FROM_FILE = true;
if (READ_FROM_FILE)
    fileID = fopen('../data/data_from_ros2.log','r');
    formatSpec = "%f %f %f %f";
    scan = textscan(fileID,formatSpec);
    scan = cell2mat(scan);
    range = scan(:,1); %% Cambiar despues
    rho = scan(:,2);
else
    range = [1]; %m Rango, luego del canal
    rho = [1]; % Reflectividad, luego del canal                                
end
            
PLOT_CH = false;
LOG_CH = false;
%% RX
PLOT_RX = false;
LOG_RX = false;

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

%%
WRITE_TO_FILE = true;

if (WRITE_TO_FILE)
    fileID_out = fopen('../data/data_from_matlab.log','w');
    formatSpec = '%f %f %f %f %f\n';

    for i=1:size(range)
        fprintf(fileID_out,formatSpec,new_dist(i), range(i),rho(i),scan(i,3),scan(i,4));
    end
    fclose(fileID_out);
end





