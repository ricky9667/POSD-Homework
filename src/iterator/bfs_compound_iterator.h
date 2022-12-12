#pragma once

#include <vector>
#include "../shape.h"
#include "iterator.h"
#include "factory/iterator_factory.h"

class CompoundShape;

template <class ForwardIterator>
class BFSCompoundIterator : public Iterator
{
private:
    std::vector<Shape *> _shapes;
    int _currentIndex = 0;

public:
    BFSCompoundIterator(ForwardIterator begin, ForwardIterator end)
    {
        std::vector<Iterator *> childIterators;

        for (ForwardIterator parentIterator = begin; parentIterator != end; parentIterator++)
        {
            _shapes.push_back(*parentIterator);
            Iterator *childIterator = (*parentIterator)->createIterator(IteratorFactory::getInstance("BFS"));
            childIterators.push_back(childIterator);
        }

        for (auto childIterator = childIterators.begin(); childIterator != childIterators.end(); childIterator++)
        {
            auto it = *childIterator;
            for (; !it->isDone(); it->next())
            {
                _shapes.push_back(it->currentItem());
            }
            delete it;
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
