#pragma once

#include <vector>
#include "shape_visitor.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include "../bounding_box.h"
#include "../iterator/factory/list_iterator_factory.h"

class CollisionDetector : public ShapeVisitor
{
private:
    std::vector<Shape *> _collideResult;
    BoundingBox *_targetBoundingBox;

public:
    CollisionDetector(Shape *shape)
    {
        _targetBoundingBox = new BoundingBox(shape->getPoints());
    }

    void visitCircle(Circle *circle) override
    {
        BoundingBox *circleBoundingBox = new BoundingBox(circle->getPoints());
        if (_targetBoundingBox->collide(circleBoundingBox))
            _collideResult.push_back(circle);
    }

    void visitTriangle(Triangle *triangle) override
    {
        BoundingBox *triangleBoundingBox = new BoundingBox(triangle->getPoints());
        if (_targetBoundingBox->collide(triangleBoundingBox))
            _collideResult.push_back(triangle);
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        BoundingBox *rectangleBoundingBox = new BoundingBox(rectangle->getPoints());
        if (_targetBoundingBox->collide(rectangleBoundingBox))
            _collideResult.push_back(rectangle);
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        Iterator *iterator = compoundShape->createIterator(new ListIteratorFactory());
        for (; !iterator->isDone(); iterator->next())
        {
            Shape *currentShape = iterator->currentItem();
            BoundingBox *boundingBox = new BoundingBox(currentShape->getPoints());
            if (_targetBoundingBox->collide(boundingBox))
                _collideResult.push_back(currentShape);
        }
    }

    std::vector<Shape *> collidedShapes() const
    {
        return _collideResult;
    }
};
