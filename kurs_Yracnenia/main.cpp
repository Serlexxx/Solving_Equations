#include <stdlib.h>
#include "algorithms.h"
using namespace std;
int main(int argc, char* argv[]) {
    cout << "Size of the system of equations:  ";
    int sz;
    float val;
    cin >> sz;  // порядок системы
    // объект класса шаблонного algorithm
    algorithm<float>* la1 = new algorithm<float>(sz);
    algorithm<float>* la2 = new algorithm<float>(sz);
    // ввод системы линейных уравнений
    cout << "Enter lines of system of linear equations:  " << endl;
    for (int j = 0; j < sz; j++) {
        cout << "A[" << j << ",1]+...+A[" << j << ", "
            << (sz - 1) << "]=B[" << j << "]" << endl;
        for (int i = 0; i < sz; i++) {
            cin >> val;
            la1->savA(j, i, val);
            la2->savA(j, i, val);
        }
        cin >> val;
        la1->savB(j, val);
        la2->savB(j, val);
        
        
        
    }
    for (int i = 0; i < sz; i++) {
        la2->savX(i, la2->readB(i) / la2->readA(i, i));
    }
    cout << "Linear system:" << endl;
    la1->prnls();
    la1->bigelem();
    cout << "Linear system:" << endl;
    la1->prnls();
    la1->gauss();
    la2->iter();
    delete la1;
    delete la2;
    system("pause");
    return 0;
}