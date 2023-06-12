classdef ChannelTop
    %CHANNELTOP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        ARX;
        FS;
        LAMBDA0;
        PULSED;
	MAX_RANGE;
    end
    
    methods
    function obj = ChannelTop(ARX,FS,LAMBDA0, PULSED, MAX_RANGE)
            %CHANNELTOP Construct an instance of this class
            %   Detailed explanation goes here
            obj.ARX = ARX;
            obj.FS = FS;
            obj.LAMBDA0 = LAMBDA0;
            obj.PULSED = PULSED;
	    obj.MAX_RANGE = MAX_RANGE;
        end
        
        function outputCh = ProcessChannel(obj,tline,tx_signal,range, rho,PLOT_CH)            
            %%% Canal
            tau = 2*range/3e8;
            delay_samples = round(tau*obj.FS);
            real_tau = delay_samples*(1/obj.FS);
            real_range = real_tau*3e8/2;

            power_gain = rho*obj.ARX/(4*pi*real_range.^2);
            delta_phase = 3e8/obj.LAMBDA0.*real_tau;

	    if (obj.PULSED)
              ch_out = sqrt(power_gain) .* [zeros(delay_samples,1); tx_signal] .* exp(-1j*delta_phase);
	      % Fixed Length
	      zeros_extra = round(2*obj.MAX_RANGE/3e8)-length(ch_out);
	      ch_out = [ch_out; zeros(zeros_extra,1)];
	    else
              ch_out = sqrt(power_gain) .* [zeros(delay_samples,1); tx_signal(1:end-delay_samples)] .* exp(-1j*delta_phase);	      
	    end
            
            if (PLOT_CH)
                figure
                plot(tx_signal);
                hold all
                plot(ch_out);
                title("CHANNEL")
            end
            outputCh = ch_out;
        end
    end
end

