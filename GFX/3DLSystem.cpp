#include "3DLSystem.h"


Vector3D transform(const Vector3D& position, const Vector3D& rotation) {
    Vector3D newPosition;
    // Implement the transformation of position by the given rotation
    // This is just a placeholder. Replace this with your actual transformation logic.
    newPosition.x = position.x + rotation.x;
    newPosition.y = position.y + rotation.y;
    newPosition.z = position.z + rotation.z;
    return newPosition;
}

Lines2D create3DLSystem(Figure &figure, const ini::Configuration &configuration, int figIndex, Lines2D& lines, NormalizedColor& color)
{
    std::set<char> alphabet;
    double angle;
    std::string initiator;
    unsigned int iterations;

    std::string inputfile = configuration["Figure" + std::to_string(figIndex)]["inputfile"].as_string_or_die();
    LParser::LSystem3D l_system = ReadLSystem3D(inputfile, alphabet, angle, initiator, iterations);
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

    // Interpret the L-system string as drawing commands
    std::stack<Vector3D> positions;
    std::stack<double> angles;
    Vector3D position;
    position.x = 0;
    position.y = 0;
    position.z = 0;
    double currentAngle = 0.0;
    Vector3D rotation; // Declare rotation variable here

    Vector3D vectorH = Vector3D::point(1, 0, 0);
    Vector3D vectorL = Vector3D::point(0, 1, 0);
    Vector3D vectorU = Vector3D::point(0, 0, 1);


    for (char command : currentString) { // Changed from initiator to currentString
        std::cout << "Processing command: " << command << std::endl;
        Vector3D newPosition;
        if (alphabet.find(command) != alphabet.end()) {
            if(l_system.draw(command)) {
                // Draw a line segment
                std::cout << "Drawing command: " << command << std::endl;
                newPosition.x = position.x;
                newPosition.y = position.y + 1.0;
                newPosition.z = position.z;
                figure.points.push_back(position);
                figure.points.push_back(newPosition);
                if (position.z != 0 && newPosition.z != 0) {
                    Point2D oldPoint2D(position.x / position.z, position.y / position.z);
                    Point2D newPoint2D(newPosition.x / newPosition.z, newPosition.y / newPosition.z);
                    // Create a 2D line from the projected points
                    Line2D line(oldPoint2D, newPoint2D, color);
                    lines.push_back(line);
                } else {
                    std::cerr << "Error: Division by zero in point projection." << std::endl;
                }
                position = newPosition;
            }
        } else {
            std::cout << "Non-drawing command: " << command << std::endl;
            Vector3D newVecH;
            Vector3D newVecL;
            Vector3D newVecU;
            switch (command) {
                case '+':
                    // Rotate left
                    newVecH = vectorH * cos(angle) + vectorL * sin(angle);
                    newVecL = -(vectorH * sin(angle)) + vectorL * cos(angle);
                    vectorH = newVecH;
                    vectorL = newVecL;
                    break;
                case '-':
                    // Rotate right
                    newVecH = vectorH * cos(-angle) + vectorL * sin(-angle);
                    newVecL = -(vectorH * sin(-angle)) + vectorL * cos(-angle);
                    vectorH = newVecH;
                    vectorL = newVecL;
                    break;
                case '^':
                    // Rotate upwards
                    newVecH = vectorH * cos(angle) + vectorU * sin(angle);
                    newVecU = -(vectorH * sin(angle)) + vectorU * cos(angle);
                    vectorH = newVecH;
                    vectorU = newVecU;
                    break;
                case '&':
                    // Rotate downwards
                    newVecH = vectorH * cos(-angle) + vectorU * sin(-angle);
                    newVecU = -(vectorH * sin(-angle)) + vectorU * cos(-angle);
                    vectorH = newVecH;
                    vectorU = newVecU;
                    break;
                case '\\':
                    // Roll left
                    newVecL = vectorL * cos(angle) - vectorU * sin(angle);
                    newVecU = vectorL * sin(angle) + vectorU * cos(angle);
                    vectorL = newVecL;
                    vectorU = newVecU;
                    break;
                case '/':
                    // Roll right
                    newVecL = vectorL * cos(-angle) - vectorU * sin(-angle);
                    newVecU = vectorL * sin(-angle) + vectorU * cos(-angle);
                    vectorL = newVecL;
                    vectorU = newVecU;
                    break;
                case '(':
                    // Save the current position and angle
                    positions.push(position);
                    angles.push(currentAngle);
                    break;
                case ')':
                    // Restore the saved position and angle
                    if (!positions.empty() && !angles.empty()) {
                        position = positions.top();
                        positions.pop();
                        currentAngle = angles.top();
                        angles.pop();
                    } else {
                        std::cerr << "Error: Attempted to pop from an empty stack." << std::endl;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return lines;
}
