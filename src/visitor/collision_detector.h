#pragma once

#include <vector>
#include "shape_visitor.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include "../bounding_box.h"
#include "../iterator/factory/iterator_factory.h"

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

    ~CollisionDetector()
    {
        delete _targetBoundingBox;
    }

    void visitCircle(Circle *circle) override
    {
        BoundingBox *circleBoundingBox = new BoundingBox(circle->getPoints());
        if (_targetBoundingBox->collide(circleBoundingBox))
            _collideResult.push_back(circle);

        delete circleBoundingBox;
    }

    void visitTriangle(Triangle *triangle) override
    {
        BoundingBox *triangleBoundingBox = new BoundingBox(triangle->getPoints());
        if (_targetBoundingBox->collide(triangleBoundingBox))
            _collideResult.push_back(triangle);

        delete triangleBoundingBox;
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        BoundingBox *rectangleBoundingBox = new BoundingBox(rectangle->getPoints());
        if (_targetBoundingBox->collide(rectangleBoundingBox))
            _collideResult.push_back(rectangle);

        delete rectangleBoundingBox;
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        Iterator *iterator = compoundShape->createIterator(IteratorFactory::getInstance("List"));
        for (; !iterator->isDone(); iterator->next())
        {
            Shape *currentShape = iterator->currentItem();
            currentShape->accept(this);
        }

        delete iterator;
    }

    std::vector<Shape *> collidedShapes() const
    {
        return _collideResult;
    }
};
