#ifndef ENGINE_PARSER_H
#define ENGINE_PARSER_H
#include "../src/Include.h"
#include "TransformationMatrix.h"
#include "3DLSystem.h"
#include "Platonische lichamen/Cone.h"
#include "Platonische lichamen/Cylinder.h"
#include "Platonische lichamen/Sphere.h"
#include "Platonische lichamen/Torus.h"


void ParseLineDrawing(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor, Figures3D &figures, bool zBuffer);
LParser::LSystem2D ReadLSystem(const std::string &inputfile, std::set<char> &alphabet, double &angle, std::string &initiator,
                               unsigned int &iterations, double &starting_angle);
LParser::LSystem3D ReadLSystem3D(const std::string &inputfile, std::set<char> &alphabet, double &angle, std::string &initiator,
                                 unsigned int &iterations);
img::EasyImage ParseZBuffer(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundcolor, Figures3D &figures);
#endif //ENGINE_PARSER_H
