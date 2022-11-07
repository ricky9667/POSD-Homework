#pragma once

#include "shape_visitor.h"
#include "../iterator/factory/list_iterator_factory.h"

class IllegalNodeChecker : public ShapeVisitor
{
private:
    bool _isIllegal = false;
    bool _isCheckingChild = false;

public:
    void visitCircle(Circle *circle) override
    {
        _isIllegal = false;
    }

    void visitTriangle(Triangle *triangle) override
    {
        _isIllegal = false;
    }

    void visitRectangle(Rectangle *rectangle) override
    {
        _isIllegal = false;
    }

    void visitCompoundShape(CompoundShape *compoundShape) override
    {
        if (_isCheckingChild)
        {
            _isIllegal = true;
            return;
        }

        Iterator *iterator = compoundShape->createIterator(new ListIteratorFactory());

        // compound shape has no children
        if (iterator->isDone())
        {
            _isIllegal = true;
        }
        else
        {
            iterator->next();

            // check if only child is also a compound shape
            if (iterator->isDone())
            {
                _isCheckingChild = true;
                iterator->currentItem()->accept(this);
                _isCheckingChild = false;
            }
            else
            {
                _isIllegal = false;
            }
        }
    }

    bool isIllegal() const
    {
        return _isIllegal;
    }
};
