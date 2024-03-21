#ifndef ENGINE_INTRO_H
#define ENGINE_INTRO_H
#include "Include.h"
#include "Matrices.h"

img::EasyImage colorRectangle(const ini::Configuration &configuration);
img::EasyImage introBlocks(const ini::Configuration &configuration);
img::EasyImage linesQuarterCircle(const ini::Configuration &configuration);
img::EasyImage linesDiamond(const ini::Configuration &configuration);
img::EasyImage draw2DLines(const Lines2D &lines,const int size, NormalizedColor& color);
img::EasyImage LSystem2D(const ini::Configuration &configuration);
img::EasyImage LSystem3D(const ini::Configuration &configuration);
#endif //ENGINE_INTRO_H
