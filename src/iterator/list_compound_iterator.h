#pragma once

#include <vector>
#include <string>
#include "../shape.h"
#include "iterator.h"

class CompoundShape;

template <class ForwardIterator>
class ListCompoundIterator : public Iterator
{
private:
    std::vector<Shape *> _shapes;
    int _currentIndex = 0;

public:
    ListCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        for (ForwardIterator parentIterator = begin; parentIterator != end; parentIterator++)
            _shapes.push_back(*parentIterator);

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

