#include "Icosahedron.h"

void createIcosahedron(Figure &figure)
{
    std::vector<Vector3D> Points
    {
            Vector3D::point(0,0,0),
            Vector3D::point(0, 0, sqrt(5)/2),
    };

    for(int i = 2; i < 7; i++)
    {
        Vector3D vector;
        vector.x = cos((i-2)*(2*M_PI/5));
        vector.y = sin((i-2)*(2*M_PI/5));
        vector.z = 0.5;
        Points.emplace_back(vector);
    }

    for(int i = 7; i < 12; i++)
    {
        Vector3D vector;
        vector.x = cos(M_PI*5 + (i-7) * 2 * (M_PI / 5));
        vector.y = sin(M_PI*5 + (i-7) * 2 * (M_PI / 5));
        vector.z = -0.5;
        Points.emplace_back(vector);
    }

    Points.emplace_back(Vector3D::point(0, 0,-sqrt(5)/2));

    std::vector<std::vector<int>> Lines
    {
            {1, 2, 3},
            {1, 3, 4},
            {1, 4, 5},
            {1, 5, 6},
            {1, 6, 2},
            {2, 7, 3},
            {3, 7, 8},
            {3, 8, 4},
            {4, 8, 9},
            {4, 9, 5},
            {5, 9, 10},
            {5, 10, 6},
            {6, 10, 11},
            {6, 11, 2},
            {2, 11, 7},
            {12, 8, 7},
            {12, 9, 8},
            {12, 10, 9},
            {12, 11, 10},
            {12, 7, 11},
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
