#include "Cone.h"

void createCone(Figure& figure, const int n, const double h)
{
    // Define the points
    std::vector<Vector3D> Points;
    double angle = 2.0 * M_PI / n;
    for (int i = 0; i < n; ++i) {
        Points.emplace_back(Vector3D::point(cos(i * angle), sin(i * angle), 0));  // Base perimeter
    }
    Points.emplace_back(Vector3D::point(0, 0, h));  // Tip of the cone

    // Define the faces
    std::vector<std::vector<int>> Faces;
    for (int i = 0; i < n; ++i) {
        Faces.push_back({i, (i+1) % n, n});  // Side
    }
    std::vector<int> baseFace;
    for (int i = 0; i < n; ++i) {
        baseFace.push_back(i);
    }
    Faces.push_back(baseFace);  // Base

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