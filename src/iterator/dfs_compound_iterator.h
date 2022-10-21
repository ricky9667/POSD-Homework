#pragma once

#include <vector>

#include "iterator.h"
#include "../shape.h"
#include "factory/dfs_iterator_factory.h"

class CompoundShape;

template <class ForwardIterator>
class DFSCompoundIterator : public Iterator
{
private:
    std::vector<Shape *> _shapes;
    int _currentIndex = 0;

public:
    DFSCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        for (ForwardIterator parentIterator = begin; parentIterator != end; parentIterator++)
        {
            _shapes.push_back(*parentIterator);
            Iterator *childIterator = (*parentIterator)->createIterator(new DFSIteratorFactory());
            for (; !childIterator->isDone(); childIterator->next())
            {
                _shapes.push_back(childIterator->currentItem());
            }
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
