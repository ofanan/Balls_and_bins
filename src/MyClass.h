#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <vector>
using std::vector;
class MyClass {
    int size;
    vector<int> vec;
    MyClass(int m_size);
};

MyClass::MyClass(int m_size) : size(m_size), vec(m_size, 0);

#endif
