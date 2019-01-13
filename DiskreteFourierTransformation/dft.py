from math import pi
from cmath import exp

def angle(X):
    #return arctan2(X[i].imag, X[i].real)
    pass
    
def dft(x):
    N = len(x)
    X = [None] * N
    l = 0
    wExponent = 1j*(-2)*pi/(N)
    for l in range(N):
        k = 0
        temp = 0
        for k in range(N):
            temp = x[k]*exp(wExponent*k*l) + temp
        X[l] = temp
    return X

def fft(x):
    N = len(x)
    max = int(N/2)

    #decimation in time
    xs = [None] * max
    xss = [None] * max

    k = 0
    for k in range(max):
        xs[k] = x[2*k]
        xss[k] = x[2*k + 1]

    #fourier transform those both parts
    XS = dft(xs)
    XSS = dft(xss)

    #add both together to actual fourier transformation
    X = [None] * N
    l = 0
    wExponent = 1j*2*pi/N*(-1)
    for l in range(max):
        X[l] = XS[l] + exp(wExponent*l)*XSS[l]

    l = 0
    for l in range(max):
        X[l + max] = XS[l] - exp(wExponent*l)*XSS[l]
    
    return X