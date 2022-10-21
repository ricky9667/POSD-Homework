#pragma once

class Iterator;
class IteratorFactory;
class Shape
{
public:
    virtual ~Shape() {}
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual std::string info() = 0;
    virtual Iterator *createIterator(IteratorFactory *factory) = 0;
    virtual Iterator *createDFSIterator() = 0;
    virtual Iterator *createBFSIterator() = 0;

    virtual void addShape(Shape *shape)
    {
        throw std::string("Unable to add shape, please override this function if needed.");
    }

    virtual void deleteShape(Shape *shape)
    {
        throw std::string("Unable to delete shape, please override this function if needed.");
    }
};
