#include "TransformationMatrix.h"
Matrix TransformationMatrix::scaleFigure(const double &scale) {
    Matrix m;
    m(1, 1) = scale;
    m(2, 2) = scale;
    m(3, 3) = scale;
    m(4,4) = 1;
    return m;
}
Matrix TransformationMatrix::rotateX(const double &angle) {
    Matrix m;
    m(2, 2) = cos(angle);
    m(3, 2) = -sin(angle);
    m(2, 3) = sin(angle);
    m(3, 3) = cos(angle);
    return m;
}

Matrix TransformationMatrix::rotateY(const double &angle) {
    Matrix m;
    m(1, 1) = cos(angle);
    m(1, 3) = -sin(angle);
    m(3, 1) = sin(angle);
    m(3, 3) = cos(angle);
    return m;
}

Matrix TransformationMatrix::rotateZ(const double &angle){
    Matrix m;
    m(1,1) = cos(angle);
    m(1,2) = -sin(angle);
    m(2,1) = sin(angle);
    m(2,2) = cos(angle);
    return m;
}

Matrix TransformationMatrix::translate(const Vector3D &vector){
    Matrix m;
    m(4,1) = vector.x;
    m(4,2) = vector.y;
    m(4,3) = vector.z;
    m(4,4) = 1;
    return m;
}

Matrix TransformationMatrix::eyepointTransformation(const Vector3D& point) {
    Matrix m;
    double r = std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);

    // Handle cases where r is zero to avoid division by zero errors
    if (std::abs(r) < std::numeric_limits<double>::epsilon()) {
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
    return m;

}

Matrix TransformationMatrix::lineDrawing(const double &scale, const double &aX, const double &aY, const double &aZ,
                                         Vector3D &center, Vector3D &eye) {
    Matrix m;
    m = TransformationMatrix::scaleFigure(scale) * TransformationMatrix::rotateX(aX)
        * TransformationMatrix::rotateY(aY) * TransformationMatrix::rotateZ(aZ)
        * TransformationMatrix::translate(center) * TransformationMatrix::eyepointTransformation(eye);
    return m;
}
