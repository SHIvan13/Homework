#pragma once


struct Dot{
    float x;
    float y;
};

struct Circle{
    Dot center;
    float rad;
};

struct Square{
    Dot upLeft;
    float len;
};