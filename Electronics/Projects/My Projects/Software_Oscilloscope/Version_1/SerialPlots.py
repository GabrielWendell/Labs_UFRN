'''
Uses the SocketPlot-Test example to plot a sine wave.
Run SocketPlot-Test.py on a different console window
'''
from SoftOscilloscope import SocketClientPlot
plot = SocketClientPlot('localhost', 5000)
plot.start()
'''

Example for serial plots
'''
from SoftOscilloscope import SerialPlot
plot = SerialPlot('COM_PORT_NUMBER', BAUD_RATE)
plot.start()

'''
Takes a generic stream and sets custom parameters
'''
from SoftOscilloscope import GenericPlot
plot = GenericPlot(
	myStream, 
	xlim=(-100,100),
	ylim=(-50, 50),
	interval=1, 
	autoscale=False,
	read_size=1)
plot.start()