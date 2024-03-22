#ifndef ENGINE_TRANSFORMATIONMATRIX_H
#define ENGINE_TRANSFORMATIONMATRIX_H
#include "../src/Include.h"
    Matrix scaleFigure(const double &scale);

    Matrix rotateX(const double &angle);

    Matrix rotateY(const double &angle);

    Matrix rotateZ(const double &angle);

    Matrix translate(const Vector3D &vector);

    Matrix eyepointTransformation(const Vector3D &point);

    Matrix lineDrawing(const double &scale, const double &aX, const double &aY,
    const double &aZ, Vector3D &center, Vector3D  &eye);

    void ApplyTransformation(Figure &fig, const Matrix &m);

    Point2D doProjection(const Vector3D &point, const double d);

    Lines2D doProjection(const Figures3D& figures3D);

#endif //ENGINE_TRANSFORMATIONMATRIX_H
