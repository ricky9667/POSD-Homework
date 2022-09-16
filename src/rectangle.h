#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : public Shape
{
private:
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec) 
    {
        _lengthVec = lengthVec;
        _widthVec = widthVec;
    }

    ~Rectangle()
    {
        if (_lengthVec != nullptr)
            delete[] _lengthVec;
        if (_widthVec != nullptr)
            delete[] _widthVec;

        _lengthVec = nullptr;
        _widthVec = nullptr;
    }

    double length() 
    {
        return _lengthVec->length();
    }

    double width() 
    {
        return _widthVec->length();
    }

    double area() override 
    {
        return _lengthVec->length() * _widthVec->length();
    }

    double perimeter() override
    {
       return 2 * (_lengthVec->length() + _widthVec->length()); 
    }

    std::string info() override
    {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }
};

