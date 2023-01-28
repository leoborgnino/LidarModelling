classdef TxTop
    %TX_TOP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        SettingsTx;
        T_WAIT;
        T_0;
        CHIRP_SLOPE;
    end
    
    methods
        function obj = TxTop(SettingsTx)
            % TX_TOP Constructor
            %   Asigna las configuraciones de Tx
            %   Calcula T wait como 2xMAXRANGE
            %   Calcula T0 como la suma entre TWAIT y TMEAS
            %   Calcula gamma como el ancho de banda del chirp sobre el
            %   tiempo total de chirp T0
            obj.SettingsTx  = SettingsTx;
            obj.T_WAIT      = 2*obj.SettingsTx.MAX_RANGE/3e8; % s
            obj.T_0         = obj.SettingsTx.T_MEAS + obj.T_WAIT; %s Duracion entera del chirp
            obj.CHIRP_SLOPE = obj.SettingsTx.CHIRP_BW/obj.T_0;  % gamma

         end
        
        function outputTx = ProcessTx(obj, tline, PLOT_TX)
            % ProcessTx
            %   Genera el chirp del Tx
            %% Transmisor
            chirp_tx = exp(1j.*pi*obj.CHIRP_SLOPE.*tline.^2); % Chirp en el tiempo total de simulacion
            outputTx = sqrt(obj.SettingsTx.PTX) .* chirp_tx;
            if (PLOT_TX == true)
                %%% Ploteo de Tx
                subplot(3,1,1);
                plot(tline, obj.CHIRP_SLOPE.*tline);
                subplot(3,1,2);
                plot(tline, outputTx);
                subplot(3,1,3);
                N_FFT = 4096;
                fvec = (0:N_FFT-1)*(3*2e9/N_FFT);
                plot(fvec,abs(fft(outputTx,N_FFT)).^2);
            end
        end
    end
end

