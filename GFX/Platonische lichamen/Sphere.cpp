#include "Sphere.h"


void createSphere(Figure& figure, const int n)
{
    createIcosahedron(figure);

    for (unsigned int i = 0; i < n; i++) {
        Figure newFig;
        int pointCounter = 0;

        for (auto face : figure.faces) {
            Vector3D a = figure.points[face.point_indexes[0]];
            Vector3D b = figure.points[face.point_indexes[1]];
            Vector3D c = figure.points[face.point_indexes[2]];

            Vector3D d = (a+b)/2;
            Vector3D e = (a+c)/2;
            Vector3D f = (b+c)/2;

            newFig.points.push_back(a);
            newFig.points.push_back(b);
            newFig.points.push_back(c);
            newFig.points.push_back(d);
            newFig.points.push_back(e);
            newFig.points.push_back(f);

            Face face1({pointCounter, pointCounter+3, pointCounter+4});
            Face face2({pointCounter+1, pointCounter+5, pointCounter+3});
            Face face3({pointCounter+2, pointCounter+4, pointCounter+5});
            Face face4({pointCounter+3, pointCounter+5, pointCounter+4});

            newFig.faces.push_back(face1);
            newFig.faces.push_back(face2);
            newFig.faces.push_back(face3);
            newFig.faces.push_back(face4);

            pointCounter += 6;
        }
        figure = newFig;
    }

    for (auto & point : figure.points) point.normalise();

}