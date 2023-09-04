#include <iostream>
#include <vector>
#include <math.h>


struct Point {
    double x;
    double y;

    bool operator==(const Point& p) const {
        return ((x == p.x) && (y == p.y));
    }

    bool operator!=(const Point& p) const {
        return !(*this == p);
    }
};

Point middle(Point P1, Point P2) {
    return {(P1.x + P2.x) / 2, (P1.y + P2.y) / 2};
}

double distance(Point P1, Point P2) {
    double dist = (P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y);
    return sqrt(dist);
}

class Line {
private:

    Point A;
    Point B;

public:

    Line(double k, double b) : A({0, b}), B({1, k}) {}

    Line(Point point, double k) : A(point), B({point.x + 1, point.y + k}) {}

    Line(Point _A, Point _B) : A(_A), B(_B) {}

    double slope() const { // for non-vertical
        return (B.y - A.y) / (B.x - A.x);
    }

    double bias() const { // for non-vertical
        return (A.y - A.x  * slope()); 
    }

    bool operator==(const Line& l) const {
        bool isVertical = (A.x == B.x), l_isVertical = (l.A.x == l.B.x);
        if (isVertical == l_isVertical) {
            if (isVertical) {
                return (A.x == l.A.x);
            } else {
                double k = slope(), _k = l.slope();
                if (k != _k) {
                    return false;
                }
                double b = bias(), _b = l.bias();
                if (b != _b) {
                    return false;
                }
                return true;
            }
        }
        return false;
    }

    bool operator!=(const Line& l) const {
        return !(*this == l);
    }
};


class Shape {};

class Polygon : public Shape {
private:

    std::vector<Point> vertices;

public:

    Polygon() = default;

    Polygon(const std::vector<Point>& points) : vertices(points) {}

    template <class... Points>
    Polygon(Point A, Points... other) : Polygon(other) {
        vertices.push_back(A);                                       // or make insertion at the beginning
    }

    size_t verticesCount() const {
        return vertices.size();
    }

    std::vector<Point> getVertices() const {
        return vertices;
    }

    bool isConvex() const {
        size_t size = vertices.size();

        Point AB = {vertices[0].x - vertices[size-1].x, vertices[0].y - vertices[size-1].y};
        Point BC = {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y};

        bool flag = (AB.x * BC.y > AB.y * BC.x);
        for (size_t i = 2; i < vertices.size(); ++i) {
            AB = {vertices[i-1].x - vertices[i-2].x, vertices[i-1].y - vertices[i-2].y};
            BC = {vertices[i].x - vertices[i-1].x, vertices[i].y - vertices[i-1].y};

            bool _flag = (AB.x * BC.y > AB.y * BC.x);
            if (flag != _flag) return false;
        }

        AB = {vertices[size-1].x - vertices[size-2].x, vertices[size-1].y - vertices[size-2].y};
        BC = {vertices[0].x - vertices[size-1].x, vertices[0].y - vertices[size-1].y};

        bool _flag = (AB.x * BC.y > AB.y * BC.x);
        if (flag != _flag) return false;
        return true;
    }
};

class Ellipse : public Shape {
private:

    Point A;
    Point B;
    double r;

public:

    Ellipse() = default;

    Ellipse(Point _A, Point _B, double _r) : A(_A), B(_B), r(_r) {}

    std::pair<Point,Point> focuses() const {
        return std::pair<Point, Point>{A, B};
    }

    std::pair<Line, Line> directrices() const {
        Point A;
        // return std::pair<Line, Line>{Line(), Line()};
    }

    double eccentricity() const {
        return distance(A, B) / r;   // == 2c / 2a
    }

    Point center() const {
        return middle(A, B);
    }
};

class Circle : public Ellipse {
private:

    Point center;
    double r;

public:

    Circle(Point _center, double _r) {}

    double radius() const {

    }
};

class Rectangle : public Polygon {
private:

    Point A, B, C, D;

public:

    Rectangle() = default;

    Rectangle(Point A, Point B, double k) {

    }

    Point center() const {

    }

    std::pair<Line, Line> diagonals() const {}
};

class Square : public Rectangle {
private:

    Point A, B, C, D;

public:

    Square(Point A, Point B) {}

    Circle circumscribedCircle() const {}
    
    Circle inscribedCircle() const {}
};

class Triangle : public Polygon {
private:

    Point A, B, C;

public:

    Point orthocenter() const {} 
    
    Line EulerLine() const {} 
    
    Circle ninePointsCircle() const {}


    Point centroid() const {}

    Circle circumscribedCircle() const {}
    
    Circle inscribedCircle() const {}
};
