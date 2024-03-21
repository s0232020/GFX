#ifndef ENGINE_TRANSFORMATIONMATRIX_H
#define ENGINE_TRANSFORMATIONMATRIX_H
#include "Include.h"
class TransformationMatrix {
public:
    static Matrix scaleFigure(const double &scale);

    static Matrix rotateX(const double &angle);

    static Matrix rotateY(const double &angle);

    static Matrix rotateZ(const double &angle);

    static Matrix translate(const Vector3D &vector);

    static Matrix eyepointTransformation(const Vector3D &point);

    static Matrix lineDrawing(const double &scale, const double &aX, const double &aY,
    const double &aZ, Vector3D &center, Vector3D  &eye);
};
#endif //ENGINE_TRANSFORMATIONMATRIX_H
