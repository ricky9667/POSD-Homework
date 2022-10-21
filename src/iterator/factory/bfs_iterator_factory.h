#pragma once

#include "./iterator_factory.h"
#include "../null_iterator.h"
#include "../bfs_compound_iterator.h"

class BFSIteratorFactory : public IteratorFactory
{
    Iterator *createIterator()
    {
        return new NullIterator();
    }

    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
    {
        return new BFSCompoundIterator(begin, end);
    }
};
