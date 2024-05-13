#ifndef ENGINE_3DLSYSTEM_H
#define ENGINE_3DLSYSTEM_H

#include "Utils.h"
#include <stack>
#include <string>
#include <map>
#include "../src/vector3d.h"
#include <vector>
#include "../src/l_parser.h"
#include "../src/ini_configuration.h"
#include "Parser.h"

void create3DLSystem(Figure &figure, const ini::Configuration &configuration, int figIndex);

#endif //ENGINE_3DLSYSTEM_H
