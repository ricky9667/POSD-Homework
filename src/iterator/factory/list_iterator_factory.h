#pragma once

#include "iterator_factory.h"

class ListIteratorFactory : public IteratorFactory
{
    Iterator *createIterator()
    {
        return new NullIterator();
    }

    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
    {
        return new ListCompoundIterator(begin, end);
    }
};
