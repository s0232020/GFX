cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        src/easy_image.cc
        src/engine.cc
        src/ini_configuration.cc
        GFX/main.cpp
        GFX/main.h
        src/Include.h
        src/l_parser.cc
        src/vector3d.cc
        GFX/TransformationMatrix.cpp
        GFX/Parser.cpp
        GFX/Parser.h
        GFX/Utils.h
        "GFX/Platonische lichamen/Cube.cpp"
        "GFX/Platonische lichamen/Cube.h"
        GFX/LineDrawing.cpp
        GFX/LineDrawing.h
        "GFX/Platonische lichamen/Tetrahedron.cpp"
        "GFX/Platonische lichamen/Tetrahedron.h"
        "GFX/Platonische lichamen/Icosahedron.cpp"
        "GFX/Platonische lichamen/Icosahedron.h"
        "GFX/Platonische lichamen/Octahedron.cpp"
        "GFX/Platonische lichamen/Octahedron.h"
        "GFX/Platonische lichamen/Dodecahedron.cpp"
        "GFX/Platonische lichamen/Dodecahedron.h"
        GFX/3DLSystem.cpp
        GFX/3DLSystem.h
        "GFX/Platonische lichamen/Cone.cpp"
        "GFX/Platonische lichamen/Cone.h"
        "GFX/Platonische lichamen/Cylinder.cpp"
        "GFX/Platonische lichamen/Cylinder.h")

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION .)
