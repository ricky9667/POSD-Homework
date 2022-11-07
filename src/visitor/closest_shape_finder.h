#pragma once

#include "shape_visitor.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include "../bounding_box.h"

class ClosestShapeFinder : public ShapeVisitor
{
private:
    Shape *_closestShape = nullptr;
    CompoundShape *_closestParent = nullptr;
    BoundingBox *_targetBoundingBox, *_closestBoundingBox;

public:
    ClosestShapeFinder(Shape *shape)
    {
        _targetBoundingBox = new BoundingBox(shape->getPoints());
    }

    void visitCircle(Circle *circle) override
    {
        BoundingBox *circleBoundingBox = new BoundingBox(circle->getPoints());
        if (_closestShape == nullptr)
        {
            _closestShape = circle;
            _closestBoundingBox = circleBoundingBox;
        }
        else if (_targetBoundingBox->distance(circleBoundingBox) < _targetBoundingBox->distance(_closestBoundingBox))
        {
            _closestShape = circle;
            _closestBoundingBox = circleBoundingBox;
        }
    }

    void visitTriangle(Triangle *triangle) override
    {
        BoundingBox *triangleBoundingBox = new BoundingBox(triangle->getPoints());
        if (_closestShape == nullptr)
        {
            _closestShape = triangle;
            _closestBoundingBox = triangleBoundingBox;
        }
        else if (_targetBoundingBox->distance(triangleBoundingBox) < _targetBoundingBox->distance(_closestBoundingBox))
        {
            _closestShape = triangle;
            _closestBoundingBox = triangleBoundingBox;
        }
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        BoundingBox *rectangleBoundingBox = new BoundingBox(rectangle->getPoints());
        if (_closestShape == nullptr)
        {
            _closestShape = rectangle;
            _closestBoundingBox = rectangleBoundingBox;
        }
        if (_targetBoundingBox->distance(rectangleBoundingBox) < _targetBoundingBox->distance(_closestBoundingBox))
        {
            _closestShape = rectangle;
            _closestBoundingBox = rectangleBoundingBox;
        }
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        Iterator *iterator = compoundShape->createIterator(new ListIteratorFactory());
        for (; !iterator->isDone(); iterator->next())
        {
            Shape *currentShape = iterator->currentItem();
            currentShape->accept(this);
            if (currentShape == _closestShape)
                _closestParent = compoundShape;
        }
    }

    Shape *getClosestShape() const
    {
        return _closestShape;
    }

    CompoundShape *getParent() const
    {
        return _closestParent;
    }
};
