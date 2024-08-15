#include "Torus.h"

void createTorus(Figure &figure, const int n, const int m, const double R, const double r)
{
    // Create a 2D array to keep track of the points
    std::vector<std::vector<int>> pointTracker(n, std::vector<int>(m, 0));
    int pointCounter = 0;

    // Generate points on the surface of the torus
    for (int i = 0; i < n; ++i)
    {
        double theta = 2 * M_PI * i / n; // angle around the torus loop
        for (int j = 0; j < m; ++j)
        {
            double phi = 2 * M_PI * j / m; // angle around the torus cross-section
            double x = (R + r * cos(phi)) * cos(theta);
            double y = (R + r * cos(phi)) * sin(theta);
            double z = r * sin(phi);

            figure.points.push_back(Vector3D::point(x, y, z));
            pointTracker[i][j] = pointCounter++;
        }
    }

    // Connect the points to form faces
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::vector<int> facePoints = {
                    pointTracker[i][j],
                    pointTracker[(i + 1) % n][j],
                    pointTracker[(i + 1) % n][(j + 1) % m],
                    pointTracker[i][(j + 1) % m]
            };
            figure.faces.push_back(Face(facePoints));
        }
    }
}