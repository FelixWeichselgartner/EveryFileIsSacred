def zeroPadding(function, n):
    for x in range(n):
        function.append(0)
    return function

def zeroPaddingToNextPOW2N(function):
    length = len(function)
    n = 1
    while length > pow(2, n):
        n += 1 
    #print(f'n = {n}')
    add = pow(2, n) - length
    #print(f'length {length} + add {add} = {length + add} == {pow(2, n)}')
    function = zeroPadding(function, add)
    return function
    
from math import pi

def main():
    #signal x
    x = []
    #making a dc signal with 5V here
    amount = 10
    n = 0
    inkrement = 2*pi/amount
    i = 0
    for i in range(amount):
        x.append(5)
        n = n + inkrement

    N = len(x)

    #original signal
    print(f'signal: x = {x}\n\n')

    x = zeroPaddingToNextPOW2N(x)

    #after zero padding
    print(f'signal: x = {x}\n\n')

if __name__ == "__main__":
    main()