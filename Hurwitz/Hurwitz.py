"""
Copyright (c) 2019 Felix Weichselgarnter

Hurwitz class to calculate stability of a
characteristic polynom of a closed loop
"""
import numpy as np

class Hurwitz:

    def __init__(self, factors):
        self.a = factors
        self.N = len(factors) - 1

        if self.a[0] < 0:
            for i in range(len(factors)):
                self.a[i] = -self.a[i]
        
        self.fillH()
        self.calcHurwitzDeterminants()
        self.checkStability()

    def getA(self, index):
        try:
            return self.a[index]
        except:
            return 0

    def fillH(self):
        m = 0
        self.H = np.zeros([self.N, self.N])
        for i in range(1, -self.N + 1, -1):
            for k in range(self.N):
                self.H[m][k] = self.getA(i + k * 2)
            m += 1

        print(f'H = \n{self.H}\n')

    def getSubMatrix(self, shape):
        sub = np.zeros([shape, shape])
        for i in range(shape):
            for k in range(shape):
                sub[i][k] = self.H[i][k]

        return sub

    def calcHurwitzDeterminants(self):
        self.HN = []
        for i in range(self.N):
            self.HN.append(np.linalg.det(self.getSubMatrix(i)))

    def checkStability(self):
        self.stable = True

        for i in range(self.N):
            if self.a[i] > 0:
                print(f'a[{i}] = {self.a[i]} > 0')
            else:
                self.stable = False
                print(f'a[{i}] = {self.a[i]} <= 0')
        print()

        i = 1
        for h in self.HN:
            if h > 0:
                print(f'H{i} = {h} > 0')
            else:
                self.stable = False
                print(f'H{i} = {h} <= 0')
            i += 1
        print()

    def getStability(self):
        return self.stable

    def printStability(self):
        print('#####################################')
        if self.stable:
            print('your polynom is stable')
        else:
            print('your polynom is not stable')
        print('#####################################')



def test():
    polynom1 = Hurwitz(np.array([0.1, 1, 2]))
    stability = polynom1.getStability()
    polynom1.printStability()

if __name__ == "__main__":
    test()