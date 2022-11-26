#pragma once

#include <vector>
#include <stack>
#include "../shape.h"
#include "../circle.h"
#include "../triangle.h"
#include "../rectangle.h"
#include "../compound_shape.h"

class ShapeBuilder
{
private:
    std::vector<Shape *> _result;
    std::stack<CompoundShape *> _buildingCompoundShapes;

    void _buildBasicShape(Shape *shape)
    {
        if (_buildingCompoundShapes.empty())
            _result.push_back(shape);
        else
            _buildingCompoundShapes.top()->addShape(shape);
    }

public:
    void buildCircle(const Point *center, const Point *to_radius)
    {
        Circle *circle = new Circle(new TwoDimensionalVector(center, to_radius));
        _buildBasicShape(circle);
    }

    void buildTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
    {
        Triangle *triangle = new Triangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));
        _buildBasicShape(triangle);
    }

    void buildRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point)
    {
        Rectangle *rectangle = new Rectangle(
            new TwoDimensionalVector(common_point, v1_point),
            new TwoDimensionalVector(common_point, v2_point));
        _buildBasicShape(rectangle);
    }

    void buildCompoundShape()
    {
        _buildingCompoundShapes.push(new CompoundShape({}, 0));
    }

    void buildCompoundEnd()
    {
        CompoundShape *compoundShape = _buildingCompoundShapes.top();
        _buildingCompoundShapes.pop();

        if (_buildingCompoundShapes.empty())
            _result.push_back(compoundShape);
        else
            _buildingCompoundShapes.top()->addShape(compoundShape);
    }

    std::vector<Shape *> getResult()
    {
        return _result;
    }
};
