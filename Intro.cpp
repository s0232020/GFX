#include "Include.h"
img::EasyImage colorRectangle(const ini::Configuration &configuration)
{
    int width = configuration["ImageProperties"]["width"].as_int_or_die();
    int height = configuration["ImageProperties"]["height"].as_int_or_die();
    img::EasyImage image(width, height);
    for(unsigned int i = 0; i < width; i++){
        for (unsigned int j = 0; j < height; j++){
            image(i,j).red = i;
            image(i,j).green = j;
            image(i,j).blue = (i+j)%width;

        }
    }
    return image;
}

img::EasyImage introBlocks(const ini::Configuration &configuration){
    int Wi = configuration["ImageProperties"]["width"].as_int_or_die();
    int Hi = configuration["ImageProperties"]["height"].as_int_or_die();
    img::EasyImage image(Wi, Hi);
    std::vector<double> colorWhiteVec = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
    std::vector<double> colorBlackVec = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
    int nrXBlocks = configuration["BlockProperties"]["nrXBlocks"].as_int_or_die();
    int nrYBlocks = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die();
    bool invertColors = configuration["BlockProperties"]["invertColors"].as_bool_or_die();

    int Wb = Wi/nrXBlocks;
    int Hb = Hi/nrYBlocks;

    Color white(colorWhiteVec);
    Color black(colorBlackVec);

    for (unsigned int i = 0; i < Hi; i++) {
        for (unsigned int j = 0; j < Wi; j++) {
            if ((i / Hb + j / Wb) % 2 == 0) {
                image(i, j).red = 255;
                image(i, j).green = 255;
                image(i, j).blue = 255;
            } else {
                image(i, j).red = 0;
                image(i, j).green = 0;
                image(i, j).blue = 0;
            }
        }
    }


    return image;
}

img::EasyImage linesQuarterCircle(const ini::Configuration &configuration){
    int Wi = configuration["ImageProperties"]["width"].as_int_or_die();
    int Hi = configuration["ImageProperties"]["height"].as_int_or_die();
    img::EasyImage image(Wi, Hi);
    std::vector<double> backgroundColor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    std::vector<double> lineColor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
    int nrLines = configuration["LineProperties"]["nrLines"].as_int_or_die();

    int Hs = Hi/(nrLines - 1);
    int Ws = Wi/(nrLines - 1);

    Color LineColor(lineColor);
    Color BackgroundColor(backgroundColor);

    for (unsigned int i = 0; i < Hi; i++) {
        for (unsigned int j = 0; j < Wi; j++) {
            ;
        }
    }

    return image;
}


img::EasyImage draw2DLines(const Lines2D &lines,const int size){
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
    img::EasyImage image(imagex, imagey);
    img::Color color(color);


    for (const auto& element:lines){
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
        image.draw_line(p1x, p1y, p2x, p2y, color);
    }
    return image;
}

img::EasyImage linesDiamond(const ini::Configuration &configuration){
    int nrlines = configuration["LineProperties"]["nrLines"].as_int_or_die();
    int width = configuration["ImageProperties"]["width"].as_int_or_die();
    int height = configuration["ImageProperties"]["height"].as_int_or_die();
    std::vector<double> backgroundColor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    std::vector<double> lineColor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
    img::EasyImage image(width, height);

    Color LineColor(lineColor);
    Color BackgroundColor(backgroundColor);


    return image;
}
void ReadLSystem(std::string inputfile){
    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    std::set<char> alphabet = l_system.get_alphabet();
    double angle = l_system.get_angle();
    std::string initiator = l_system.get_initiator();
    unsigned int iterations = l_system.get_nr_iterations();
    double starting_angle = l_system.get_starting_angle();

    for (char c:alphabet){
        bool draw = l_system.draw(c);
        std::string replacement = l_system.get_replacement(c);
    }
}



img::EasyImage LSystem2D(const ini::Configuration &configuration){
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    std::string inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    std::vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    ReadLSystem(inputfile);
    img::EasyImage image(size,size);
    return image;
}


//Lines2D DrawLSystem(const LParser::LSystem2D &l_system){
//    todo
//}