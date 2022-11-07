#pragma once

#include <vector>
#include "iterator.h"
#include "factory/dfs_iterator_factory.h"
#include "../visitor/illegal_node_checker.h"

class IllegalNodeIterator : public Iterator
{
private:
    std::vector<Shape *> _shapes;
    int _currentIndex = 0;

public:
    IllegalNodeIterator(Shape *root)
    {
        // find all illegal nodes
        IllegalNodeChecker *visitor = new IllegalNodeChecker();
        root->accept(visitor);
        if (visitor->isIllegal())
        {
            _shapes.push_back(root);
        }

        Iterator *it = root->createIterator(new DFSIteratorFactory());
        for (; !it->isDone(); it++)
        {
            Shape *shape = it->currentItem();
            shape->accept(visitor);
            if (visitor->isIllegal())
                _shapes.push_back(shape);
        }

        first();
    }

    void first() override
    {
        _currentIndex = 0;
    }

    Shape *currentItem() override
    {
        if (isDone())
            throw std::string("The iterator has finished iterating, call first() before using currentItem().");

        return _shapes[_currentIndex];
    }

    void next() override
    {
        if (isDone())
            throw std::string("The iterator has finished iterating, call first() before using currentItem().");

        _currentIndex++;
    }

    bool isDone() const override
    {
        return _currentIndex >= _shapes.size();
    }
};
