from dft import dft, fft
from math import sin, pi, pow
from numpy import arctan2, angle, around
from numpy import angle as npangle
from numpy import fft as npfft

"""
to do list:
    phase does not return right results yet
    modulo 2pi for angles to get values in ]-pi;pi]
"""

def DC_TEST():
    print('DC TEST:\n\n')

    #signal x
    x = []
    #making signal a sine wave 
    amount = 8
    n = 0
    inkrement = 2*pi/amount
    i = 0
    for i in range(amount):
        x.append(5)
        n = n + inkrement

    N = len(x)

    #original signal
    print(f'signal: x = {x}\n\n')

    #if my ouput is the same it highly possible that is correct
    print(f'Numpy-fft:\n{around(abs(npfft.fft(x)), decimals=6)}')
    print(f'phase with numpy = {around(angle(npfft.fft(x)), decimals=6)}\n\n')

    #Diskrete-Fourier-Transformation
    X = around(dft(x), decimals=6)

    print('Diskrete-Fourier-Transformation:')
    print(f'X = {X}\n')

    #amplitude and phase
    A = [None] * N
    p = [None] * N
    i = 0
    for i in range(len(X)):
        temp1 = abs(X[i])
        A[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #temp2 = around(arctan2(X[i].imag, X[i].real), decimals=6)
        temp2 = around(npangle(X[i]), decimals=6)
        p[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #print(p[i])
    
    print(f'Amplitude: A = {A}')
    print(f'Phase: p = {p}\n\n')

    #Fast-Fourier-Transformation
    X2 = around(fft(x), decimals=6)

    print('Fast-Fourier-Transformation:')
    print(f'X2 = {X2}\n')

    #amplitude and phase
    A2 = [None] * N
    p2 = [None] * N
    i = 0
    for i in range(len(X2)):
        temp1 = abs(X2[i])
        A2[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #temp2 = around(arctan2(X2[i].imag, X2[i].real), decimals=6)
        temp2 = around(npangle(X2[i]), decimals=6)
        p2[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
    
    print(f'Amplitude: A2 = {A2}')
    print(f'Phase: p2 = {p2}\n\n\n')

def AC_TEST():
    print('AC TEST:\n\n')   

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
    print(f'signal: x = {x}\n\n')

    #if my ouput is the same it highly possible that is correct
    #try out yourself with the file ProofItWorks.m
    print('Octave(Matlab)-Output:')
    print('fft = 0.00000 +  0.00000i   -0.00000 - 20.00000i    0.00000 -  0.00000i    0.00000 -  0.00000i    0.00000 +  0.00000i    0.00000 +  0.00000i    0.00000 +  0.00000i   -0.00000 + 20.00000i\n')
    print('fft(Amplitude) = 1.6823e-16   2.0000e+01   1.4662e-15   1.7764e-15   1.0564e-15   1.7764e-15   1.4662e-15   2.0000e+01')
    print('fft(Phase)     = 0.00000     -1.57080     -1.13998     -1.56195      0.00000      1.56195      1.13998      1.57080\n\n')
    #you can also try numpy fft.fft()
    #print(f'Numpy-fft:\n{abs(npfft.fft(x))}')
    #print(f'phase with numpy = {around(angle(npfft.fft(x)), decimals=6)}')

    #Diskrete-Fourier-Transformation
    X = around(dft(x), decimals=6)

    print('Diskrete-Fourier-Transformation:')
    print(f'X = {X}\n')

    #amplitude and phase
    A = [None] * N
    p = [None] * N
    i = 0
    for i in range(len(X)):
        temp1 = abs(X[i])
        A[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #temp2 = arctan2(X[i].imag, X[i].real)
        temp2 = around(npangle(X[i]), decimals=6)
        p[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #print(p[i])
    
    print(f'Amplitude: A = {A}')
    print(f'Phase: p = {p}\n\n')

    #Fast-Fourier-Transformation
    X2 = around(fft(x), decimals=6)

    print('Fast-Fourier-Transformation:')
    print(f'X2 = {X2}\n')

    #amplitude and phase
    A2 = [None] * N
    p2 = [None] * N
    i = 0
    for i in range(len(X2)):
        temp1 = abs(X2[i])
        A2[i] = temp1 #if temp1 > pow(10, -13) else 0 #comment this out later -> just better visualization
        #temp2 = arctan2(X2[i].imag, X2[i].real)
        temp2 = around(npangle(X2[i]), decimals=6)
        p2[i] = temp2 #if temp2 > pow(10, -13) else 0 #comment this out later -> just better visualization
    
    print(f'Amplitude: A2 = {A2}')
    print(f'Phase: p2 = {p2}\n\n\n')

if __name__ == "__main__":
    DC_TEST()
    AC_TEST()