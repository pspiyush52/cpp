#include "line.h"

namespace Geom{
    Line::Line(const Point& From, const Point& To):
        from(From), to(To){
        }

    double Line::slope(){
        return ((to['y'] - from['y']) / (to['x'] - from['x']));
    }

    std::ostream& operator<<(std::ostream& output, const Line& l){
        output << "Line [from: " << l.from << ", to: " << l.to << "]";
        return output;
    }
}