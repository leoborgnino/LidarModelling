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

%% TX
PLOT_TX = true
tx_signal = Transmitter.ProcessTx(tline, PLOT_TX)

%% Canal: Lee datos
PLOT_CH = true
READ_FROM_FILE = true
ch_out = Channel.ProcessChannel(tline,tx_signal,READ_FROM_FILE,PLOT_CH);

%% RX
PLOT_RX = true
output_rx = Receptor.ProcessRx(tline,ch_out,tx_signal,PLOT_RX);

% 
% %% Receptor
% 
% wait_samples = ceil(T_WAIT*FS);
% noise_power = Q_ELECT/RPD * FS;
% prx_theo = PTX*power_gain
% 
% theo_snr = prx_theo*T_MEAS/(Q_ELECT/RPD);
% theo_snr_dB = 10*log10(theo_snr)
% f_vec = (0:NFFT-1)*(FS/NFFT);
% 
% detector_out_noiseless = conj(ch_out.*conj(chirp_tx));
% dsp_input_noiseless = detector_out_noiseless(1+wait_samples:end);
% prx_measured_noiseless = mean(abs(dsp_input_noiseless).^2)
% 
% NITERS = 100
% for NITER=1:NITERS
%     noise = sqrt(noise_power/2).*(randn(size(ch_out))+1j.*randn(size(ch_out)));
%     detector_out = detector_out_noiseless + noise;
%     % figure
%     % hold all
%     % plot(tline, real(detector_out_noiseless))
%     % plot(tline, real(noise))
%     % plot(tline, real(detector_out))
%     
%     %%% DSP
%     dsp_input = detector_out(1+wait_samples:end);
%     prx_measured = mean(abs(dsp_input).^2);
% 
%     %%% FFT
%     y_mf = abs(fft(dsp_input,NFFT)).^2;
%     if NITER==1
%         y_mf_accum = y_mf/NITERS;
%     else
%         y_mf_accum = y_mf_accum + y_mf/NITERS; 
%     end
% end
%  %plot(f_vec,y_mf_accum)
%  
% ground = sum(y_mf_accum)/NFFT;
% maxim = max(y_mf_accum);
% SNR_meas = 10*log10((maxim-ground)/ground)
%  
% %%% Celdas 
% fbeat = CHIRP_SLOPE*2*range/3e8;
% max_pos = fbeat/FS*NFFT+1
% cell_of_interest = round(fbeat*T_MEAS);
% total_cells = FS*T_MEAS;
% point_per_cell = NFFT/total_cells;
% 
% fft_dec_phase = mod(max_pos-1,point_per_cell)
% y_mf_dec = y_mf(1+fft_dec_phase:point_per_cell:end)
% fvec_dec = f_vec(1+fft_dec_phase:point_per_cell:end)
% 
% %% CFAR
% 
% 
% 
% plot(f_vec,y_mf);
% hold all
% plot(fvec_dec,y_mf_dec);
% 





