from dft import dft, fft
from math import sin, pi, pow
from numpy import arctan2, angle
from numpy import angle as npangle
from numpy import fft as npfft

"""
to do list:
    phase does not return right results yet
"""

if __name__ == "__main__":
    #signal x
    x = []

    #making signal a sine wave 
    amount = 8
    n = 0
    inkrement = 2*pi/amount
    i = 0
    for i in range(amount):
        x.append(sin(n)*5)
        n = n + inkrement

    N = len(x)

    #original signal
    print(f'signal: x = {x}')

    #if my ouput is the same it highly possible that is correct
    #try out yourself with the file ProofItWorks.m
    print('Octave-Output:')
    print('fft(Amplitude) = 1.6823e-16   2.0000e+01   1.4662e-15   1.7764e-15   1.0564e-15   1.7764e-15   1.4662e-15   2.0000e+01')
    print('fft(Phase)     = 0.00000     -1.57080     -1.13998     -1.56195      0.00000      1.56195      1.13998      1.57080')
    #you can also try numpy fft.fft()
    #print(f'Numpy-fft:\n{abs(npfft.fft(x))}')

    #Diskrete-Fourier-Transformation
    X = dft(x)

    print('Diskrete-Fourier-Transformation:')
    #print(f'X = {X}')

    #amplitude and phase
    A = [None] * N
    p = [None] * N
    i = 0
    for i in range(len(X)):
        temp1 = abs(X[i])
        A[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        temp2 = arctan2(X[i].imag, X[i].real)
        #temp2 = npangle(X[i])
        p[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #print(p[i])
    
    print(f'Amplitude: A = {A}')
    print(f'Phase: p = {p}')

    #Fast-Fourier-Transformation
    X2 = fft(x)

    print('Fast-Fourier-Transformation:')
    #print(f'X2 = {X2}')

    #amplitude and phase
    A2 = [None] * N
    p2 = [None] * N
    i = 0
    for i in range(len(X2)):
        temp1 = abs(X2[i])
        A2[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        temp2 = arctan2(X2[i].imag, X2[i].real)
        #temp2 = npangle(X2[i])
        p2[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
    
    print(f'Amplitude: A2 = {A2}')
    print(f'Phase: p2 = {p2}')
    