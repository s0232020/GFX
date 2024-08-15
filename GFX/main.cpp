#include "main.h"
#include "ZBuffer.h"
#include <algorithm>
img::EasyImage draw2DLines(Lines2D &lines, const int &size, NormalizedColor &backgroundcolor, bool zBuffer)
{
    double xmin = lines.front().p1.x;
    double xmax = lines.front().p1.x;
    double ymin = lines.front().p1.y;
    double ymax = lines.front().p1.y;

    for(const auto& element: lines){
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

    ZBuffer zbuffer(image.get_width(), image.get_height());

    for (auto& element: lines){
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

        if (zBuffer)
            image.draw_zbuf_line(lround(p1x), lround(p1y), element.p1.z, lround(p2x), lround(p2y), element.p2.z,
                                 element.color.toEasyImageColor(), zbuffer);
        else image.draw_line(lround(p1x), lround(p1y), lround(p2x), lround(p2y), element.color.toEasyImageColor());
    }
    return image;
}

// Test
//{
//    std::list<Point2D> points;
//    for (auto &i: lines) {
//        points.push_back(i.p1);
//        points.push_back(i.p2);
//    }
//    std::list<double> xPoints;
//    std::list<double> yPoints;
//    for (auto &i: points) {
//        xPoints.push_back(i.x);
//        yPoints.push_back(i.y);
//    }
//
//    double xMax = *std::max_element(xPoints.begin(), xPoints.end());
//    double xMin = *std::min_element(xPoints.begin(), xPoints.end());
//    double yMax = *std::max_element(yPoints.begin(), yPoints.end());
//    double yMin = *std::min_element(yPoints.begin(), yPoints.end());
//
//    double xRange = xMax - xMin;
//    double yRange = yMax - yMin;
//
//    double imageX = size * (xRange / std::max(xRange, yRange));
//    double imageY = size * (yRange / std::max(xRange, yRange));
//
//    double d = 0.95 * (imageX / xRange);
//
//    double DCx = d * ((xMax + xMin)/2.0);
//    double DCy = d * ((yMax + yMin)/2.0);
//    double dx = (imageX/2.0) - DCx;
//    double dy = (imageY/2.0) - DCy;
//
//    img::Color col = backgroundcolor.toEasyImageColor();
//
//    img::EasyImage image(lround(imageX), lround(imageY), col);
//
//    ZBuffer buffer(image.get_width(), image.get_height());
//
//    for (auto &i : lines) {
//        i.p1.x = i.p1.x * d + dx;
//        i.p1.y = i.p1.y * d + dy;
//        i.p2.x = i.p2.x * d + dx;
//        i.p2.y = i.p2.y * d + dy;
//
//        img::Color lineColor = i.color.toEasyImageColor();
//
//        if (zBuffer) {
//            image.draw_zbuf_line(lround(i.p1.x), lround(i.p1.y), i.z1, lround(i.p2.x), lround(i.p2.y), i.z2, lineColor, buffer);
//        } else {
//            image.draw_line(lround(i.p1.x), lround(i.p1.y), lround(i.p2.x), lround(i.p2.y),lineColor);
//        }
//    }
//    return image;
//}


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
    img::EasyImage image = draw2DLines(lines, size, backgroundColor, false);

    return image;
}

img::EasyImage LSystem3D(const ini::Configuration &configuration, bool zBuffer)
{
    int size;
    NormalizedColor backgroundColor;
    Figures3D figures;

    if (zBuffer)
    {
        ParseLineDrawing(configuration, size, backgroundColor, figures, true);
    } else {
        ParseLineDrawing(configuration, size, backgroundColor, figures, false);
    }
    Lines2D lines = doProjection(figures);

    img::EasyImage image = draw2DLines(lines, size, backgroundColor, zBuffer);
    return image;
}

img::EasyImage zBuffer(const ini::Configuration &configuration)
{
    int size;
    NormalizedColor backgroundcolor;
    Figures3D figures;
    img::EasyImage image = ParseZBuffer(configuration, size, backgroundcolor, figures);
    return image;

}