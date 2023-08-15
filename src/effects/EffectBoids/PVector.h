#ifndef PVECTOR_H
#define PVECTOR_H

#include <Arduino.h>

class PVector 
{
public:
    PVector();
    std::vector<int> get();
    void set(int x, int y);
    void add(PVector);
    void sub(PVector);
    void div(int);
    void mult(int);
    void limit(int);
    void setMag(int);

private:
    int x = 0;
    int y = 0;
};

#endif