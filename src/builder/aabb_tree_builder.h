#pragma once

#include "../shape.h"
#include "../triangle.h"
#include "../circle.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../visitor/closest_shape_finder.h"

class AABBTreeBuilder
{
private:
    Shape *_tree = nullptr;

public:
    void insertTriangle(Point *common_point, Point *v1_point, Point *v2_point)
    {
        Triangle *triangle = new Triangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));

        if (_tree == nullptr)
        {
            _tree = triangle;
        }
        else
        {
            // closest shape finder
        }
    }

    void insertCircle(const Point *center, const Point *to_radius)
    {
        Circle *circle = new Circle(
            new TwoDimensionalVector(center, to_radius));

        if (_tree == nullptr)
        {
            _tree = circle;
        }
        else
        {
            // closest shape finder
        }
    }

    void insertRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
    {
        Rectangle *rectangle = new Rectangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));

        if (_tree == nullptr)
        {
            _tree = rectangle;
        }
        else
        {
            // closest shape finder
        }
    }

    Shape *getTree() const
    {
        return _tree;
    }
};
