#ifndef ENGINE_MATRICES_H
#define ENGINE_MATRICES_H
#include "Include.h"

class Eyepoint{
public:
    static void ApplyTransformation(Figure &fig, const Matrix &m);
    static Point2D doProjection(const Vector3D &point, const double d);
    static Lines2D doProjection(const Figures3D& figures3D);
};
#endif //ENGINE_MATRICES_H
