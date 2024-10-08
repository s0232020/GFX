#include "Cylinder.h"
#include <cmath>

void createCylinder(Figure& figure, const int n, const double h)
{
    // Define the points
    std::vector<Vector3D> Points;
    double angle = 2.0 * M_PI / n;
    for (int i = 0; i < n; ++i) {
        Points.emplace_back(Vector3D::point(cos(i * angle), sin(i * angle), 0));  // Base perimeter
        Points.emplace_back(Vector3D::point(cos(i * angle), sin(i * angle), h));  // Top perimeter
    }

    // Define the faces
    std::vector<std::vector<int>> Faces;
    for (int i = 0; i < n; ++i) {
        Faces.push_back({2*i, (2*i+2) % (2*n), (2*i+3) % (2*n), 2*i+1});  // Side
    }
    std::vector<int> baseFace, topFace;
    for (int i = 0; i < n; ++i) {
        baseFace.push_back(2*i);
        topFace.push_back(2*i+1);
    }
    Faces.push_back(baseFace);  // Base
    Faces.push_back(topFace);  // Top

    // Add the faces to the figure
    for (const auto& face : Faces) {
        Face newFace;
        for (int index : face) {
            newFace.point_indexes.emplace_back(index);
        }
        figure.faces.emplace_back(newFace);
    }

    // Add the points to the figure
    for (const auto& point : Points) {
        figure.points.emplace_back(point);
    }
}