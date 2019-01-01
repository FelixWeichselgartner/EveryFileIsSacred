# documentation on usage:
# https://docs.python.org/3/library/ctypes.html

import ctypes

libfile = ctypes.CDLL('./libfile.so')

libfile.ArithM.restype = ctypes.c_float
def ctypes_arithm(a, b):
    return libfile.ArithM(ctypes.c_float(a), ctypes.c_float(b))

libfile.parallel.restype = ctypes.c_float
def ctypes_parallel(a, b):
    return libfile.parallel(ctypes.c_float(a), ctypes.c_float(b))

def ctypes_sum(a, b):
    return libfile.sum(ctypes.c_int(a), ctypes.c_int(b))

def ctypes_absolute(a):
    return libfile.absolute(ctypes.c_int(a))

#absolute value of number
print(f'the absolute value of {-20} is {ctypes_absolute(-20)}')

#sum of 2 numbers
x, y = 5, 4
print(f'the sum of {x} and {y} is {ctypes_sum(x, y)}')

#arithm average of 2 values
a, b = float(2.8431), float(20.15686)
print(f'the arithm average of {a} and {b} is {ctypes_arithm(a, b)}')

#parallel resistance of 50 Ohm and 50 Ohm
first = float(50.0)
second = float(50.0)
resistance = ctypes_parallel(first, second)
print(f'{first}Ohm parallel to {second}Ohm = {resistance}Ohm')