#include "struct.h"

void setCircle(Circle* c, Dot center, float r);
void circleInfo(Circle c);
float circleLen(Circle c);
float circleAr(Circle c);

void setSquare(Square* s, Dot upLeft, float l);
void squareInfo(Square s);
float squarePer(Square s);
float squareAr(Square s);

bool inCircle(Dot d, Circle c);
bool inSquare(Dot d, Square s);

bool onCircle(Dot d, Circle c);
bool onSquare(Dot d, Square s);

bool circlesInter(Circle a, Circle b);
bool squaresInter(Square a, Square b);
bool difInter(Circle c, Square s);

bool circle_in_circle(Circle c1, Circle c2);
bool square_in_square(Square s1, Square s2);
bool square_in_circle(Square s, Circle c);
bool circle_in_square(Circle c, Square s);