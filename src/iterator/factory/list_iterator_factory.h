#pragma once

#include "iterator_factory.h"

class ListIteratorFactory : public IteratorFactory
{
    Iterator *createIterator();
    Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end);
};
