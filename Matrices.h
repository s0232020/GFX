#ifndef ENGINE_MATRICES_H
#define ENGINE_MATRICES_H
#include "Include.h"
struct TransformationMatrix {
    Matrix scaleFigure(const double scale) {
        Matrix m;
        m(1, 1) = scale;
        m(2, 2) = scale;
        m(3, 3) = scale;
        return m;
    }

    Matrix rotateX(const double angle) {
        Matrix m;
        m(2, 2) = cos(angle);
        m(3, 2) = -sin(angle);
        m(2, 3) = sin(angle);
        m(3, 3) = cos(angle);
        return m;
    }

    Matrix rotateY(const double angle) {
        Matrix m;
        m(1, 1) = cos(angle);
        m(1, 3) = -sin(angle);
        m(3, 1) = sin(angle);
        m(3, 3) = cos(angle);
        return m;
    }

    Matrix rotateZ(const double angle){
        Matrix m;
        m(1,1) = cos(angle);
        m(1,2) = -sin(angle);
        m(2,1) = sin(angle);
        m(2,2) = cos(angle);
        return m;
    }

    Matrix translate(const Vector3D &vector){
        Matrix m;
        m(4,1) = vector.x;
        m(4,2) = vector.y;
        m(4,3) = vector.z;
        m(4,4) = 1;
        return m;
    }

    void ApplyTransformation(Figure &fig, const Matrix &m){
        for(auto &point:fig.points){
            point = point * m;
        }
    }

    void toPolar(const Vector3D& point, double& theta, double& phi) {
        double r = std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);

        // Handle cases where r is zero to avoid division by zero errors
        if (std::abs(r) < std::numeric_limits<double>::epsilon()) {
            theta = 0.0;
            phi = M_PI_2;
            return;
        }

        theta = std::atan2(point.y, point.x);
        phi = std::acos(point.z / r);
    }

    Matrix eyePointTrans(const Vector3D &eyepoint, double rotateX, double rotateY, double rotateZ, double scale){
        TransformationMatrix transform;
        Matrix m;

        Vector3D::normalise(eyepoint);

        m = transform.scaleFigure(scale);
        m = transform.rotateX(rotateX);
        m = transform.rotateY(rotateZ);
        m = transform.rotateZ(rotateZ);
        m = transform.translate(eyepoint);

        return m;
    }
};
#endif //ENGINE_MATRICES_H
