import matplotlib.pyplot as plt
import os

PLOT_TX = True
PLOT_CHANNEL = True
PLOT_RX = True

def read_signal (name):
    with open('./logs/'+name) as f:
        lines = f.readlines()
        signal = lines[0].split()
        signal = [float(ii) for ii in signal]
        return signal


plot = ['tx_output','channel_output','rx_output']

signals = []
files = os.listdir('./logs')
for i in plot:
    signals_tmp = []
    for j in files:
        if i in j:
            signals_tmp.append(read_signal(j))
    signals.append(signals_tmp)

for j in range(len(signals)):    
    plt.figure()
    for i in range(len(signals[1])):
        plt.plot(signals[j][i][-20000:])
    plt.show()
    #plt.savefig("debug"+str(j)+".png",dpi=500)
