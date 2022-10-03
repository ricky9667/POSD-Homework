#pragma once

#include "iterator.h"
#include "../shape.h"

class NullIterator : public Iterator
{
public:
    void first() override {}

    Shape* currentItem() const override {}

    void next() override {}

    bool isDone() const override {}
};

