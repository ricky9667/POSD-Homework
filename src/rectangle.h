#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"
#include "iterator/iterator.h"

class Rectangle : public Shape
{
private:
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec) 
    {
        if (lengthVec->dot(widthVec) != 0)
            throw std::string("Cannot initialize Rectangle without orthogonal vectors.");

        if (!lengthVec->isConnected(widthVec))
            throw std::string("Cannot initialized Rectangle with disconnected vectors.");

        _lengthVec = lengthVec;
        _widthVec = widthVec;
    }

    double length() 
    {
        return _lengthVec->length();
    }

    double width() 
    {
        return _widthVec->length();
    }

    double area() const override 
    {
        return _lengthVec->length() * _widthVec->length();
    }

    double perimeter() const override
    {
       return 2 * (_lengthVec->length() + _widthVec->length()); 
    }

    std::string info() override
    {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }

    Iterator *createDFSIterator() override {}

    Iterator *createBFSIterator() override {}

    void addShape(Shape *shape) override {}

    void deleteShape(Shape *shape) override {}
};

