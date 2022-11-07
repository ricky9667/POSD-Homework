#pragma once

#include "iterator_factory.h"

class IllegalNodeIteratorFactory : public IteratorFactory
{
private:
    Shape *_root;

public:
    IllegalNodeIteratorFactory(Shape *root) : _root{root} {}

    Iterator *createIterator()
    {
        return new IllegalNodeIterator(_root);
    }

    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
    {
        // return new ListCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
    }
};
