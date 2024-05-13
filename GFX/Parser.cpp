#include "Parser.h"
void ParseLineDrawing(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor, Figures3D &figures)
{
    size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundcolorVec = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundColor = NormalizedColor(backgroundcolorVec);
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyepoint = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyepoint[0], eyepoint[1], eyepoint[2]);

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
        std::string FigureType = configuration[figureKey]["type"];
        Figure figure;
        if (FigureType == "LineDrawing")
        {
            TransformLineDrawing(figure, configuration, figureKey);
        }

        if (FigureType == "Cube")
        {
            createCube(figure);
        }

        if (FigureType == "Tetrahedron")
        {
            createTetrahedron(figure);
        }

        if (FigureType == "Octahedron")
        {
            createOctahedron(figure);
        }

        if (FigureType == "Icosahedron")
        {
            createIcosahedron(figure);
        }

        if (FigureType == "Dodecahedron")
        {
            createDodecahedron(figure);
        }

        if (FigureType == "3DLSystem")
        {
            create3DLSystem(figure, configuration, figIndex);
        }

        figure.color = Color;
        Matrix m = lineDrawing(scale, rX, rY, rZ, center, eye);
        ApplyTransformation(figure, m);
        figures.emplace_back(figure);
        backgroundColor.toEasyImageColor();
    }
}

LParser::LSystem2D ReadLSystem(const std::string &inputfile, std::set<char> &alphabet, double &angle, std::string &initiator,
                               unsigned int &iterations, double &starting_angle)
{
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