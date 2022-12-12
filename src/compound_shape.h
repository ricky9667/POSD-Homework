#pragma once

#include <list>
#include <set>
#include <algorithm>
#include "point.h"
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"
#include "iterator/factory/iterator_factory.h"
#include "visitor/shape_visitor.h"

class CompoundShape : public Shape
{
private:
    std::list<Shape *> _shapes;
    std::list<Shape *> _shouldBeDeletedShapes;

public:
    CompoundShape(Shape **shapes, int size) : _shapes(shapes, shapes + size) {}

    ~CompoundShape()
    {
        for (auto shape : _shapes)
            delete shape;

        for (auto shape : _shouldBeDeletedShapes)
            delete shape;
    }

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

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator(_shapes.begin(), _shapes.end());
    }

    void addShape(Shape *shape) override
    {
        _shapes.push_back(shape);
    }

    void deleteShape(Shape *shape) override
    {
        if (std::find(_shapes.begin(), _shapes.end(), shape) != _shapes.end())
        {
            _shapes.remove(shape);
            _shouldBeDeletedShapes.push_back(shape);
        }

        for (auto it : _shapes)
        {
            try
            {
                it->deleteShape(shape);
            }
            catch (std::string exception)
            {
            }
        }
    }

    std::set<Point> getPoints() override
    {
        std::set<Point> points;
        for (auto shape : _shapes)
            for (auto point : shape->getPoints())
                points.insert(point);
        return points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitCompoundShape(this);
    }

    void replace(Shape *oldShape, Shape *newShape)
    {
        for (std::list<Shape *>::iterator it = _shapes.begin(); it != _shapes.end(); it++)
        {
            if (*it == oldShape)
            {
                _shapes.insert(it, newShape);
                _shapes.erase(it);
                break;
            }
        }
    }
};
