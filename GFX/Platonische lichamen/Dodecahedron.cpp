#include "Dodecahedron.h"

void createDodecahedron(Figure &figure)
{
    std::vector<Vector3D> Points
            {
                    Vector3D::point(0,0,0),
                    Vector3D::point(0, 0, sqrt(5)/2),
            };

    for(int i = 2; i < 7; i++)
    {
        Vector3D vector;
        vector.x = cos((i - 2) * (2 * M_PI / 5));
        vector.y = sin((i - 2) * (2 * M_PI / 5));
        vector.z = 0.5;
        Points.emplace_back(vector);
    }

    for(int i = 7; i < 12; i++)
    {
        Vector3D vector;
        vector.x = cos(M_PI * 5 + (i - 7) * (2 * M_PI / 5));
        vector.y = sin(M_PI * 5 + (i - 7) * (2 * M_PI / 5));
        vector.z = -0.5;
        Points.emplace_back(vector);
    }

    Points.emplace_back(Vector3D::point(0, 0,-sqrt(5)/2));

    std::vector<Vector3D> middlePoints;
    for(int i = 0; i < 5; ++i) {
        Vector3D middlePoint;
        middlePoint.x = (Points[i].x + Points[(i + 1) % 5].x) / 2.0;
        middlePoint.y = (Points[i].y + Points[(i + 1) % 5].y) / 2.0;
        middlePoint.z = (Points[i].z + Points[(i + 1) % 5].z) / 2.0;
        middlePoints.emplace_back(middlePoint);
    }

    for(int i = 0; i < 5; ++i) {
        Vector3D middlePoint;
        middlePoint.x = (Points[i].x + Points[i + 7].x) / 2.0;
        middlePoint.y = (Points[i].y + Points[i + 7].y) / 2.0;
        middlePoint.z = (Points[i].z + Points[i + 7].z) / 2.0;
        middlePoints.emplace_back(middlePoint);
    }

    for(int i = 0; i < 5; ++i) {
        Vector3D middlePoint;
        middlePoint.x = (Points[i + 7].x + Points[(i + 1) % 5 + 7].x) / 2.0;
        middlePoint.y = (Points[i + 7].y + Points[(i + 1) % 5 + 7].y) / 2.0;
        middlePoint.z = (Points[i + 7].z + Points[(i + 1) % 5 + 7].z) / 2.0;
        middlePoints.emplace_back(middlePoint);
    }

    std::vector<std::vector<int>> Lines {
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
    
    for (const auto& line : Lines)
    {
        Face face;
        for (int index : line) {
            face.point_indexes.emplace_back(index);
        }
        figure.faces.emplace_back(face);
    }

    for (const auto& point : middlePoints)
    {
        figure.points.emplace_back(point);
    }
}
