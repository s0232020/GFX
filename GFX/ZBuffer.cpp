#include "ZBuffer.h"
#include <limits>
#include "Utils.h"

ZBuffer::ZBuffer(const unsigned int width, const unsigned int height) : zbuffer(width, std::vector<double>(height, std::numeric_limits<double>::infinity())) {}

bool ZBuffer::should_draw(unsigned int x, unsigned int y, double z_value_of_pixel) {
    return z_value_of_pixel < zbuffer[x][y];
}

void ZBuffer::update(int x, int y, double z_value_of_pixel) { // changed from unsigned int to int
    zbuffer[x][y] = z_value_of_pixel;
}

void ZBuffer::triangulate(Figure &fig)
{
    std::vector<Face> newFaces;

    for (auto &f: fig.faces) {
        if (f.point_indexes.size() > 3) {
            for (unsigned int i = 1; i < f.point_indexes.size()-1; i++) {
                Face newFace({f.point_indexes[0], f.point_indexes[i], f.point_indexes[i+1]});
                newFaces.push_back(newFace);
            }
        } else newFaces.push_back(f);
    }
    fig.faces = newFaces;
}

void ZBuffer::calculations(int &size, double &width, double &height, double &d, double &dx, double &dy, Lines2D &lines)
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

    width = size * (xrange / std::max(xrange,yrange));
    height = size * (yrange / std::max(xrange,yrange));
    d = 0.95 * (width / xrange);
    double dcx = d * ((xmin + xmax) / 2);
    double dcy = d * ((ymin + ymax) / 2);

    dx = (width / 2) - dcx;
    dy = (height / 2) - dcy;


}

double ZBuffer::get(unsigned int x, unsigned int y)
{
    return zbuffer[x][y];
}