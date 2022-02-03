#pragma once
#define DEBUG true
#define e 0.005
#include <iostream>
#include <math.h>
#include "data.h"
// класс некоторых действий линейной алгебры
template<class Type> class algorithm : public Data<Type> {
public: // открытые свойства и методы
    algorithm(uint ms) : Data<Type>(ms) {} // конструктор

    void bigelem() { // формирование системы с ведущим элементом
        uint k, i, j, kmax;
        Type maxval;
        for (k = 0; k <  Data<Type>::sizes(); k++) {
            maxval =  Data<Type>::readA(k, k);
              //  matA.at(k).at(k); // проход по диагонали
            kmax = k;
            for (j = k + 1; j <  Data<Type>::sizes(); j++) { // больший элемент в столбце
                if (abs( Data<Type>::readA(j,k)) > abs(maxval)) {/*matA.at(j).at(k)*/
                    maxval =  Data<Type>::readA(j, k);//matA.at(j).at(k);
                    kmax = j;
                }
            }
            if (kmax != k) { // если требуется перестановка
                for (i = 0; i <  Data<Type>::sizes(); i++) { // перестановка строк матрицы A
                    maxval =  Data<Type>::readA(k, i); // matA.at(k).at(i)
                     Data<Type>::savA(k, i,  Data<Type>::readA(kmax, i)); // matA.at(k).at(i) = matA.at(kmax).at(i)
                     Data<Type>::savA(kmax, i, maxval); // matA.at(kmax).at(i) = maxval
                }
                maxval =  Data<Type>::readB(k);// vecB.at(k); // перестановка элементов вектора B
                 Data<Type>::savB(k,  Data<Type>::readB(kmax)); // vecB.at(k) = vecB.at(kmax)
                 Data<Type>::savB(kmax, maxval); // vecB.at(kmax) = maxval
            }
        }
    }

    void gauss() {  // метод исключения Гаусса
        int k, i, j;
        Type temp;
        for (k = 1; k <  Data<Type>::sizes(); k++) { // прямой ход
            for (i = k; i <  Data<Type>::sizes(); i++) {
                temp =  Data<Type>::matA.at(i).at(k - 1) /  Data<Type>::matA.at(k - 1).at(k - 1);
                for (j = 0; j <  Data<Type>::sizes(); j++) {
                     Data<Type>::matA.at(i).at(j) =  Data<Type>::matA.at(i).at(j) - temp *  Data<Type>::matA.at(k - 1).at(j);
                }
                 Data<Type>::vecB.at(i) =  Data<Type>::vecB.at(i) - temp *  Data<Type>::vecB.at(k - 1);
            }
            if(DEBUG == true) {
                cout << "Forward stroke, cycle: " << k << endl;
                prnls();
            }

        }
    if(DEBUG == true)
        cout << "Reverse" << endl;
    for (k =  Data<Type>::sizes() - 1; k >= 0; k--) { // обратный ход
        temp =  Data<Type>::vecB.at(k);
        for (j =  Data<Type>::sizes() - 1; j > k; j--) {
            temp -=  Data<Type>::matA.at(k).at(j) *  Data<Type>::vecX.at(j);
        }
         Data<Type>::vecX.at(k) = temp /  Data<Type>::matA.at(k).at(k);
        if(DEBUG == true)
            cout << "X[" << k << "] = " <<  Data<Type>::vecX.at(k) << endl;
        }
    }
 
    //Решение СЛАУ методом итераций
    void iter()
    {
        vector<Type> res(Data<Type>::sizes());
        int i, j;


        for (i = 0; i < Data<Type>::sizes(); i++)
        {
            res.at(i) = Data<Type>::readB(i) / Data<Type>::readA(i, i);
        }

        double eps = 0.0001;
        vector<Type> Xn(Data<Type>::sizes());
        int counter = 0;

        do {
            for (i = 0; i < Data<Type>::sizes(); i++) {
                Xn.at(i) = Data<Type>::readB(i) / Data<Type>::readA(i, i);
                for (j = 0; j < Data<Type>::sizes(); j++) {
                    if (i == j)
                        continue;
                    else {
                        Xn.at(i) -= Data<Type>::readA(i,j) / Data<Type>::readA(i, i) * res.at(j);
                    }
                }
            }

            bool flag = true;
            for (i = 0; i < Data<Type>::sizes() - 1; i++) {
                if (abs(Xn.at(i) - res.at(i)) > e) {
                    flag = false;
                    break;
                }
            }

            for (i = 0; i < Data<Type>::sizes(); i++) {
                res.at(i) = Xn.at(i);
            }

            if (flag)
                break;
            counter++;
        } while (1);
        for (i = 0; i < Data<Type>::sizes(); i++) {
            Data<Type>::savX(i, res.at(i));
        }
        cout << endl << "Count iterration: " << counter << endl;
        for (int i = 0; i < Data<Type>::sizes(); i++)
            cout << "X[" << i << "] = " << Data<Type>::vecX.at(i) << " " << endl;
    }

    void prnls() { // вывод системы в поток экрана
        int j, i;
        for (j = 0; j <  Data<Type>::sizes(); j++) {
            for (i = 0; i <  Data<Type>::sizes(); i++) {
                if ( Data<Type>::matA.at(j).at(i) < 0)
                    cout <<  Data<Type>::matA.at(j).at(i) << "*X[" << i << "]";
                else
                    cout << "+" <<  Data<Type>::matA.at(j).at(i) << "*X[" << i << "]";
            }
            cout << "=" <<  Data<Type>::vecB.at(j) << endl;
        }
    }
};