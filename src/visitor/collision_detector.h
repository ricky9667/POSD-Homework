#pragma once

#include <vector>
#include "shape_visitor.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"
#include "../bounding_box.h"
#include "../iterator/factory/bfs_iterator_factory.h"

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

    void visitCircle(Circle *circle) override {}

    void visitTriangle(Triangle *triangle) override {}

    void visitRectangle(Rectangle *rectangle) override {}

    void visitCompoundShape(CompoundShape *compoundShape) override {}

    std::vector<Shape *> collidedShapes() const
    {
        return _collideResult;
    }
};
