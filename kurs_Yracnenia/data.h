#pragma once
// файл data.h, шаблонный класс data, C++
#include <vector>
using namespace std;       // пространство имён std
typedef unsigned int uint; // беззнаковый целый
template<class Type>
class Data {
public: // открытые свойства и методы
    Data(uint ms) {// конструктор
        try {
            msize = ms;
            vecB.assign(msize, (Type)0);
            vecX.assign(msize, (Type)0);
            matA.resize(msize);
            for (uint i = 0; i < msize; i++) matA.at(i).assign(msize, (Type)0);
        }
        catch (...) {
            msize = 0;
            throw;
        }
    }
    ~Data() {} // деструктор
    // методы для манипулирования данными
    uint sizes() { return (msize); }
    void savA(uint j, uint i, Type val) { matA.at(j).at(i) = val; }
    void savB(uint j, Type val) { vecB.at(j) = val; }
    void savX(uint j, Type val) { vecX.at(j) = val; }
    Type readA(uint j, uint i) { return (matA.at(j).at(i)); }
    Type readB(uint j) { return (vecB.at(j)); }
    Type readX(uint j) { return (vecB.at(j)); }
protected: // защищённые свойства и методы
    typedef vector<Type> vType; // тип вектор типа Type
    typename typedef vector<Type>::iterator pvType; // итератор для вектора типа Type
    vector<vType> matA; // матрица коэффициентов A
    vType vecB; // вектор правых частей B
    vType vecX; // вектор искомый X
    uint msize; // размер матриц и векторов
};