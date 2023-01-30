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
PLOT_TX = false
LOG_TX = false
tx_signal = Transmitter.ProcessTx(tline, PLOT_TX);

%% Canal: Lee datos
READ_FROM_FILE = true
if (READ_FROM_FILE)
    fileID = fopen('data/data_from_ros2.log','r');
    formatSpec = "%f %f %f %f";
    scan = textscan(fileID,formatSpec);
    scan = cell2mat(scan)
    range = scan(1:5,1); %% Cambiar despues
    rho = scan(1:5,2);
else
    range = [1]; %m Rango, luego del canal
    rho = [1]; % Reflectividad, luego del canal                                
end
            
PLOT_CH = true
LOG_CH = false
%% RX
PLOT_RX = true
LOG_RX = false

for i=1:size(range)
    ch_out = Channel.ProcessChannel(tline,tx_signal,range(i),rho(i),PLOT_CH);
    output_rx = Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);
end