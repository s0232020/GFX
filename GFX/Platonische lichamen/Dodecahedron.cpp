#include "Dodecahedron.h"

void createDodecahedron(Figure &figure) {
    Figure icosahedron;
    createIcosahedron(icosahedron);

    for (const Face face: icosahedron.faces) {
        Vector3D Jelle = Vector3D::point(0, 0, 0);
        for (int index: face.point_indexes) {
            Jelle += icosahedron.points[index];
        }
        Jelle /= face.point_indexes.size();
        figure.points.emplace_back(Jelle);
    }

    std::vector<std::vector<int>> faceIndices = {
            {1,  2,  3,  4,  5},
            {1,  6,  7,  8,  2},
            {2,  8,  9,  10, 3},
            {3,  10, 11, 12, 4},
            {4,  12, 13, 14, 5},
            {5,  14, 15, 6,  1},
            {20, 19, 18, 17, 16},
            {20, 15, 14, 13, 19},
            {19, 13, 12, 11, 18},
            {18, 11, 10, 9,  17},
            {17, 9,  8,  7,  16},
            {16, 7,  6,  15, 20},
    };

    for (const auto& indices : faceIndices) {
        Face face;
        for (int index : indices) {
            face.point_indexes.push_back(index - 1); // Subtract 1 here
        }
        figure.faces.push_back(face);
    }
}