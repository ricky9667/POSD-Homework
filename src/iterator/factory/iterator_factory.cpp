#include "iterator_factory.h"
#include "dfs_iterator_factory.h"
#include "bfs_iterator_factory.h"
#include "list_iterator_factory.h"

IteratorFactoryMap IteratorFactory::_instances = {};

IteratorFactory *IteratorFactory::getInstance(std::string name)
{
    if (_instances.find(name) == _instances.end())
    {
        if (name == "DFS")
            _instances[name] = new DFSIteratorFactory();
        else if (name == "BFS")
            _instances[name] = new BFSIteratorFactory();
        else if (name == "List")
            _instances[name] = new ListIteratorFactory();
    }
    return _instances[name];
}
