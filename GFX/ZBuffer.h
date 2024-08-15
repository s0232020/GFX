#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>

class Figure;
class Line2D;
using Lines2D = std::vector<Line2D>;


class ZBuffer {
public:
    ZBuffer(unsigned int width, unsigned int height);
    bool should_draw(unsigned int x, unsigned int y, double z_value_of_pixel);
    void update(int x, int y, double z_value_of_pixel);
    static void triangulate(Figure &fig);
    static void calculations(int &size, double &width, double &height, double &d, double &dx, double &dy, Lines2D &lines);
    double get(unsigned int x, unsigned int y);
private:
    std::vector<std::vector<double>> zbuffer;
};

#endif //ENGINE_ZBUFFER_H
