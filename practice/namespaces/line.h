#ifndef __LINE_H
#define __LINE_H

#include "point.h"
#include <string>

namespace Geom{
    class Line{
        public:
            Line(const Point& From, const Point& To);
            double slope();
            friend std::ostream& operator<<(std::ostream& output, const Line& l);
        private:
            Point from;
            Point to;
    };
}

#endif // __LINE_H