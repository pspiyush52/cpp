#ifndef __POINT_H
#define __POINT_H

#include <iostream>
#include <cmath>

namespace Geom{
    class Point {
        public:
            Point();
            explicit Point(double xy);
            Point(double x, double y);
            double distance(const Point& p) const;
            double length() const;
            double slope() const;
            double get_x() const;
            double get_y() const;
            unsigned int quadrant() const;
            bool operator==(const Point& p) const;
            Point operator+(const Point& p) const;
            Point operator-(const Point& p) const;
            void operator+=(const Point& p);
            void operator-=(const Point& p);
            const double& operator[](char axis) const;  // getter for const objects
            double& operator[](char axis);  // getter and setter for non-const objects
            Point& operator++();  // prefix
            Point operator++(int);  // postfix
            Point& operator--();  // prefix
            Point operator--(int);  // postfix
            friend std::ostream& operator<<(std::ostream& output, const Point& p);
            static unsigned int get_point_count();
        private:
            double m_x;
            double m_y;
            static inline unsigned int point_count{};
    };
}

#endif // __POINT_H