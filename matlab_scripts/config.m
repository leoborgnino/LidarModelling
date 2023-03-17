%% Constantes

%%% Transmisor Tx

SettingsTx = struct('PTX'        ,           50e-3, ... % Watts
                    'CHIRP_BW'   ,             2e9, ... % Hz
                    'MAX_RANGE'  ,             300, ... % m
                    'Q_ELECT'    ,         1.6e-19, ... %C
                    'T_MEAS'     ,            5e-6 ... %s
                   )

SettingsTxPulsed = struct('PTX'        ,           50e-3, ... % Watts
                          'TAU_SIGNAL' ,            5e-9, ... % s
                          'LAMBDA0'    ,          950e-9, ... % m
                          'Q_ELECT'    ,         1.6e-19 ...  % C
                          )

%%% Receptor Rx
SettingsRx = struct( 'ARX'    , pi*(2.54e-2/2)^2, ... % 1 in de diametro Apertura del receptor
                     'LAMBDA0',          1550e-9, ... % m
                     'RPD'    ,              0.8, ... % A/W
                     'FS'     ,            3*2e9  ... % 3*CHIRP_BW TX  Frecuencia de muestreo
                     )
