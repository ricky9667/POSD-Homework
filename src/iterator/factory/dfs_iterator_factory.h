#pragma once

#include "./iterator_factory.h"
#include "../null_iterator.h"
#include "../dfs_compound_iterator.h"

class DFSIteratorFactory : public IteratorFactory
{
    Iterator *createIterator()
    {
        return new NullIterator();
    }

    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
    {
        return new DFSCompoundIterator(begin, end);
    }
};
