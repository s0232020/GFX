#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

struct NormalizedColor{
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    NormalizedColor(){

    }

    NormalizedColor(const std::vector<double>& doubleVec){
        if(doubleVec.size() == 3){
            r = doubleVec[0];
            g = doubleVec[1];
            b = doubleVec[2];
        }
        else{
            throw std::runtime_error("Vector verkeerde size");
        }
    }
    img::Color toEasyImageColor() const {
        img::Color returnValue;
        returnValue.red = r * 255.0;
        returnValue.green = g * 255.0;
        returnValue.blue = b * 255.0;
        return returnValue;
    }

};


struct Point2D{
    double x = 0.0;
    double y = 0.0;

    Point2D(){

    }

    Point2D(double x, double y){
        this->x = x;
        this->y = y;
    }
};

struct Line2D{
    Point2D p1;
    Point2D p2;
    NormalizedColor color;

    Line2D(){}

    Line2D(Point2D p1, Point2D p2){
        this->p1 = p1;
        this->p2 = p2;
    }

    Line2D(Point2D p1, Point2D p2, NormalizedColor& color){
        this->p1 = p1;
        this->p2 = p2;
        this->color = color;
    }
};

inline double toRad(double degrees){
    return degrees * M_PI / 180.0;
}

struct Face{
    std::vector<int> point_indexes;
};
struct Figure{
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    NormalizedColor color;
};

typedef std::list<Figure> Figures3D;
using Lines2D = std::vector<Line2D>;
#endif //ENGINE_UTILS_H
