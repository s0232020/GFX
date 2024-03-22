#include "Include.h"
#include "Matrices.h"

void Eyepoint::ApplyTransformation(Figure &fig, const Matrix &m)
{
    for(auto &point:fig.points)
    {
        point = point * m;
    }
}


Point2D Eyepoint::doProjection(const Vector3D &point, const double d)
{
    double x_prime = (d * point.x) / -point.z;
    double y_prime = (d * point.y) / -point.z;

    return Point2D(x_prime, y_prime);
}

Lines2D Eyepoint::doProjection(const Figures3D& figures3D)
{
    Lines2D lines2D;
    double d = 1.0;
    std::vector<std::vector<Point2D>> vecPoints2D;
    for (Figure figure:figures3D)
    {
        NormalizedColor color = figure.color;
        std::vector<Point2D> Points2D;
        for (Vector3D it:figure.points)
        {
            Point2D point = Eyepoint::doProjection(it, 1);
            Points2D.emplace_back(point);
        }
        vecPoints2D.emplace_back(Points2D);
        for (Face face:figure.faces)
        {
            int &p1 = face.point_indexes[0];
            int &p2 = face.point_indexes[1];
            Point2D &point1 = Points2D[p1];
            Point2D &point2 = Points2D[p2];
            Line2D line(point1, point2, color);
            lines2D.emplace_back(line);
        }

    }

    return lines2D;
}