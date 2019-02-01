from dft import dft, fft, angle
from math import sin, pi, pow
from numpy import arctan2, around, max
from numpy import angle as npangle
from numpy import fft as npfft
import plot as plt

"""
to do list:
    phase does not return right results yet -> fault: python returns different values for angle(4, 0) and angle(4, -0)
    modulo 2pi for angles to get values in ]-pi;pi]

    abs is actually sqrt(re^2 + im^2)
        own implementation
"""

def DC_TEST():
    print('DC TEST:\n\n')

    #signal x
    x = []
    #making a dc signal with 5V here
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
    NUMPYFFT = around(npfft.fft(x), decimals=6)
    print(f'NumpyFFT = {NUMPYFFT}\n')
    print(f'Amplitude = {around(abs(NUMPYFFT), decimals=6)}')
    print(f'Phase = {around(npangle(NUMPYFFT), decimals=6)}\n\n')

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
        A[i] = temp1
        temp2 = angle(X[i])
        p[i] = temp2
    
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
        A2[i] = temp1
        temp2 = angle(X[i])
        p2[i] = temp2
    print(f'Amplitude: A2 = {A2}')
    print(f'Phase: p2 = {p2}\n\n\n')

    plt.plot(x, X, max(x))

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
    print('fft(Phase)     = 0.00000     -1.57080     -1.13998     -1.56195      0.00000      1.56195      1.13998      1.57080\nthe phase is actually false\n\n')
    #you can also try numpy fft.fft()
    NUMPYFFT = around(npfft.fft(x), decimals=6)
    print(f'NumpyFFT = {NUMPYFFT}\n')
    print(f'Amplitude = {around(abs(NUMPYFFT), decimals=6)}')
    print(f'Phase = {around(npangle(NUMPYFFT), decimals=6)}\n\n')

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
        A[i] = temp1
        temp2 = angle(X[i])
        p[i] = temp2
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
        A2[i] = temp1
        temp2 = angle(X[i])
        p2[i] = temp2
    
    print(f'Amplitude: A2 = {A2}')
    print(f'Phase: p2 = {p2}\n\n\n')

    plt.plot(x, X, max(x))

def AC_TEST_with_zero_padding():
    print('AC TEST with zero padding:\n\n')   

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

    for i in range (amount*4):
        x.append(0)

    N = len(x)

    #original signal
    print(f'signal: x = {x}\n\n')

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
        A[i] = temp1
        temp2 = angle(X[i])
        p[i] = temp2
    
    #dividing by 1/N is not right anymore because of zero padding
    X = X * N/8

    print(f'Amplitude: A = {A}')
    print(f'Phase: p = {p}\n\n')

    plt.plot(x, X, max(x))

if __name__ == "__main__":
    DC_TEST()
    AC_TEST()
    AC_TEST_with_zero_padding()