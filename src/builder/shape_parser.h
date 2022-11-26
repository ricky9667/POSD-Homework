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

    void _parseLeftParenthesis()
    {
        std::string token = _scanner->next();
        if (token != _leftParenthesis)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a left parenthesis when scanning." << std::endl;
            throw std::string("Failed expecting a left parenthesis when scanning.");
        }
    }

    void _parseRightParenthesis()
    {
        std::string token = _scanner->next();
        if (token != _rightParenthesis)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a right parenthesis when scanning." << std::endl;
            throw std::string("Failed expecting a right parenthesis when scanning.");
        }
    }

    void _parseComma()
    {
        std::string token = _scanner->next();
        if (token != _comma)
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a comma when scanning." << std::endl;
            throw std::string("Failed expecting a comma when scanning.");
        }
    }

    std::pair<Point *, Point *> _parseVectorWithPoints()
    {
        std::string token = _scanner->next();
        if (token != "Vector")
        {
            std::cout << "Current token: " << token << std::endl;
            std::cout << "Failed expecting a Vector when scanning." << std::endl;
            throw std::string("Failed expecting a Vector when scanning.");
        }

        _parseLeftParenthesis();

        _parseLeftParenthesis();
        double x1 = _scanner->nextDouble();
        _parseComma();
        double y1 = _scanner->nextDouble();
        _parseRightParenthesis();

        _parseComma();

        _parseLeftParenthesis();
        double x2 = _scanner->nextDouble();
        _parseComma();
        double y2 = _scanner->nextDouble();
        _parseRightParenthesis();

        _parseRightParenthesis();

        return std::make_pair(new Point(x1, y1), new Point(x2, y2));
    }

    void _parseCircle()
    {
        _parseLeftParenthesis();
        std::pair<Point *, Point *> vectorPoints = _parseVectorWithPoints();
        _parseRightParenthesis();
        _builder->buildCircle(vectorPoints.first, vectorPoints.second);
    }

    void _parseTriangle()
    {
        _parseLeftParenthesis();
        std::pair<Point *, Point *> v1Points = _parseVectorWithPoints();
        _parseComma();
        std::pair<Point *, Point *> v2Points = _parseVectorWithPoints();
        _parseRightParenthesis();


        _builder->buildTriangle(v1Points.first, v1Points.second, v2Points.second);
    }

    void _parseRectangle()
    {
        _parseLeftParenthesis();
        std::pair<Point *, Point *> lengthPoints = _parseVectorWithPoints();
        _parseComma();
        std::pair<Point *, Point *> widthPoints = _parseVectorWithPoints();
        _parseRightParenthesis();
        _builder->buildRectangle(lengthPoints.first, lengthPoints.second, widthPoints.second);
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
            std::cout << "Current token: " << token << std::endl;

            if (token == "CompoundShape")
                _builder->buildCompoundShape();
            else if (token == "Circle")
                _parseCircle();
            else if (token == "Triangle")
                _parseTriangle();
            else if (token == "Rectangle")
                _parseRectangle();
            else if (token == _leftParenthesis)
            {
            }
            else if (token == _rightParenthesis)
                _builder->buildCompoundEnd();
            else if (token == _comma)
            {
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
