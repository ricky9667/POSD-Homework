#pragma once

#include <list>

#include "shape.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/bfs_compound_iterator.h"

class CompoundShape : public Shape
{
private:
    std::list<Shape *> _shapes;

public:
    CompoundShape(Shape **shapes) 
    {
        for (Shape* shape = *shapes; shape != nullptr; shape++)
            _shapes.push_back(shape);
    }

    ~CompoundShape() {}

    double area() const override
    {
        double totalArea = 0;
        for (auto shape : _shapes)
            totalArea += shape->area();
        return totalArea;
    }

    double perimeter() const override
    {
        double totalPerimeter = 0;
        for (auto shape : _shapes)
            totalPerimeter = shape->perimeter();
        return totalPerimeter;
    }

    std::string info() override
    {
        std::string shapeInfo = (_shapes.front())->info();
        for (auto it = _shapes.begin(); it != _shapes.end(); it++)
        {
            shapeInfo += ", ";
            shapeInfo += (*it)->info();
        }
    }

    Iterator* createDFSIterator() override {}

    Iterator* createBFSIterator() override {}

    void addShape(Shape* shape) override {}

    void deleteShape(Shape* shape) override {}
};

