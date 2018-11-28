#include <iostream>
#include <cmath>
using namespace std;

class Complex {
    private:
        string name;
        double vreal, vimag;
        double a, phi; //phi in degree

    public:
        //Constructor
        Complex(string n = "empty", double first = 0, double second = 0, char form = ' ') {
            if (form == 'p') {
                a = first; phi = second;
                name = n;
                calculate2();
            }
            else if (form == 'c') {
                vreal = first; vimag = second;
                name = n;
                calculate();
            }
            else {
                ;
            }
        }
        calculate() {
            const double pi = 3.14159265358979323846;
            a = sqrt(vreal * vreal + vimag * vimag);
            phi = 180 / pi * atan2(vimag, vreal);
        }
        calculate2() {
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
            cout << "Real part of " << name << " = " << vreal << endl;
            cout << "Imag part of " << name << " = " << vimag << endl;
            cout << "Amplitude of " << name << " = " << a << endl;
            cout << "Phase of " << name << " " << phi << endl;
        }

        //Overload + operator to add to complex numbers
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
};

void declare_complex() {
    string name; char form;
    cout << "How do you want to call your complex number?: ";
    cin >> name;
    cout << "Do you want to enter polar form or carthesian form (p || c)?: ";
    cin >> form;
    double amplitude, phase, real, imaginary;
    if (form == 'p') {
        cout << "enter Amplitude: ";
        cin >> amplitude;
        cout << "enter phase: ";
        cin >> phase;
        Complex Number1 = Complex(name, amplitude, phase, 'p');
        Number1.printNumber();
    }
    else if (form == 'c') {
        cout << "enter real part: ";
        cin >> real;
        cout << "enter imaginary part: ";
        cin >> imaginary;
        Complex Number1 = Complex(name, real, imaginary, 'c');
        Number1.printNumber();
    }
    else {
        cout << "wrong input";
    }
    return;
}

void overloading_test() {
    Complex number1 = Complex("number1", 1, 1, 'c');
    Complex number2 = Complex("number2", 1, 1, 'c');
    Complex number3 = Complex("number3", 0, 0, 'c');
    Complex number4 = Complex("number4", 0, 0, 'c');
    Complex number5 = Complex("number5", 0, 0, 'c');
    Complex number6 = Complex("number6", 0, 0, 'c');
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
    return;
}

int main() {
    declare_complex();
    overloading_test();
    return 0;
}