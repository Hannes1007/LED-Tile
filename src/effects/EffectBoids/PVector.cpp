#include "PVector.h"

PVector::PVector()
{
 
}

std::vector<int> PVector::get()
{
    std::vector<int> returnVector;
    returnVector.push_back(x);
    returnVector.push_back(y);

    return returnVector;
}

void PVector::set(int xValue, int yValue)
{
    x = xValue;
    y = yValue;
}

void PVector::add(PVector vector)
{
    x = x + vector.get().at(0);
    y = y + vector.get().at(1);
}

void PVector::sub(PVector vector)
{
    x = x - vector.get().at(0);
    y = y - vector.get().at(1);
}

void PVector::div(int div)
{
    if(div != 0)
    {
        x = x / div;
        y = y / div;
    }
}

void PVector::mult(int mult)
{
    x = x * mult;
    y = y * mult;
}

void PVector::setMag(int newMag)
{
    float mag = sqrt(pow(x,2) + pow(y,2));
    x = x * newMag/mag;
    y = y * newMag/mag;  
}

void PVector::limit(int limit)
{
    float mag = sqrt(pow(x,2) + pow(y,2));
    if (mag > limit)
    {
        x = x * limit/mag;
        y = y * limit/mag; 
    }
}