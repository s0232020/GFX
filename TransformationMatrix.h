#ifndef ENGINE_TRANSFORMATIONMATRIX_H
#define ENGINE_TRANSFORMATIONMATRIX_H
#include "Include.h"
class TransformationMatrix{
public:
    static Matrix scaleFigure(const double &scale);
    static Matrix rotateX(const double &angle);
    static Matrix rotateY(const double &angle);
    static Matrix rotateZ(const double &angle);
    static Matrix translate(const Vector3D &vector);
};
#endif //ENGINE_TRANSFORMATIONMATRIX_H
