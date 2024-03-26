#include "Cube.h"

void createCube(Figure &figure) {
    std::vector<Vector3D> Points {
        Vector3D::point(0,0,0),
        Vector3D::point(1, -1, -1),
        Vector3D::point(-1, 1, -1),
        Vector3D::point(1, 1, 1),
        Vector3D::point(-1, -1, 1),
        Vector3D::point(1, 1, -1),
        Vector3D::point(-1, -1, -1),
        Vector3D::point(1, -1, 1),
        Vector3D::point(-1, 1, 1)
    };

    std::vector<std::vector<int>> Lines {
            {1, 5, 3, 7},
            {5, 2, 8, 3},
            {2, 6, 4, 8},
            {6, 1, 7, 4},
            {7, 3, 8, 4},
            {1, 6, 2, 5}
    };

    for (const auto& line : Lines) {
        Face face;
        for (int index : line) {
            face.point_indexes.emplace_back(index);
        }
        figure.faces.emplace_back(face);
    }

    for (const auto& point : Points) {
        figure.points.emplace_back(point);
    }
}
