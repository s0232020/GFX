#include "TransformationMatrix.h"
Matrix scaleFigure(const double &scale)
{
    Matrix m;
    m(1, 1) = scale;
    m(2, 2) = scale;
    m(3, 3) = scale;
    m(4,4) = 1;
    return m;
}
Matrix rotateX(const double &angle)
{
    Matrix m;
    m(1,1) = 1;
    m(4,4) = 1;
    m(2, 2) = cos(angle);
    m(3, 2) = -sin(angle);
    m(2, 3) = sin(angle);
    m(3, 3) = cos(angle);
    return m;
}

Matrix rotateY(const double &angle)
{
    Matrix m;
    m(2,2) = 1;
    m(4,4) = 1;
    m(1, 1) = cos(angle);
    m(1, 3) = -sin(angle);
    m(3, 1) = sin(angle);
    m(3, 3) = cos(angle);
    return m;
}

Matrix rotateZ(const double &angle)
{
    Matrix m;
    m(3,3) = 1;
    m(4,4) = 1;
    m(1,1) = cos(angle);
    m(1,2) = -sin(angle);
    m(2,1) = sin(angle);
    m(2,2) = cos(angle);
    return m;
}

Matrix translate(const Vector3D &vector)
{
    Matrix m;
    m(1,1) = 1;
    m(2,2) = 1;
    m(3,3) = 1;
    m(4,4) = 1;
    m(4,1) = vector.x;
    m(4,2) = vector.y;
    m(4,3) = vector.z;
    return m;
}

Matrix eyepointTransformation(const Vector3D& point)
{
    Matrix m;
    double r = std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);

    if (std::abs(r) < std::numeric_limits<double>::epsilon())
    {
        double theta = 0.0;
        double phi = M_PI_2;
    }

    double theta = std::atan2(point.y, point.x);
    double phi = std::acos(point.z / r);

    m(1,1) = -sin(theta);
    m(1,2) = -cos(theta)*cos(phi);
    m(1,3) = cos(theta)*sin(phi);
    m(2,1) = cos(theta);
    m(2,2) = -sin(theta)*cos(phi);
    m(2,3) = sin(theta)*sin(phi);
    m(3,2) = sin(phi);
    m(3,3) = cos(phi);
    m(4,3) = -r;
    m(4,4) = 1;
    return m;

}

Matrix lineDrawing(const double &scale, const double &aX, const double &aY,
                                         const double &aZ, Vector3D &center, Vector3D &eye){
    Matrix m;
    m = scaleFigure(scale) * rotateX(aX)
        * rotateY(aY) * rotateZ(aZ)
        * translate(center) * eyepointTransformation(eye);
    return m;
}

void ApplyTransformation(Figure &fig, const Matrix &m)
{
    for(auto &point:fig.points)
    {
        point = point * m;
    }
}


Point2D doProjection(const Vector3D &point, const double d)
{
    double x_prime = (d * point.x) / -point.z;
    double y_prime = (d * point.y) / -point.z;

    return Point2D(x_prime, y_prime);
}

Lines2D doProjection(const Figures3D& figures3D)
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
            Point2D point = doProjection(it, 1);
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