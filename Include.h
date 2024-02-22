//
// Created by Family on 14/02/2024.
//

#ifndef ENGINE_INCLUDE_H
#define ENGINE_INCLUDE_H

#include "easy_image.h"
#include "ini_configuration.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

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
};

struct Color{
    unsigned int r = 0;
    unsigned int g = 0;
    unsigned int b = 0;

    Color(){

    }


    Color(const std::vector<double>& doubleVec){
        if(doubleVec.size() == 3){
            r = doubleVec[0] * 255;
            g = doubleVec[1] * 255;
            b = doubleVec[2] * 255;
        }
        else{
            throw std::runtime_error("Vector verkeerde size");
        }
    }

    img::Color toEasyImageColor(){
        img::Color returnValue(r, g, b);
        return returnValue;
    }

    NormalizedColor toNormalizedColor(){
        NormalizedColor returnValue;
        returnValue.r = r / 255.0;
        returnValue.g = g / 255.0;
        returnValue.b = b / 255.0;
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

struct Line2D{
    Point2D p1;
    Point2D p2;
    Color color;

    Line2D(Point2D p1, Point2D p2, Color color){
        this->p1 = p1;
        this->p2 = p2;
        this->color = color;
    }
};

using Lines2D = std::vector<Line2D>;
#endif //ENGINE_INCLUDE_H
