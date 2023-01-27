%% Constantes

%%% Transmisor Tx
PTX = 50e-3; %W
CHIRP_BW = 2e9; %Hz
MAX_RANGE = 300; %m
T_WAIT = 2*MAX_RANGE/3e8; %s
Q_ELECT= 1.6e-19; %C
T_MEAS = 5e-6; %s
T_0 = T_MEAS + T_WAIT; %s Duracion entera del chirp
CHIRP_SLOPE =  CHIRP_BW/T_0; % gamma

%%% Canal
range = 250; %m Rango, luego del canal
rho = 0.1; % Reflectividad, luego del canal

%%% Receptor Rx

ARX = pi*(2.54e-2/2)^2; % 1 in de diametro Apertura del receptor
LAMBDA0 = 1550e-9; % m
OMEGA0 = 3e8/LAMBDA0; % rad/s
RPD = 0.8; % A/W
FS = 3*CHIRP_BW; % Frecuencia de muestreo
NCELLS =  FS*T_MEAS; %% EL MUESTREO ESTA MUY ALTO, HABRIA QUE PASARLO POR UN FILTRO PASA BAJOS
FS = NCELLS/T_MEAS; % OJO
TS = 1/FS; % Periodo de muestreo
NFFT = ceil(8*NCELLS);

%%% Simulacion
T_SIM = ceil(T_0*FS); % Tiempo total de la simulación
tline = TS.*(0:T_SIM-1)'; % Vector de tiempo del tiempo total de la simulacion
