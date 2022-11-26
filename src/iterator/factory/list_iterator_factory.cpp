#include "iterator_factory.h"
#include "list_iterator_factory.h"
#include "../null_iterator.h"
#include "../list_compound_iterator.h"

Iterator *ListIteratorFactory::createIterator()
{
    return new NullIterator();
}

Iterator *ListIteratorFactory::createIterator(std::list<Shape *>::const_iterator begin, std::list<Shape *>::const_iterator end)
{
    return new ListCompoundIterator<std::list<Shape *>::const_iterator>(begin, end);
}