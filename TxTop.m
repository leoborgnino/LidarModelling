classdef TxTop
    %TX_TOP Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        PTX = 50e-3; %W
        CHIRP_BW = 2e9; %Hz
        MAX_RANGE = 300; %m
        Q_ELECT= 1.6e-19; %C
        T_MEAS = 5e-6; %s
        T_WAIT;
        T_0;
        CHIRP_SLOPE;
    end
    
    methods
        function obj = tx_top(PTX,CHIRP_BW)
            %TX_TOP Construct an instance of this class
            %   Detailed explanation goes here
            obj.PTX = PTX;
            obj.CHIRP_BW = CHIRP_BW;
            obj.T_WAIT = 2*obj.MAX_RANGE/3e8; %s
            obj.T_0 = obj.T_MEAS + obj.T_WAIT; %s Duracion entera del chirp
            obj.CHIRP_SLOPE =  obj.CHIRP_BW/obj.T_0; % gamma
         end
        
        function outputArg = method1(obj,datapath)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.PTX + obj.CHIRP_BW;
        end
    end
end

