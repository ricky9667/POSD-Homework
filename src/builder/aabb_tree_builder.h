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
    void insertTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
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
            ClosestShapeFinder *visitor = new ClosestShapeFinder(triangle);
            _tree->accept(visitor);

            Shape *closestShape = visitor->getClosestShape();
            CompoundShape *parent = visitor->getParent();

            Shape *shapes[] = {closestShape, triangle};
            CompoundShape *compoundShape = new CompoundShape(shapes, 2);

            if (parent == nullptr)
                _tree = compoundShape;
            else
            {
                parent->deleteShape(closestShape);
                parent->addShape(compoundShape);
            }
        }
    }

    void insertCircle(const Point *center, const Point *to_radius)
    {
        Circle *circle = new Circle(new TwoDimensionalVector(center, to_radius));

        if (_tree == nullptr)
        {
            _tree = circle;
        }
        else
        {
            ClosestShapeFinder *visitor = new ClosestShapeFinder(circle);
            _tree->accept(visitor);

            Shape *closestShape = visitor->getClosestShape();
            CompoundShape *parent = visitor->getParent();

            Shape *shapes[] = {closestShape, circle};
            CompoundShape *compoundShape = new CompoundShape(shapes, 2);

            if (parent == nullptr)
                _tree = compoundShape;
            else
            {
                parent->deleteShape(closestShape);
                parent->addShape(compoundShape);
            }
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
            ClosestShapeFinder *visitor = new ClosestShapeFinder(rectangle);
            _tree->accept(visitor);

            Shape *closestShape = visitor->getClosestShape();
            CompoundShape *parent = visitor->getParent();

            Shape *shapes[] = {closestShape, rectangle};
            CompoundShape *compoundShape = new CompoundShape(shapes, 2);

            if (parent == nullptr)
                _tree = compoundShape;
            else
            {
                parent->deleteShape(closestShape);
                parent->addShape(compoundShape);
            }
        }
    }

    Shape *getTree() const
    {
        return _tree;
    }
};
