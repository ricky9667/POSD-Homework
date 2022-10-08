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
    CompoundShape(Shape **shapes, int size) : _shapes(shapes, shapes + size) {}

    ~CompoundShape() {}

    double area() override
    {
        double totalArea = 0;
        for (auto shape : _shapes)
            totalArea += shape->area();
        return totalArea;
    }

    double perimeter() override
    {
        double totalPerimeter = 0;
        for (auto shape : _shapes)
            totalPerimeter += shape->perimeter();
        return totalPerimeter;
    }

    std::string info() override
    {
        std::string shapeInfo = "";
        bool isFirst = true;

        for (auto shape : _shapes)
        {
            if (isFirst)
            {
                shapeInfo += shape->info();
                isFirst = false;
            }
            else
            {
                shapeInfo += ", ";
                shapeInfo += shape->info();
            }
        }

        return "CompoundShape (" + shapeInfo + ")";
    }

    Iterator *createDFSIterator() override
    {
        return new DFSCompoundIterator<std::list<Shape *>::iterator>(_shapes.begin(), _shapes.end());
    }

    Iterator* createBFSIterator() override {}

    void addShape(Shape* shape) override
    {
        _shapes.push_back(shape);
    }

    void deleteShape(Shape* shape) override
    {
        _shapes.remove(shape);
        for (auto it : _shapes)
        {
            try 
            {
                it->deleteShape(shape);
            }
            catch (std::string exception) {}
        }
    }
};
