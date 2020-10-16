#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"
#include "Color.h"
#include <sstream> 

const std::string RECTANGLE_NAME = "rectangle";
const std::string TRIANGLE_NAME = "triangle";
const std::string ELLIPSE_NAME = "ellipse";
const std::string REGULAR_POLYGON_NAME = "regularPolygon";

Color GetColor(const std::string& color)
{
    auto iter = COLORS_NAMES.find(color);

    if (iter != COLORS_NAMES.end())
    {
        return iter->second;
    }


    throw std::invalid_argument("Unknown color");
}

std::unique_ptr<CRectangle> CreateRectangle(std::istringstream& strm)
{
    SPoint leftTopCorner;
    double width, height;
    std::string color;

    if (!(strm >> leftTopCorner.x >> leftTopCorner.y >> width >> height >> color))
    {
        throw std::invalid_argument("Invalid arguments to create rectangle");
    }

    CRectangle rectangle(leftTopCorner, width, height, GetColor(color));

    return std::make_unique<CRectangle>(rectangle);
}

std::unique_ptr<CTriangle> CreateTriangle(std::istringstream& strm)
{
    SPoint vertex1, vertex2, vertex3;
    std::string color;

    if (!(strm >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> color))
    {
        throw std::invalid_argument("Invalid arguments to create triangle");
    }

    CTriangle triangle(vertex1, vertex2, vertex3, GetColor(color));

    return std::make_unique<CTriangle>(triangle);
}

std::unique_ptr<CEllipse> CreateEllipse(std::istringstream& strm)
{
    SPoint center;
    double horizontalRadius, verticalRadius;
    std::string color;

    if(!(strm >> center.x >> center.y >> horizontalRadius >> verticalRadius >> color))
    {
        throw std::invalid_argument("Invalid arguments to create ellipse");
    }

    CEllipse ellipse(center, horizontalRadius, verticalRadius, GetColor(color));

    return std::make_unique<CEllipse>(ellipse);
}

std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::istringstream& strm)
{
    SPoint center;
    size_t vertexCount;
    double radius;
    std::string color;

    if (!(strm >> center.x >> center.y >> vertexCount >> radius >> color))
    {
        throw std::invalid_argument("Invalid arguments to create regular polygon");
    }

    if (vertexCount < 3)
    {
        throw std::invalid_argument("Error. A regular polygon must have at least 3 vertices");
    }

    CRegularPolygon regularPolygon(center, vertexCount, radius, GetColor(color));

    return std::make_unique<CRegularPolygon>(regularPolygon);
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
    std::istringstream strm(description);
    std::string shapeName;

    strm >> shapeName;

    if (shapeName == RECTANGLE_NAME)
    {
        return CreateRectangle(strm);
    }
    else if (shapeName == TRIANGLE_NAME)
    {
        return CreateTriangle(strm);
    }
    else if (shapeName == ELLIPSE_NAME)
    {
        return CreateEllipse(strm);
    }
    else if (shapeName == REGULAR_POLYGON_NAME)
    {
        return CreateRegularPolygon(strm);
    }

    throw std::invalid_argument("Unknown shape");
}
