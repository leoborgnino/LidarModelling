classdef TxTopPulsed
    %TXTOPPULSED Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        SettingsTxPulsed;
    end
    
    methods
        function obj = TxTopPulsed(SettingsTxPulsed)
            obj.SettingsTxPulsed  = SettingsTxPulsed;
        end
        
        function outputTxPulsed = ProcessTx(obj, tline, FS, PLOT_TX)
            L_pulso = obj.SettingsTxPulsed.TAU_SIGNAL*FS;
            x_t = [sqrt(obj.SettingsTxPulsed.PTX).*ones(L_pulso,1);zeros(L_pulso*2,1)];
            %x_t = [zeros(floor((length(tline)-L_pulso)/2),1);sqrt(obj.SettingsTxPulsed.PTX).*ones(L_pulso,1);zeros(floor((length(tline)-L_pulso)/2)+1,1)];
            if (PLOT_TX)
               figure
               plot(x_t)
	       title("TX")
            end
            outputTxPulsed = x_t;
        end
    end
end


