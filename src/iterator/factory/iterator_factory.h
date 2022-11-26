#pragma once

#include <list>
#include <string>
#include <map>
#include "../iterator.h"

typedef std::map<std::string, IteratorFactory *> IteratorFactoryMap;

class IteratorFactory
{
public:
    virtual Iterator *createIterator() = 0;
    virtual Iterator *createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end) = 0;
    static IteratorFactory *getInstance(std::string name);

private:
    static IteratorFactoryMap _instances;
};
