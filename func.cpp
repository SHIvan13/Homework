#include "func.h"
#include <iostream>
#include <cmath>

void setCircle(Circle* c, Dot center, float r){
    c->center = center;
    c->rad = r;
}

void circleInfo(Circle c){
    std::cout << "center x: " << c.center.x << std::endl;
    std::cout << "center y: " << c.center.y << std::endl;
    std::cout << "radius: " << c.rad << std::endl;
}

float circleLen(Circle c){
    return c.rad * 2 * M_PI;
}

float circleAr(Circle c){
    return c.rad * c.rad * M_PI;
}

void setSquare(Square* s, Dot upLeft, float l){
    s->upLeft = upLeft;
    s->len = l;
}

void squareInfo(Square s){
    std::cout << "upper left x: " << s.upLeft.x << std::endl;
    std::cout << "upper left y: " << s.upLeft.y << std::endl;
    std::cout << "length: " << s.len << std::endl;
}

float squarePer(Square s){
    return s.len * 4;
}

float squareAr(Square s){
    return s.len * s.len;
}

bool inCircle(Dot d, Circle s){
    return pow(d.x - s.center.x, 2) + pow(d.y - s.center.y, 2) <= pow(s.rad, 2);
}

bool inSquare(Dot d, Square s){
    return s.upLeft.x < d.x && d.x < (s.upLeft.x + s.len) && (s.upLeft.y - s.len) < d.y && d.y < s.upLeft.y;
}

bool onCircle(Dot d, Circle s){
    return pow(d.x - s.center.x, 2) + pow(d.y - s.center.y, 2) == pow(s.rad, 2);
}

bool onSquare(Dot d, Square s){
    if(d.y == s.upLeft.y || d.y == (s.upLeft.y - s.len)){
        return (s.upLeft.x <= d.x && d.x <= (s.upLeft.x + s.len));
    }
    if(d.x == s.upLeft.x || d.x == (s.upLeft.x + s.len)){
        return ((s.upLeft.y - s.len) <= d.y && d.y <= s.upLeft.y);
    }
    return 0;
}

bool circlesInter(Circle a, Circle b){
    float dist = sqrt(pow(a.center.x - b.center.x, 2) + pow(a.center.y - b.center.y, 2));
    return dist <= (a.rad + b.rad);
}

bool squaresInter(Square a, Square b){
    Dot upLeft;
    upLeft = a.upLeft;

    Dot loLeft;
    loLeft.x = a.upLeft.x;
    loLeft.y = a.upLeft.y - a.len;

    Dot loRight;
    loRight.x = a.upLeft.x + a.len;
    loRight.y = a.upLeft.y - a.len;

    Dot upRight;
    upRight.x = a.upLeft.x + a.len;
    upRight.y = a.upLeft.y;

    if(!square_in_square(a, b)){
        return (inSquare(upLeft, b) + inSquare(loLeft, b) + inSquare(loRight, b) + inSquare(upRight, b) + onSquare(upLeft, b) + onSquare(loLeft, b) + onSquare(loRight, b) + onSquare(upRight, b));
    }
    else{
        return 0;
    }
    
}

bool difInter(Circle c, Square s){
    float x_min = s.upLeft.x;
    float x_max = s.upLeft.x + s.len;
    float y_min = s.upLeft.y - s.len;
    float y_max = s.upLeft.y;

    if (inSquare(c.center, s)){
        float dis_side = std::min(std::min(c.center.x - x_min, x_max - c.center.x), std::min(y_max - c.center.y, c.center.y - y_min));

        Dot upLeft;
        upLeft = s.upLeft;

        Dot loLeft;
        loLeft.x = s.upLeft.x;
        loLeft.y = s.upLeft.y - s.len;

        Dot loRight;
        loRight.x = s.upLeft.x + s.len;
        loRight.y = s.upLeft.y - s.len;

        Dot upRight;
        upRight.x = s.upLeft.x + s.len;
        upRight.y = s.upLeft.y;

        float dis_vert = std::max(std::max((sqrt(pow(c.center.x - upLeft.x, 2) + pow(c.center.y - upLeft.y, 2))), sqrt(pow(c.center.x - loLeft.x, 2) + pow(c.center.y - loLeft.y, 2))), std::max(sqrt(pow(c.center.x - loRight.x, 2) + pow(c.center.y - loRight.y, 2)), sqrt(pow(c.center.x - upRight.x, 2) + pow(c.center.y - upRight.y, 2))));
        
        return (c.rad >= dis_side && c.rad <= dis_vert);
    }
    else{
        float x_near = std::max(x_min, std::min(c.center.x, x_max));
        float y_near = std::max(y_min, std::min(c.center.y, y_max));

        float dis = sqrt(pow(x_near - c.center.x, 2) + pow(y_near - c.center.y, 2));
        return dis <= c.rad;
    
    }
    
}

bool circle_in_circle(Circle c1, Circle c2){
    float dis = sqrt(pow(c1.center.x - c2.center.x, 2) + pow(c1.center.y - c2.center.y, 2));
    return dis + c1.rad <= c2.rad;
}

bool square_in_square(Square s1, Square s2){
    Dot upLeft;
    upLeft = s1.upLeft;

    Dot loLeft;
    loLeft.x = s1.upLeft.x;
    loLeft.y = s1.upLeft.y - s1.len;

    Dot loRight;
    loRight.x = s1.upLeft.x + s1.len;
    loRight.y = s1.upLeft.y - s1.len;

    Dot upRight;
    upRight.x = s1.upLeft.x + s1.len;
    upRight.y = s1.upLeft.y;

    return (inSquare(upLeft, s2) * inSquare(loLeft, s2) * inSquare(loRight, s2) * inSquare(upRight, s2));
}

bool square_in_circle(Square s, Circle c){
    Dot upLeft;
    upLeft = s.upLeft;

    Dot loLeft;
    loLeft.x = s.upLeft.x;
    loLeft.y = s.upLeft.y - s.len;

    Dot loRight;
    loRight.x = s.upLeft.x + s.len;
    loRight.y = s.upLeft.y - s.len;

    Dot upRight;
    upRight.x = s.upLeft.x + s.len;
    upRight.y = s.upLeft.y;

    return (inCircle(upLeft, c) * inCircle(loLeft, c) * inCircle(loRight, c) * inCircle(upRight, c));
}

bool circle_in_square(Circle c, Square s){
    Dot loRight;
    loRight.x = s.upLeft.x + s.len;
    loRight.y = s.upLeft.y - s.len;

    return (((c.center.x - s.upLeft.x) >= c.rad) * ((s.upLeft.y - c.center.y) >= c.rad) * ((loRight.x - c.center.x) >= c.rad) * ((c.center.y - loRight.y) >= c.rad));
}