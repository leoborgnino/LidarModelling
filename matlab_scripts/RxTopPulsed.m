classdef RxTopPulsed
    %RXTOP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        SettingsRx;
        T_MEAS;
        NCELLS;
    end
    
    methods
        function obj = RxTopPulsed(SettingsRx, T_MEAS)
            %RXTOP Construct an instance of this class
            %   Detailed explanation goes here
            obj.SettingsRx = SettingsRx;
            obj.T_MEAS     = T_MEAS;
            obj.NCELLS     = SettingsRx.FS*obj.T_MEAS;
        end
        
        function [outputRx, f_vec] = ProcessRx(obj, tline, data_input, PRX, PLOT_RX)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            OMEGA0 = 3e8/obj.SettingsRx.LAMBDA0; % rad/s
            FS     = obj.NCELLS/obj.T_MEAS; % OJO FS CORREGIDO
            TS     =                  1/FS; % Periodo de muestreo
            
            noise_power = 1.6e-19/obj.SettingsRx.RPD * obj.SettingsRx.FS;
            
            %%%%%%%% TEORIA
%             prx_theo = entrada*power_gain %%% NO IRIA 
%             theo_snr = prx_theo*T_MEAS/(Q_ELECT/RPD);
%             theo_snr_dB = 10*log10(theo_snr)

	    % AFE
            detector_out_noiseless = data_input*PRX;
            dsp_input_noiseless = detector_out_noiseless;
            prx_measured_noiseless = mean(abs(dsp_input_noiseless).^2);
            
            noise = sqrt(noise_power/2).*(randn(size(data_input))+1j.*randn(size(data_input)));
            detector_out = detector_out_noiseless + noise;
            
            if (PLOT_RX)
	        figure
                subplot(2,1,1)
                plot(abs(detector_out_noiseless))
		title("Entrada al detector")
		%plot(tline, real(noise))
                subplot(2,1,2)
                plot(abs(detector_out))
                title("Salida AFE")
            end
               
            %%% DSP
            dsp_input = detector_out;
            prx_measured = mean(abs(dsp_input).^2);
            
            %%% MF
	    matched_filter = conj(data_input(end:-1:1));
            y_mf = conv(matched_filter,detector_out);
	    noise_mf = conv(matched_filter,noise);
            f_vec = tline;
            if (PLOT_RX)
	      figure
              subplot(2,1,1)
              plot(abs(noise_mf))
              title("NOISE RX")
              subplot(2,1,2)
              plot(abs(y_mf))
              title("MF RX")
            end
            outputRx = abs(y_mf);
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

