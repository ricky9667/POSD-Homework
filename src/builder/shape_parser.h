#pragma once

#include <string>
#include <vector>
#include <utility>
#include "scanner.h"
#include "shape_builder.h"
#include "../point.h"
#include "../two_dimensional_vector.h"

class ShapeParser
{
private:
    Scanner *_scanner;
    ShapeBuilder *_builder;
    std::string _input;
    const std::string _leftParenthesis = "(", _rightParenthesis = ")", _comma = ",";

    void _scanLeftParenthesis()
    {
        std::string token = _scanner->next();
        if (token != _leftParenthesis)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a left parenthesis when scanning." << std::endl;
            throw std::string("Failed expecting a left parenthesis when scanning.");
        }
    }

    void _scanRightParenthesis()
    {
        std::string token = _scanner->next();
        if (token != _rightParenthesis)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a right parenthesis when scanning." << std::endl;
            throw std::string("Failed expecting a right parenthesis when scanning.");
        }
    }

    void _scanComma()
    {
        std::string token = _scanner->next();
        if (token != _comma)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a comma when scanning." << std::endl;
            throw std::string("Failed expecting a comma when scanning.");
        }
    }

    std::pair<Point *, Point *> _scanVectorPoints()
    {
        std::string token = _scanner->next();
        if (token != "Vector")
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a Vector when scanning." << std::endl;
            throw std::string("Failed expecting a Vector when scanning.");
        }

        _scanLeftParenthesis();

        _scanLeftParenthesis();
        double x1 = _scanner->nextDouble();
        _scanComma();
        double y1 = _scanner->nextDouble();
        _scanRightParenthesis();

        _scanComma();

        _scanLeftParenthesis();
        double x2 = _scanner->nextDouble();
        _scanComma();
        double y2 = _scanner->nextDouble();
        _scanRightParenthesis();

        _scanRightParenthesis();

        return std::make_pair(new Point(x1, y1), new Point(x2, y2));
    }

public:
    ShapeParser(std::string input) : _input{input}
    {
        _scanner = new Scanner(input);
        _builder = new ShapeBuilder();
    }

    ~ShapeParser() {}

    void parse()
    {
        while (!_scanner->isDone())
        {
            std::string token = _scanner->next();
            if (token == "CompoundShape")
            {
                _builder->buildCompoundShape();
            }
            else if (token == "Circle")
            {
                _scanLeftParenthesis();
                std::pair<Point *, Point *> vectorPoints = _scanVectorPoints();
                _scanRightParenthesis();
                _builder->buildCircle(vectorPoints.first, vectorPoints.second);
            }
            else if (token == "Triangle")
            {
                _scanLeftParenthesis();
                std::pair<Point *, Point *> v1Points = _scanVectorPoints();
                _scanComma();
                std::pair<Point *, Point *> v2Points = _scanVectorPoints();
                _scanRightParenthesis();
                _builder->buildTriangle(v1Points.first, v1Points.second, v2Points.second);
            }
            else if (token == "Rectangle")
            {
                _scanLeftParenthesis();
                std::pair<Point *, Point *> lengthPoints = _scanVectorPoints();
                _scanComma();
                std::pair<Point *, Point *> widthPoints = _scanVectorPoints();
                _scanRightParenthesis();
                _builder->buildRectangle(lengthPoints.first, lengthPoints.second, widthPoints.second);
            }
            else if (token == _leftParenthesis)
            {
                // initially left blank
            }
            else if (token == _rightParenthesis)
            {
                _builder->buildCompoundEnd();
            }
            else if (token == _comma)
            {
                // initially left blank
            }
            else
            {
                throw std::string("Unable to parse an unknown token.");
            }
        }
    }

    std::vector<Shape *> getResult()
    {
        if (!_scanner->isDone())
            throw std::string("Should parse before getting the result of the parser.");

        return _builder->getResult();
    }
};
