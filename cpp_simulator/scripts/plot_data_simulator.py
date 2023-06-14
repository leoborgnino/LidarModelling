import matplotlib.pyplot as plt

PLOT_TX = True
PLOT_CHANNEL = True
PLOT_RX = True

with open('./logs/tx_output.log') as f:
    lines = f.readlines()
    tx_signal = lines[0].split()
    tx_signal = [float(ii) for ii in tx_signal]

with open('./logs/channel_output.log') as f:
    lines = f.readlines()
    channel_signal = lines[0].split()
    channel_signal = [float(ii) for ii in channel_signal]

with open('./logs/rx_output.log') as f:
    lines = f.readlines()
    rx_signal = lines[0].split() 
    rx_signal = [float(ii) for ii in rx_signal]
   
tline = [ii for ii in range(len(tx_signal))]
plt.figure()
plt.plot(tline,tx_signal)
plt.savefig("debug0.png",dpi=500)
plt.figure()
plt.plot(tline,channel_signal)
plt.savefig("debug1.png",dpi=500)
plt.figure()
plt.plot(tline,rx_signal)
plt.savefig("debug2.png",dpi=500)


plt.figure()
plt.plot(tline,tx_signal)
plt.plot(tline,channel_signal)
plt.plot(tline,rx_signal)
plt.savefig("debug3.png",dpi=500)

