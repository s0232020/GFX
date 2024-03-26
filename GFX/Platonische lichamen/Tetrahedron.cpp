#include "Tetrahedron.h"

void createTetrahedron(Figure &figure)
{
    std::vector<Vector3D> Points {
            Vector3D::point(0,0,0),
            Vector3D::point(1, -1, -1),
            Vector3D::point(-1, 1, -1),
            Vector3D::point(1, 1, 1),
            Vector3D::point(-1, -1, 1),
    };

    std::vector<std::vector<int>> Lines {
            {1, 2, 3},
            {2, 4, 3},
            {1, 4, 2},
            {1, 3, 4},
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