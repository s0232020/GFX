#include "3DLSystem.h"

Face::Face(std::vector<int> i) : point_indexes(std::move(i)) {}

Vector3D transform(const Vector3D& position, const Vector3D& rotation) {
    Vector3D newPosition;
    // Implement the transformation of position by the given rotation
    // This is just a placeholder. Replace this with your actual transformation logic.
    newPosition.x = position.x + rotation.x;
    newPosition.y = position.y + rotation.y;
    newPosition.z = position.z + rotation.z;
    return newPosition;
}


void create3DLSystem(const ini::Configuration &configuration, Figure &figure, const std::string &figureKey) {
    // Load the L-system from the configuration
    const std::string inputfile = configuration[figureKey]["inputfile"].as_string_or_die();
    std::set<char> alphabet;
    double angle;
    std::string initiator;
    unsigned int iterations;

    LParser::LSystem3D l_system = ReadLSystem3D(inputfile, alphabet, angle, initiator, iterations);

    std::vector<double> center = configuration[figureKey]["center"].as_double_tuple_or_die();;

    std::map<char, std::string> replacements;
    std::map<char, bool> draw;
    for (auto i: alphabet) {
        draw[i] = l_system.draw(i);
        replacements[i] = l_system.get_replacement(i);
    }

    angle = (angle*M_PI)/180;

    Vector3D curPoint = Vector3D::point(0, 0, 0);
    Vector3D H = Vector3D::vector(1, 0, 0);
    Vector3D L = Vector3D::vector(0, 1, 0);
    Vector3D U = Vector3D::vector(0, 0, 1);
    std::stack<Vector3D> pointStack;
    std::stack<Vector3D> HStack;
    std::stack<Vector3D> LStack;
    std::stack<Vector3D> UStack;


    figure.points.push_back(curPoint);
    int indexCounter = 0;

    for (unsigned int i = 0; i < iterations; i++) {
        std::string replacement;
        for (auto j: initiator) {
            if (j == '+') replacement += "+";
            else if (j == '-') replacement += "-";
            else if (j == '(') replacement += "(";
            else if (j == ')') replacement += ")";
            else if (j == '^') replacement += "^";
            else if (j == '&') replacement += "&";
            else if (j == '\\') replacement += "\\";
            else if (j == '/') replacement += "/";
            else if (j == '|') replacement += "|";
            else replacement += replacements[j];
        }
        initiator = replacement;
    }

    std::vector<Vector3D> toAdd;
    for (unsigned int k = 0; k < initiator.length(); k++) {
        char i = initiator[k];
        if (i == '+') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempH(H);
            H = (H*cos(angle)) + (L*sin(angle));
            L = (L*cos(angle)) - (tempH*sin(angle));
            continue;
        }
        if (i == '-') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempH(H);
            H = (H*cos(-angle)) + (L*sin(-angle));
            L = (L*cos(-angle)) - (tempH*sin(-angle));
            continue;
        }
        if (i == '^') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempH(H);
            H = (H*cos(angle)) + (U*sin(angle));
            U = (U*cos(angle)) - (tempH*sin(angle));
            continue;
        }
        if (i == '&') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempH(H);
            H = (H*cos(-angle)) + (U*sin(-angle));
            U = (U*cos(-angle)) - (tempH*sin(-angle));
            continue;
        }
        if (i == '\\') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempL(L);
            L = (L*cos(angle)) - (U*sin(angle));
            U = (tempL*sin(angle)) + (U*cos(angle));
            continue;
        }
        if (i == '/') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            Vector3D tempL(L);
            L = (L*cos(-angle)) - (U*sin(-angle));
            U = (tempL*sin(-angle)) + (U*cos(-angle));
            continue;
        }
        if (i == '|') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            H = -H;
            L = -L;
            continue;
        }
        if (i == '(') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            pointStack.push(curPoint);
            HStack.push(H);
            LStack.push(L);
            UStack.push(U);
            continue;
        }
        if (i == ')') {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
            curPoint = pointStack.top();
            pointStack.pop();
            H = HStack.top();
            HStack.pop();
            L = LStack.top();
            LStack.pop();
            U = UStack.top();
            UStack.pop();

            figure.points.push_back(curPoint);
            indexCounter++;
            continue;
        }
        curPoint += H;
        if (draw[i]) toAdd.push_back(curPoint);
        else {
            if (!toAdd.empty()) {
                figure.points.push_back(toAdd[toAdd.size()-1]);
                indexCounter++;
                Face newFace({indexCounter, indexCounter-1});
                figure.faces.push_back(newFace);
                toAdd.clear();
            }
        }
    }


}