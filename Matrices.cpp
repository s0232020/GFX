#include "Include.h"
#include "Matrices.h"

void Eyepoint::ApplyTransformation(Figure &fig, const Matrix &m){
    for(auto &point:fig.points){
        point = point * m;
    }
}


Point2D Eyepoint::doProjection(const Vector3D &point, const double d) {
    double x_prime = (d * point.x) / -point.z;
    double y_prime = (d * point.y) / -point.z;

    return Point2D(x_prime, y_prime);
}

std::vector<Point2D> projectPoints(const std::vector<Vector3D>& points3D, double d) {
    std::vector<Point2D> points2D;
    for (const auto& point : points3D) {
        double x_prime = (d * point.x) / -point.z;
        double y_prime = (d * point.y) / -point.z;
        points2D.emplace_back(x_prime, y_prime);
    }
    return points2D;
}
Lines2D Eyepoint::doProjection(const Figures3D& figures3D, NormalizedColor& color) {
    Lines2D lines2D;
    double d = 1.0; // Set an appropriate value for the distance 'd'

    std::vector<Point2D> points2D;
    for (const auto& figure : figures3D) {
        points2D.insert(points2D.end(), projectPoints(figure.points, d).begin(), projectPoints(figure.points, d).end());

        for (const auto& face : figure.faces) {
            for (size_t i = 1; i < face.point_indexes.size(); i++) {
                Vector3D v1 = figure.points[face.point_indexes[i - 1]];
                Vector3D v2 = figure.points[face.point_indexes[i]];

                Point2D point1 = doProjection(v1, 1);
                Point2D point2 = doProjection(v2, 1);

                Line2D line(point1, point2);
                lines2D.emplace_back(line);
            }
        }
    }

    return lines2D;
}