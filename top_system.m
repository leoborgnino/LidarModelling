%clear all;
%close all;

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
READ_FROM_FILE = false

%% TX
PLOT_TX = true
LOG_TX = false
tx_signal = Transmitter.ProcessTx(tline, PLOT_TX)

%% Canal: Lee datos
PLOT_CH = true
LOG_CH = false
ch_out = Channel.ProcessChannel(tline,tx_signal,READ_FROM_FILE,PLOT_CH);

%% RX
PLOT_RX = true
LOG_RX = false
output_rx = Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);
