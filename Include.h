#ifndef ENGINE_INCLUDE_H
#define ENGINE_INCLUDE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include "easy_image.h"
#include "ini_configuration.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "l_parser.h"
#include <string>
#include <set>
#include <stack>
#include "vector3d.h"
#include <list>
#include <limits>

struct NormalizedColor{
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    NormalizedColor(){

    }

    NormalizedColor(const std::vector<double>& doubleVec){
        if(doubleVec.size() == 3){
            r = doubleVec[0];
            g = doubleVec[1];
            b = doubleVec[2];
        }
        else{
            throw std::runtime_error("Vector verkeerde size");
        }
    }
    img::Color toEasyImageColor() const {
        img::Color returnValue;
        returnValue.red = r * 255.0;
        returnValue.green = g * 255.0;
        returnValue.blue = b * 255.0;
        return returnValue;
    }

};


struct Point2D{
    double x = 0.0;
    double y = 0.0;

    Point2D(){

    }

    Point2D(double x, double y){
        this->x = x;
        this->y = y;
    }
};

struct Point3D{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    Point3D(){}
    Point3D(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Line2D{
    Point2D p1;
    Point2D p2;
    NormalizedColor color;

    Line2D(){}

    Line2D(Point2D p1, Point2D p2){
        this->p1 = p1;
        this->p2 = p2;
    }

    Line2D(Point2D p1, Point2D p2, NormalizedColor& color){
        this->p1 = p1;
        this->p2 = p2;
        this->color = color;
    }
};
struct Line3D{
    Point3D p1;
    Point3D p2;
    Line3D(){}
    Line3D(Point3D p1, Point3D p2){
        this->p1 = p1;
        this->p2 = p2;
    }
};
struct Face{
    std::vector<int> point_indexes;
};
struct Figure{
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    NormalizedColor color;
};
typedef std::list<Figure> Figures3D;

using Lines2D = std::vector<Line2D>;
using Lines3D = std::vector<Line3D>;
#endif //ENGINE_INCLUDE_H
