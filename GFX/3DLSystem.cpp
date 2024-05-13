#include "3DLSystem.h"

void create3DLSystem(Figure &figure, const ini::Configuration &configuration, int figIndex)
{
    std::set<char> alphabet;
    double angle;
    std::string initiator;
    unsigned int iterations;
    double starting_angle;

    std::string inputfile = configuration["Figure" + std::to_string(figIndex)]["inputfile"].as_string_or_die();
    LParser::LSystem2D l_system = ReadLSystem(inputfile, alphabet, angle, initiator, iterations, starting_angle);

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

    for (char command : initiator) {
        Vector3D newPosition;
        if (alphabet.find(command) != alphabet.end()) {
            if(l_system.draw(command)) {
                // Draw a line segment
                newPosition.x = position.x;
                newPosition.y = position.y + 1.0;
                newPosition.z = position.z;
                figure.points.push_back(position);
                figure.points.push_back(newPosition);
                position = newPosition;
            }
        } else {
            switch (command) {
                case '+':
                    // Rotate left
                    currentAngle += angle; // Adjust angle based on your rotation step
                    break;
                case '-':
                    // Rotate right
                    currentAngle -= angle; // Adjust angle based on your rotation step
                    break;
                case '^':
                    // Rotate upwards
                    // Use rotation variable here
                    // Implement rotation logic here
                    break;
                case '&':
                    // Rotate downwards
                    // Use rotation variable here
                    // Implement rotation logic here
                    break;
                case '\\':
                    // Roll left
                    // Use rotation variable here
                    // Implement rotation logic here
                    break;
                case '/':
                    // Roll right
                    // Use rotation variable here
                    // Implement rotation logic here
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
                    }
                    break;
                default:
                    break;
            }
        }
    }
}