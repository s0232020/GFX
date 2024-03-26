#include "main.h"
img::EasyImage draw2DLines(const Lines2D &lines,const int &size, NormalizedColor &backgroundcolor){
    double xmin = lines.front().p1.x;
    double xmax = lines.front().p1.x;
    double ymin = lines.front().p1.y;
    double ymax = lines.front().p1.y;

    for(const auto& element:lines){
        if (element.p1.x > xmax){
            xmax = element.p1.x;
        }
        if (element.p2.x > xmax){
            xmax = element.p2.x;
        }
        if (element.p1.x < xmin){
            xmin = element.p1.x;
        }
        if (element.p2.x < xmin){
            xmin = element.p2.x;
        }
        if (element.p1.y < ymin){
            ymin = element.p1.y;
        }
        if (element.p2.y < ymin){
            ymin = element.p2.y;
        }
        if (element.p1.y > ymax){
            ymax = element.p1.y;
        }
        if (element.p2.y > ymax){
            ymax = element.p2.y;
        }
    }

    double xrange = xmax - xmin;
    double yrange = ymax - ymin;

    double imagex = size*(xrange/std::max(xrange,yrange));
    double imagey = size*(yrange/std::max(xrange,yrange));
    double d = 0.95*(imagex/xrange);
    double dcx = d*((xmin+xmax)/2);
    double dcy = d*((ymin+ymax)/2);

    double dx = (imagex/2)-dcx;
    double dy = (imagey/2)-dcy;
    img::Color convert = backgroundcolor.toEasyImageColor();
    img::EasyImage image(imagex, imagey, convert);


    for (auto& element:lines){
        double p1x = 0.0;
        double p2x = 0.0;
        double p1y = 0.0;
        double p2y = 0.0;
        p1x = element.p1.x*d;
        p1y = element.p1.y*d;
        p2x = element.p2.x*d;
        p2y = element.p2.y*d;
        p1x = p1x + dx;
        p1y = p1y + dy;
        p2x = p2x + dx;
        p2y = p2y + dy;
        image.draw_line(p1x, p1y, p2x, p2y, element.color.toEasyImageColor());
    }
    return image;
}

Lines2D DrawLSystem(LParser::LSystem2D &l_system, const ini::Configuration &configuration, int &size, NormalizedColor &backgroundColor)
{
    std::vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> backgroundcolorVec = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    std::set<char> alphabet;
    double angle;
    std::string initiator;
    unsigned int iterations;
    double starting_angle;

    l_system = ReadLSystem(inputfile, alphabet, angle, initiator, iterations, starting_angle);

    Lines2D lines;
    NormalizedColor Color(color);
    Color.toEasyImageColor();
    backgroundColor = NormalizedColor(backgroundcolorVec);

    // Voer de L-system iteraties uit
    std::string currentString = initiator;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        std::string nextString;
        for (char ch : currentString)
        {
            if (alphabet.find(ch) != alphabet.end())
            {
                nextString += l_system.get_replacement(ch);
            } else
            {
                nextString += ch;
            }
        }
        currentString = nextString;
    }

    // Interpreteer de resulterende string als instructies voor het tekenen van lijnen
    Point2D oldPoint(0,0); // Muaz
    Point2D newPoint(0,0); // Muaz
    std::vector<std::vector<double>> bracket_stack;
    double currentAngle = starting_angle;
    
    for (char instruction : currentString)
    { // Deze hele for loop is geinspireerd door de code van Muaz Moin, hij heeft mij geholpen
        if (instruction == '+')
        {
            currentAngle += angle;
        } else if (instruction == '-')
        {
            currentAngle -= angle;
        } else if (instruction == '(')
        {
            bracket_stack.push_back({newPoint.x, newPoint.y, currentAngle}); // Store current angle on opening bracket
        } else if (instruction == ')')
        { // Handle closing bracket
            if (!bracket_stack.empty())
            {
                currentAngle = bracket_stack.back()[2]; // Restore angle from stack
                newPoint.x = bracket_stack.back()[0];
                newPoint.y = bracket_stack.back()[1];
                bracket_stack.pop_back();
            }
        }
        else
        { // Als de letter een teken voor een lijn is
            oldPoint = newPoint;
            newPoint.x = oldPoint.x + std::cos(currentAngle * M_PI / 180.0);
            newPoint.y = oldPoint.y + std::sin(currentAngle * M_PI / 180.0);
            if(l_system.draw(instruction))
            {
                Line2D line(oldPoint, newPoint, Color);
                lines.emplace_back(line);
            } else
            {
                ;
            }
        }
    }
    return lines;
}
img::EasyImage LSystem2D(const ini::Configuration &configuration)
{
    int size = 0;
    NormalizedColor backgroundColor;
    LParser::LSystem2D l_system;

    Lines2D lines = DrawLSystem(l_system, configuration, size, backgroundColor);
    img::EasyImage image = draw2DLines(lines, size, backgroundColor);

    return image;
}

img::EasyImage LSystem3D(const ini::Configuration &configuration)
{
    int size;
    NormalizedColor backgroundColor;
    Figures3D figures;

    ParseLineDrawing(configuration, size, backgroundColor, figures);

    Lines2D lines = doProjection(figures);

    img::EasyImage image = draw2DLines(lines, size, backgroundColor);
    return image;
}

