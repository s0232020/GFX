#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H
#include "Parser.h"
#include "TransformationMatrix.h"

Lines2D DrawLSystem(LParser::LSystem2D &l_system, const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor);

img::EasyImage draw2DLines(const Lines2D &lines,const int &size, NormalizedColor &color, bool zBuffer);

img::EasyImage LSystem2D(const ini::Configuration &configuration);

img::EasyImage LSystem3D(const ini::Configuration &configuration, bool zBuffer);

img::EasyImage zBuffer(const ini::Configuration &configuration);

#endif //ENGINE_MAIN_H