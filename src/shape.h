#pragma once

class Shape
{
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual std::string info() = 0;
    virtual ~Shape() {}
};

