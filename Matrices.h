#ifndef ENGINE_MATRICES_H
#define ENGINE_MATRICES_H
#include "Include.h"

class Eyepoint{
public:
    void ApplyTransformation(Figure &fig, const Matrix &m);
    static void eyepointTransformation(const Vector3D& point);
    static Point2D doProjection(const Vector3D &point, const double d);
    static Lines2D doProjection(const Figures3D& figures3D, NormalizedColor &color);
};
#endif //ENGINE_MATRICES_H
