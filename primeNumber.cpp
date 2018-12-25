/*
**************************************************************
*  Copyright (c) 2018 Felix Weichselgartner
*  all rights reserved
**************************************************************
*  Date of creating this file: 23.12.2018
*  Last changes: 24.12.2018
*  creator: Felix Weichselgartner
*  purpose: trying out a selfmade
*           prime number calculating algorithm
**************************************************************
*  original upload to:
*  https://github.com/FelixWeichselgartner/EveryFileIsSacred
**************************************************************
*  Calculates the amount of primes numbers you tell it to
*  easy algorithm only took about 30 minutes to program
**************************************************************
*/

#include <iostream>
using namespace std;
#include <ctime>
#define AmountOfPrimeNumbersToCalculate 30000

namespace calculate {
    class calcPrimeNumbers {
    private:
        int KnownPrimeNumbers[AmountOfPrimeNumbersToCalculate] = {2};
    public:
        calcPrimeNumbers() {}

        bool possiblePrimeNumber(int number, int divide) {
            int temp = number % divide;
            if (temp == 0) {
                return false;
            } else {
                return true;
            }
        }

        void calc() {
            int start = 3;
            int divide = 0;
            bool Prime = true;
            if (AmountOfPrimeNumbersToCalculate < 1) {
                return;
            } else {
                for (int i = 1, k = start; i < AmountOfPrimeNumbersToCalculate; k++) {
                    Prime = true;
                    divide = 2;
                    while (Prime == true && divide < k) {
                        if (possiblePrimeNumber(k, divide) == false) {
                            Prime = false;
                        }
                        divide++;
                    }
                    if (Prime == true) {
                        KnownPrimeNumbers[i] = k;
                        i++;
                    }
                }
            }
        }

        void printPrimeNumbers() {
            cout << "Calculated Prime Numbers: " << endl;
            for (int i = 0; i < AmountOfPrimeNumbersToCalculate; i++) {
                cout << KnownPrimeNumbers[i] << " | ";
            }
        }
    };
}

int main() {
    time_t start = time(0);
    class calculate::calcPrimeNumbers newRun = calculate::calcPrimeNumbers();
    newRun.calc();
    cout << "The amount of time needed to calculate " << AmountOfPrimeNumbersToCalculate << " prime numbers: " << (double)difftime(time(0), start) << " seconds" << endl;
    //newRun.printPrimeNumbers();
    return 0;
}