"""
**************************************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
**************************************************************
*  Date of creating this file: 22.12.2018
*  Last changes: 22.12.2018
*  creator: Felix Weichselgartner
*  purpose: building a music visualization
            with fourier-transformation
**************************************************************
*  original upload to:
*  https://github.com/FelixWeichselgartner/EveryFileIsSacred
**************************************************************
*  This is python skript which transforms music in
*  fourier coefficients to display them in a led matrix
*  This project is mainly possible, because of the fantastic
*  libraries that i could use
**************************************************************
"""

#pip install numpy
import numpy as np
#pip install scipy
import scipy.integrate
#pip install matplotlib
import matplotlib.pyplot as plt
#pip install pydub
from pydub import AudioSegment
#pip install simpleaudio
from pydub.playback import play
#pip install ffmpeg-python
import ffmpeg
#pip install ffmpeg
#+ for windows: 
#download https://ffmpeg.zeranoe.com/builds/
#and add to path

def plot(filename, signal, fourier, maximum):
    """plots the original signal along with the frequencies of that signal
    
    Arguments:
        filename {string} -- the name of the mp3 you opened -> is used to save plot to png
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

    savename = filename + '_fourier.png'
    plt.savefig(savename.format(1))
    #plt.show()
    plt.clf() 

def highestValue(array):
    """returns the hightest value of an array
    
    Arguments:
        array {array} -- the array to search the highest value in
    
    Returns:
        integer -- this is the highest value
    """

    value = 0
    for x in range(0, 8):
        if array[x] > value:
            value = array[x]
    return value

def normTo8Bit(array):
    """norms an array to a value range of 0 <= value <= 8
    
    Arguments:
        array {array} -- integer array is devided by 25'000 by standard - by the highest value if a value is higher than 25'000
    """

    norm = 25000
    if highestValue(array) > 25000:
            norm = highestValue(array)
    for x in range(0, 8):
        array[x] = int(array[x]/norm*8)

    
def main():
    """
    reads in a file and converts it to an array of values
    those are then transformed with the DFT (discrete fourier transformation)
    then the DFT array is divided in N different pieces all of same length
    those are then normed to 0 <= value <= 8 to be displayed on an led Matrix with size 8 on 8
    """

    filename = 'inmymind.mp3'
    #filename = input('what is your filename?')

    song = AudioSegment.from_mp3(filename)

    duration = len(song) / 1000 / 60
    framerate = song.frame_rate
    framewidth = song.frame_width
    framespersecond = song.frame_count()
    channel_count = song.channels
    
    print(f'length of the audio = {duration} minutes')
    print(f'the framerate = {framerate}')
    print(f'the framewidth = {framewidth} byte')
    print(f'the number of frames per second = {framespersecond}')
    print(f'the song has {channel_count} channels')

    part = song[35000:40000]

    print(f'length of the current part {len(part)/1000} seconds')

    #do for loop here through all parts of the song

    signal = part.get_array_of_samples()
    
    fourier = abs(np.fft.rfft(signal))

    #plot(filename, signal, fourier, part.max)

    #8*8 led matrix
    xlength = 8
    ledMatrix = np.zeros(xlength, dtype=int)
    print(ledMatrix)

    #humans can hear from 20Hz to 20kHz
    print(f'array length of signal = {len(signal)}')
    print(f'array length of fourier = {len(fourier)}')

    hearable = np.array([])
    hearable = fourier[0:20000]

    print(f'array length of hearable = {len(hearable)}')

    fsimpson = scipy.integrate.simps(fourier)
    print('simpsons integral of the all frequencies')
    print(fsimpson)
    hsimpson = scipy.integrate.simps(hearable)
    print('simpsons integral of the hearable frequencies')
    print(hsimpson)

    interval = 20000/xlength
    start = 0
    fslice = np.array([])
    for i in range(0, xlength):
        end = start + interval
        fslice = hearable[int(start):int(end)]
        ledMatrix[i] = scipy.integrate.simps(fslice)/1000000
        start += interval

    print('matrix before pushing values to range 0 to 8')
    print(ledMatrix)

    normTo8Bit(ledMatrix)

    print('this is the led matrix:')
    print('the value is the height and the x-position represents the frequency')
    print(ledMatrix)

    #play(song)

if __name__ == "__main__":
    main()