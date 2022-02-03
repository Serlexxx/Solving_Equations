#pragma once
// ���� data.h, ��������� ����� data, C++
#include <vector>
using namespace std;       // ������������ ��� std
typedef unsigned int uint; // ����������� �����
template<class Type>
class Data {
public: // �������� �������� � ������
    Data(uint ms) {// �����������
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
    ~Data() {} // ����������
    // ������ ��� ��������������� �������
    uint sizes() { return (msize); }
    void savA(uint j, uint i, Type val) { matA.at(j).at(i) = val; }
    void savB(uint j, Type val) { vecB.at(j) = val; }
    void savX(uint j, Type val) { vecX.at(j) = val; }
    Type readA(uint j, uint i) { return (matA.at(j).at(i)); }
    Type readB(uint j) { return (vecB.at(j)); }
    Type readX(uint j) { return (vecB.at(j)); }
protected: // ���������� �������� � ������
    typedef vector<Type> vType; // ��� ������ ���� Type
    typename typedef vector<Type>::iterator pvType; // �������� ��� ������� ���� Type
    vector<vType> matA; // ������� ������������� A
    vType vecB; // ������ ������ ������ B
    vType vecX; // ������ ������� X
    uint msize; // ������ ������ � ��������
};