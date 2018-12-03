#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Complex {
    private:
        double vreal, vimag;
        double a, phi; //phi in degree

    public:
        //Constructor
        Complex(double first = 0, double second = 0, char form = ' ') {
            if (form == 'p') {
                a = first; phi = second;
                calculate2();
            }
            else if (form == 'c') {
                vreal = first; vimag = second;
                calculate();
            }
            else {
                ;
            }
        }
        
        //could make those private
        void calculate() {
            const double pi = 3.14159265358979323846;
            a = sqrt(vreal * vreal + vimag * vimag);
            phi = 180 / pi * atan2(vimag, vreal);
        }
        void calculate2() {
            const double pi = 3.14159265358979323846;
            double phi_radian = phi / 180 * pi;
            vreal = a * cos(phi_radian);
            vimag = a * sin(phi_radian);
        }

        //Set functions
        double setR(double r) {
            vreal = r;
            calculate();
        }
        double setI(double i) {
            vimag = i;
            calculate();
        }
        double setA(double aa) {
            a = aa;
            calculate2();
        }
        double setPhi(double pphi) {
            phi = pphi;
            calculate2();
        }

        //Get and print functions
        double getReal() {
            return vreal;
        }
        double getImaginary() {
            return vimag;
        }
        double getAmplitude() {
            return a;
        }
        double getPhase() {
            return phi;
        }
        void printNumber() {
            cout << vreal << " + j" << vimag << endl;
            cout << a << "* exp(j * " << phi << ")" << endl;
        }

        /*
        Complex conjugate(Complex res) { 
            res.vreal = vreal; res.vimag = (-1) * vimag;
            return res; 
        }
        */

        //Kopierkonstruktor
        Complex(const Complex &copy) {
            vreal = copy.vreal;
            vimag = copy.vimag;
            a = copy.a;
            phi = copy.phi;

        }

        //Overload + operator to add to complex numbers
        //vreal & vimag is the first number
        //obj is the second number
        Complex operator + (Complex const &obj) { 
            Complex res;
            res.vreal = vreal + obj.vreal; 
            res.vimag = vimag + obj.vimag;
            res.calculate(); 
            return res; 
        }
        //subtracting objects
        Complex operator - (Complex const &obj) { 
            Complex res; 
            res.vreal = vreal - obj.vreal; 
            res.vimag = vimag - obj.vimag;
            res.calculate(); 
            return res; 
        }
        //multiplying objects
        Complex operator * (Complex const &obj) { 
            Complex res; 
            res.a = a * obj.a; 
            res.phi = phi + obj.phi;
            res.calculate2(); 
            return res; 
        }
        //dividing objects
        Complex operator / (Complex const &obj) { 
            Complex res;
            if (obj.vreal == 0 && obj.vimag == 0) {
                res.vreal = 0; res.vimag = 0;
            }
            res.vreal = (vreal * obj.vreal + vimag * obj.vimag)/(obj.vreal * obj.vreal + obj.vimag * obj.vimag);
            res.vimag = (obj.vimag * vreal - vimag * obj.vreal)/(obj.vreal * obj.vreal + obj.vimag * obj.vimag);
            res.calculate(); 
            return res; 
        }
};

Complex conjugate(Complex n) {
    Complex res; 
    res.setR(n.getReal()); res.setI((-1) * n.getImaginary());
    return res; 
}

void declare_complex() {
    char form;
    cout << "Do you want to enter polar form or carthesian form (p || c)?: ";
    cin >> form;
    double amplitude, phase, real, imaginary;
    if (form == 'p') {
        cout << "enter Amplitude: ";
        cin >> amplitude;
        cout << "enter phase: ";
        cin >> phase;
        Complex Number1 = Complex(amplitude, phase, 'p');
        Number1.printNumber();
    }
    else if (form == 'c') {
        cout << "enter real part: ";
        cin >> real;
        cout << "enter imaginary part: ";
        cin >> imaginary;
        Complex Number1 = Complex(real, imaginary, 'c');
        Number1.printNumber();
    }
    else {
        cout << "wrong input";
    }
    return;
}

void overloading_test() {
    Complex number1 = Complex(2, 1, 'c');
    Complex number2 = Complex(2, 9, 'c');
    Complex number3 = Complex(0, 0, 'c');
    Complex number4 = Complex(0, 0, 'c');
    Complex number5 = Complex(0, 0, 'c');
    Complex number6 = Complex(0, 0, 'c');
    Complex number7 = Complex(0, 0, 'c');
    cout << "number1: " << endl;
    number1.printNumber();
    cout << endl << "number2: " << endl;
    number2.printNumber();
    cout << endl << "adding both numbers: " << endl;
    number3 = number1 + number2;
    number3.printNumber();
    cout << endl << "subtracting number2 of number1: " << endl; 
    number4 = number1 - number2;
    number4.printNumber();
    cout << endl << "multiplying both numbers: " << endl;
    number5 = number1 * number2;
    number5.printNumber();
    cout << endl << "dividing first number by second numbers: " << endl;
    number6 = number1 / number2;
    number6.printNumber();
    cout << endl << "conjugate complex number of first number: " << endl;
    number7 = conjugate(number1);
    number7.printNumber();
    return;
}

void copy_test() {
    Complex number2 = Complex(2, 9, 'c');
    Complex number3 = number2;
    number3.printNumber();
}

int main() {
    //declare_complex();
    //overloading_test();
    copy_test();
    return 0;
}