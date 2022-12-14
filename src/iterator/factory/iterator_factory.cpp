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
        {
            static DFSIteratorFactory factory = DFSIteratorFactory();
            _instances[name] = &factory;
        }
        else if (name == "BFS")
        {
            static BFSIteratorFactory factory = BFSIteratorFactory();
            _instances[name] = &factory;
        }
        else if (name == "List")
        {
            static ListIteratorFactory factory = ListIteratorFactory();
            _instances[name] = &factory;
        }
    }
    return _instances[name];
}
