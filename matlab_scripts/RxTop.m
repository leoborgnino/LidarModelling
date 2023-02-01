classdef RxTop
    %RXTOP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        SettingsRx;
        T_MEAS;
        T_WAIT;
        NCELLS;
        NFFT;
    end
    
    methods
        function obj = RxTop(SettingsRx, T_MEAS, T_WAIT)
            %RXTOP Construct an instance of this class
            %   Detailed explanation goes here
            obj.SettingsRx = SettingsRx;
            obj.T_MEAS     = T_MEAS;
            obj.T_WAIT     = T_WAIT;
            obj.NCELLS     = SettingsRx.FS*obj.T_MEAS;
            obj.NFFT       = ceil(8*obj.NCELLS);
        end
        
        function [outputRx, f_vec] = ProcessRx(obj, tline, data_input, chirp_tx, PLOT_RX)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            OMEGA0 = 3e8/obj.SettingsRx.LAMBDA0; % rad/s
            FS     = obj.NCELLS/obj.T_MEAS; % OJO FS CORREGIDO
            TS     =                  1/FS; % Periodo de muestreo
            
            wait_samples = ceil(obj.T_WAIT*obj.SettingsRx.FS);
            noise_power = 1.6e-19/obj.SettingsRx.RPD * obj.SettingsRx.FS;
            
            %%%%%%%% TEORIA
%             prx_theo = PTX*power_gain %%% NO IRIA 
%             theo_snr = prx_theo*T_MEAS/(Q_ELECT/RPD);
%             theo_snr_dB = 10*log10(theo_snr)
            detector_out_noiseless = conj(data_input.*conj(chirp_tx));
            dsp_input_noiseless = detector_out_noiseless(1+wait_samples:end);
            prx_measured_noiseless = mean(abs(dsp_input_noiseless).^2);
            
            noise = sqrt(noise_power/2).*(randn(size(data_input))+1j.*randn(size(data_input)));
            detector_out = detector_out_noiseless + noise;
            
            if (PLOT_RX)
                figure
                hold all
                plot(tline, real(detector_out_noiseless))
                plot(tline, real(noise))    
                plot(tline, real(detector_out))
                title("Ruido del Detector")
            end
               
            %%% DSP
            dsp_input = detector_out(1+wait_samples:end);
            prx_measured = mean(abs(dsp_input).^2);
            
            %%% FFT
            y_mf = abs(fft(dsp_input,obj.NFFT)).^2;
            f_vec = (0:obj.NFFT-1)*(obj.SettingsRx.FS/obj.NFFT);
            if (PLOT_RX)
                figure
                plot(f_vec,y_mf)
                title("FFT RX")
            end
            outputRx = y_mf;
        end
    end
end
       
            
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

