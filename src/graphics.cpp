#include "./point.h"
#include "./two_dimensional_vector.h"
#include "./triangle.h"
#include "./rectangle.h"
#include "./circle.h"
#include "./shape.h"
#include "./compound_shape.h"
#include "./iterator/null_iterator.h"
#include "./iterator/list_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/bfs_compound_iterator.h"
#include "./bounding_box.h"
#include "./visitor/collision_detector.h"
#include "./builder/shape_parser.h"
#include "./visitor/shape_printer.h"

#include "./utils/file_reader.h"
#include "./graphics/sdl_adapter.h"
#include "./graphics/sdl/sdl_renderer.h"

#include <iostream>

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        std::cout << "Missing the path of input.txt" << std::endl;
        throw "Missing the path of input.txt";
    }
    FileReader reader(args[1]);
    std::string input = reader.read();
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> shapes = parser.getResult();

    SDL *renderer = new SDLRenderer(30);                  // Adaptee
    Canvas *canvas = new SDLAdapter(1024, 768, renderer); // Adapter
    ShapePrinter printer(canvas);
    for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++)
    {
        Iterator *sit = (*it)->createIterator(IteratorFactory::getInstance("DFS"));
        if (sit->isDone()) // could be a Leaf shape
        {
            (*it)->accept(&printer);
        }
        else // is a CompoundShape
        {
            for (; !sit->isDone(); sit->next())
                sit->currentItem()->accept(&printer);
        }
    }
    canvas->display();

    delete renderer;
    delete canvas;
}
