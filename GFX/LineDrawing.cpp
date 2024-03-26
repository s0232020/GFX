#include "LineDrawing.h"

void TransformLineDrawing(Figure &figure, const ini::Configuration &configuration, std::string &figureKey) {
    int nrPoints = configuration[figureKey]["nrPoints"].as_int_or_die();
    int nrLines = configuration[figureKey]["nrLines"].as_int_or_die();

    for (int i = 0; i < nrPoints; i++) {
        std::vector<double> pointData = configuration[figureKey]["point" +
                                                                 std::to_string(i)].as_double_tuple_or_die();
        Vector3D vector = Vector3D::point(pointData[0], pointData[1], pointData[2]);
        figure.points.emplace_back(vector);
    }

    for (int i = 0; i < nrLines; i++) {
        std::vector<int> point_indexes = configuration[figureKey]["line" +
                                                                  std::to_string(i)].as_int_tuple_or_die();
        Face face;
        for (int index: point_indexes) {
            face.point_indexes.emplace_back(index);
        }
        figure.faces.emplace_back(face);
    }
}