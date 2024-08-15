#include "Parser.h"
#include "ZBuffer.h"

void ParseLineDrawing(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor, Figures3D &figures, bool zBuffer)
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
        const double scale = configuration[figureKey]["scale"].as_double_or_die();
        const double rotateXangle = configuration[figureKey]["rotateX"].as_double_or_die();
        const double rX = toRad(rotateXangle);
        const double rotateYangle = configuration[figureKey]["rotateY"].as_double_or_die();
        const double rY = toRad(rotateYangle);
        const double rotateZangle = configuration[figureKey]["rotateZ"].as_double_or_die();
        const double rZ = toRad(rotateZangle);
        std::vector<double> centerpoint = configuration[figureKey]["center"].as_double_tuple_or_die();
        Vector3D center = Vector3D::vector(centerpoint[0], centerpoint[1], centerpoint[2]);
        std::string FigureType = configuration[figureKey]["type"];
        Figure figure;



        if (FigureType == "LineDrawing") TransformLineDrawing(figure, configuration, figureKey);

        if (FigureType == "Cube") createCube(figure);

        if (FigureType == "Tetrahedron") createTetrahedron(figure);

        if (FigureType == "Octahedron") createOctahedron(figure);

        if (FigureType == "Icosahedron") createIcosahedron(figure);

        if (FigureType == "Dodecahedron") createDodecahedron(figure);

        if (FigureType == "3DLSystem") create3DLSystem(configuration, figure, figureKey);

        if (FigureType == "Cone" || FigureType == "Cylinder")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            const double h = configuration[figureKey]["height"].as_double_or_die();
            if (FigureType == "Cone") createCone(figure, n, h);
            if (FigureType == "Cylinder") createCylinder(figure, n, h);
        }

        if (FigureType == "Sphere")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            createSphere(figure, n);
        }

        if (FigureType == "Torus")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            const int m = configuration[figureKey]["m"].as_int_or_die();
            const double R = configuration[figureKey]["R"].as_double_or_die();
            const double r = configuration[figureKey]["r"].as_double_or_die();
            createTorus(figure, n, m, R, r);
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

LParser::LSystem3D ReadLSystem3D(const std::string &inputfile, std::set<char> &alphabet, double &angle, std::string &initiator,
                               unsigned int &iterations)
{
    LParser::LSystem3D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    alphabet = l_system.get_alphabet();
    angle = l_system.get_angle();
    initiator = l_system.get_initiator();
    iterations = l_system.get_nr_iterations();

    return l_system;
}

img::EasyImage ParseZBuffer(const ini::Configuration &configuration, int &size, NormalizedColor &backgroundcolor, Figures3D &figures)
{
    Figures3D temp;

    size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = NormalizedColor(backgroundColor);
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyepoint = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyepoint[0], eyepoint[1], eyepoint[2]);
    for (int figIndex = 0; figIndex < nrFigures; figIndex++)
    {
        std::string figureKey = "Figure" + std::to_string(figIndex);
        std::vector<double> color = configuration[figureKey]["color"].as_double_tuple_or_die();
        NormalizedColor Color(color);
        const double scale = configuration[figureKey]["scale"].as_double_or_die();
        const double rotateXangle = configuration[figureKey]["rotateX"].as_double_or_die();
        const double rX = toRad(rotateXangle);
        const double rotateYangle = configuration[figureKey]["rotateY"].as_double_or_die();
        const double rY = toRad(rotateYangle);
        const double rotateZangle = configuration[figureKey]["rotateZ"].as_double_or_die();
        const double rZ = toRad(rotateZangle);

        std::vector<double> centerpoint = configuration[figureKey]["center"].as_double_tuple_or_die();
        Vector3D center = Vector3D::vector(centerpoint[0], centerpoint[1], centerpoint[2]);
        std::string FigureType = configuration[figureKey]["type"];
        Figure figure;

        if (FigureType == "LineDrawing") TransformLineDrawing(figure, configuration, figureKey);

        if (FigureType == "Cube") createCube(figure);

        if (FigureType == "Tetrahedron") createTetrahedron(figure);

        if (FigureType == "Octahedron") createOctahedron(figure);

        if (FigureType == "Icosahedron") createIcosahedron(figure);

        if (FigureType == "Dodecahedron") createDodecahedron(figure);

        if (FigureType == "3DLSystem") create3DLSystem(configuration, figure, figureKey);

        if (FigureType == "Cone" || FigureType == "Cylinder")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            const double h = configuration[figureKey]["height"].as_double_or_die();
            if (FigureType == "Cone") createCone(figure, n, h);
            if (FigureType == "Cylinder") createCylinder(figure, n, h);
        }

        if (FigureType == "Sphere")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            createSphere(figure, n);
        }

        if (FigureType == "Torus")
        {
            const int n = configuration[figureKey]["n"].as_int_or_die();
            const int m = configuration[figureKey]["m"].as_int_or_die();
            const double R = configuration[figureKey]["R"].as_double_or_die();
            const double r = configuration[figureKey]["r"].as_double_or_die();
            createTorus(figure, n, m, R, r);
        }

        figure.color = Color;
        Matrix m = lineDrawing(scale, rX, rY, rZ, center, eye);
        ApplyTransformation(figure, m);
        temp.emplace_back(figure);
        backgroundcolor.toEasyImageColor();
    }

    for (auto& figure : temp)
    {
        ZBuffer::triangulate(figure);
        figures.emplace_back(figure);
    }

    Lines2D lines = doProjection(figures);

    double width, height, d, dx, dy;
    ZBuffer::calculations(size, width, height, d, dx, dy, lines);

    img::EasyImage image(lround(width), lround(height), backgroundcolor.toEasyImageColor());
    ZBuffer zbuffer(image.get_width(), image.get_height());

    for (auto &figure : figures) {
        for (auto &face : figure.faces) {
            image.draw_zbuf_triag(
                                  figure.points[face.point_indexes[0]],
                                  figure.points[face.point_indexes[1]],
                                  figure.points[face.point_indexes[2]],
                                  d, dx, dy, figure.color.toEasyImageColor(), zbuffer);
        }
    }
    return image;
}