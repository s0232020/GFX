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
};
#endif //ENGINE_MATRICES_H
