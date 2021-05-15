'''
Created on 2010-02-25

@author: malem303
'''

import matplotlib.pyplot as plt
from imugrabber.algorithms import utils

def test_plot(y = [1,2,3], x = [1,2,3]):
    plt.figure(1)
    plt.subplot(211)
    plt.plot(x, y, '.')
    plt.subplot(212)
    plt.plot(x, y,)
    plt.show()
    
def plot_residuals(residuals, longitudes, latitudes, figure = 1):
    
    plt.figure(figure)
    plt.subplot(211)
    plt.plot(longitudes, residuals, '.')
    plt.title('Distance from unit vector')
    plt.ylabel('residuals')
    plt.xlabel('longitudes')
    
    plt.subplot(212)
    plt.plot(latitudes, residuals, '.')
    plt.ylabel('residuals')
    plt.xlabel('latitudes')
    

def plot_encoders(motion, timestamps, figure = 1):
    
    x = motion[0, :]
    y = motion[1, :]
    z = motion[2, :]
    a = motion[3, :]
    b = motion[4, :]
    
    
    plt.figure(figure)
    plt.subplot(511)
    plt.plot(timestamps, x, label='x')
    plt.ylabel('axis x')
    plt.xlabel('seconds')
    
    plt.subplot(512)
    plt.plot(timestamps, y, label='y')
    plt.ylabel('axis y')
    plt.xlabel('seconds')
    
    plt.subplot(513)
    plt.plot(timestamps, z, label='z')
    plt.ylabel('axis z')
    plt.xlabel('seconds')
    
    plt.subplot(514)
    plt.plot(timestamps, a, label='a')
    plt.ylabel('axis a')
    plt.xlabel('seconds')
    
    plt.subplot(515)
    plt.plot(timestamps, b, label='b')
    plt.ylabel('axis b')
    plt.xlabel('seconds')
    

def plot_fit(correctedMesaures, longitudes, latitudes, figure = 1):
    
    targets = utils.build_targets_matrix(longitudes, latitudes)
    
    plt.figure(figure, figsize = (15,10))
    plt.subplot(2,3,1)
    plt.plot(latitudes[0:50], targets[0, 0:50], 'b', latitudes[0:50], correctedMesaures[0, 0:50], 'r')
    plt.ylabel('axis x reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[0])
    
    plt.subplot(2,3,2)
    plt.plot(latitudes[500:550], targets[0, 500:550], 'b', latitudes[500:550], correctedMesaures[0, 500:550], 'r')
    plt.ylabel('axis x reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[500])

    plt.subplot(2,3,3)
    plt.plot(latitudes[750:800], targets[0, 750:800], 'b', latitudes[750:800], correctedMesaures[0, 750:800], 'r')
    plt.ylabel('axis x reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[750])
    
    plt.subplot(2,3,4)
    plt.plot(latitudes[0:50], targets[2, 0:50], 'b', latitudes[0:50], correctedMesaures[2, 0:50], 'r')
    plt.ylabel('axis z reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[0])
    
    plt.subplot(2,3,5)
    plt.plot(latitudes[500:550], targets[2, 500:550], 'b', latitudes[500:550], correctedMesaures[2, 500:550], 'r')
    plt.ylabel('axis z reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[500])

    plt.subplot(2,3,6)
    plt.plot(latitudes[750:800], targets[2, 750:800], 'b', latitudes[750:800], correctedMesaures[2, 750:800], 'r')
    plt.ylabel('axis z reading')
    plt.xlabel('angle b @ angle a = %d' % longitudes[750])
    
    
def plot_motion(correctedMeasures, timestamps, title = 'Gyroscope raw rates', figure = 1, xAxisRange = (0, 5.0), yAxisRange = 1.0):
    
    aSamples, bSamples, cSamples = correctedMeasures[0,:], correctedMeasures[1,:], correctedMeasures[2,:]
    
    plt.figure(figure)
    plt.subplot(311)
    plt.plot(timestamps, aSamples, label='aMotion')
    plt.title(title)
    plt.ylabel('axis a reading')
    plt.xlabel('seconds')
    plt.axis([xAxisRange[0], xAxisRange[1], -yAxisRange, yAxisRange])
    plt.legend(['target', 'measured'])
    
    plt.subplot(312)
    plt.plot(timestamps, bSamples, label='bMotion')
    plt.ylabel('axis b reading')
    plt.xlabel('seconds')
    plt.axis([xAxisRange[0], xAxisRange[1], -yAxisRange, yAxisRange])
    
    plt.subplot(313)
    plt.plot(timestamps, cSamples, label='cMotion')
    plt.ylabel('axis c reading')
    plt.xlabel('seconds')
    plt.axis([xAxisRange[0], xAxisRange[1], -yAxisRange, yAxisRange])
    

    
def plot_targets(targetVelocities, timestamps, figure = 1, xAxisRange = (0, 5.0), yAxisRange = 1.0):
                                
    aTargets, bTargets, cTargets = targetVelocities[:, 0], targetVelocities[:, 1], targetVelocities[:, 2]
    
    plt.figure(figure)
    plt.subplot(311)
    plt.plot(timestamps, aTargets, label = 'aTarget')
    
    plt.subplot(312)
    plt.plot(timestamps, bTargets)
    
    plt.subplot(313)
    plt.plot(timestamps, cTargets)
    
def plot_samplesByLabel(samplesByLabel, xAxisLabel, labelsToExclude = ['s', 't', 'timestamps', 'T'], figure = 1):
    
    x = samplesByLabel[xAxisLabel]
    
    plt.figure(figure)
    
    legends = []
    for label, samples in samplesByLabel.iteritems():
        if(label not in labelsToExclude) :
            plt.plot(x, samples)
            legends.append(label)
    
    plt.legend(legends)


        
def show_figures():
    
    plt.show()