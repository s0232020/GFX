#include "Parser.h"
void Parse3DLSystem(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor, Figures3D &figures)
{
    size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundcolorVec = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundColor = NormalizedColor(backgroundcolorVec);
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyepoint = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyepoint[0], eyepoint[1], eyepoint[2]);

    std::vector<Lines2D> vecLines;

    for (int figIndex = 0; figIndex < nrFigures; figIndex++) {
        std::string figureKey = "Figure" + std::to_string(figIndex);
        std::vector<double> color = configuration[figureKey]["color"].as_double_tuple_or_die();
        NormalizedColor Color(color);
        double scale = configuration[figureKey]["scale"].as_double_or_die();
        double rotateXangle = configuration[figureKey]["rotateX"].as_double_or_die();
        double rX = toRad(rotateXangle);
        double rotateYangle = configuration[figureKey]["rotateY"].as_double_or_die();
        double rY = toRad(rotateYangle);
        double rotateZangle = configuration[figureKey]["rotateZ"].as_double_or_die();
        double rZ = toRad(rotateZangle);
        std::vector<double> centerpoint = configuration[figureKey]["center"].as_double_tuple_or_die();
        Vector3D center = Vector3D::vector(centerpoint[0], centerpoint[1], centerpoint[2]);
        int nrPoints = configuration[figureKey]["nrPoints"].as_int_or_die();
        int nrLines = configuration[figureKey]["nrLines"].as_int_or_die();

        Figure figure;
        for (int i = 0; i < nrPoints; i++) {
            std::vector<double> pointData = configuration[figureKey]["point" + std::to_string(i)].as_double_tuple_or_die();
            Vector3D vector = Vector3D::point(pointData[0], pointData[1], pointData[2]);
            figure.points.emplace_back(vector);
        }

        for (int i = 0; i < nrLines; i++) {
            std::vector<int> point_indexes = configuration[figureKey]["line" + std::to_string(i)].as_int_tuple_or_die();
            Face face;
            for (int index : point_indexes) {
                face.point_indexes.emplace_back(index);
            }
            figure.faces.emplace_back(face);
        }
        figure.color = Color;
        Matrix m = lineDrawing(scale, rX, rY, rZ, center, eye);
        ApplyTransformation(figure, m);
        figures.emplace_back(figure);
    }
    backgroundColor.toEasyImageColor();
}

LParser::LSystem2D ReadLSystem(std::string inputfile, std::set<char> &alphabet, double &angle, std::string &initiator,
                               unsigned int &iterations, double &starting_angle){
    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    alphabet = l_system.get_alphabet();
    angle = l_system.get_angle();
    initiator = l_system.get_initiator();
    iterations = l_system.get_nr_iterations();
    starting_angle = l_system.get_starting_angle();

    return l_system;
}