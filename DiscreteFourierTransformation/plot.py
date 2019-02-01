import numpy as np
import matplotlib.pyplot as plt

def singlePlot(function):
    maximum = max(function)
    
    plt.figure(1)

    s = plt.subplot(211)
    s.set_ylim([-maximum, maximum])
    s.set_xlabel('time [s]')
    s.set_ylabel('signal')
    x = np.arange(len(function))
    plt.plot(x, function)

    plt.show()
    plt.clf() 

def plot(signal, fourier, maximum):
    """plots the original signal along with the frequencies of that signal
    
    Arguments:
        signal {array} -- an array in which your signal data is stored
        fourier {array} -- an array in which the fourier coefficients of your signal is stored
        maximum {integer} -- the maximum y and -y of the signal and therefore the coordinate system
    """

    plt.figure(1)

    s = plt.subplot(211)  # signal
    s.set_ylim([-maximum, maximum])
    s.set_xlabel('time [s]')
    s.set_ylabel('signal')
    x = np.arange(len(signal))
    plt.plot(x, signal)

    b = plt.subplot(212)  # frequencies
    b.set_xscale('log')
    b.set_xlabel('frequency [Hz]')
    b.set_ylabel('|amplitude|')
    plt.plot(abs(fourier))

    #savename = filename + '_fourier.png'
    #plt.savefig(savename.format(1))
    plt.show()
    plt.clf() 