#include "Include.h"
void ApplyTransformation(Figure &fig, const Matrix &m){
    for(auto &point:fig.points){
        point = point * m;

    }
}

void toPolar(const Vector3D &point, double &theta, double &phi, double &r){
    Matrix m;
}

Matrix eyePointTrans(const Vector3D &eyepoint){
    toPolar(eyepoint);

}