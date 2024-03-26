#include "Octahedron.h"

void createOctahedron(Figure &figure)
{
    {
        std::vector<Vector3D> Points
        {
                Vector3D::point(0,0,0),
                Vector3D::point(1, 0, 0),
                Vector3D::point(0, 1, 0),
                Vector3D::point(-1, 0, 0),
                Vector3D::point(0, -1, 0),
                Vector3D::point(0, 0, -1),
                Vector3D::point(0, 0, 1),
        };

        std::vector<std::vector<int>> Lines
        {
                {1, 2, 6},
                {2, 3, 6},
                {3, 4, 6},
                {4, 1, 6},
                {2, 1, 5},
                {3, 2, 5},
                {4, 3, 5},
                {1, 4, 5},
        };

        for (const auto& line : Lines)
        {
            Face face;
            for (int index : line) {
                face.point_indexes.emplace_back(index);
            }
            figure.faces.emplace_back(face);
        }

        for (const auto& point : Points)
        {
            figure.points.emplace_back(point);
        }
    }
}
