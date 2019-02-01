from math import cos, pi

def vonHann(alpha, beta, N):
    vonHann = [None] * N
    for n in range(N):
        vonHann[n] = alpha - beta * cos(2 * pi * n / (N - 1))
    return vonHann

def hamming(N):
    alpha = 25.0/46
    beta = 1 - alpha
    return vonHann(alpha, beta , N)

from plot import singlePlot

def main():
    test = hamming(16)
    singlePlot(test)
    #mulitiply hamming(length(signal)) * signal

if __name__ == "__main__":
    main()