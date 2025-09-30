#include "func.h"
#include <iostream>

int main(){
    // вспомогательные точки
    Dot a;
    a.x = 1;
    a.y = 4;

    Dot b;
    b.x = 2;
    b.y = 3;

    Dot c;
    c.x = 0;
    c.y = -4;

    Dot d;
    d.x = 0;
    d.y = 0;

    // Задание круга и связаные функции
    Circle* circ1 = new Circle;
    setCircle(circ1, a, 3);
    circleInfo(*circ1);
    std::cout << circleLen(*circ1) << std::endl << circleAr(*circ1) << std::endl;
    
    // Задание квадрата и связаные функции
    Square* sq1 = new Square;
    setSquare(sq1, b, 5);
    squareInfo(*sq1);
    std::cout << squarePer(*sq1) << std::endl << squareAr(*sq1) << std::endl;

    // Точка в круге/квадрате
    if(inCircle(c, *circ1)){
        std::cout << "Точка в круге." << std::endl;
    }
    else{
        std::cout << "Точка не в круге." << std::endl;
    }
    if(inSquare(c, *sq1)){
        std::cout << "Точка в квадрате." << std::endl;
    }
    else{
        std::cout << "Точка не в квадрате." << std::endl;
    }

    // Точка на контуре круга/квадрата
    if(onCircle(c, *circ1)){
        std::cout << "Точка на контуре круга." << std::endl;
    }
    else{
        std::cout << "Точка вне контура круга." << std::endl;
    }
    if(onSquare(c, *sq1)){
        std::cout << "Точка на контуре квадрата." << std::endl;
    }
    else{
        std::cout << "Точка вне контура квадрата." << std::endl;
    }

    // Пересечение кругов
    Circle* circ2 = new Circle;
    setCircle(circ2, b, 2);

    if(circlesInter(*circ1, *circ2)){
        std::cout << "Круги пересекаются." << std::endl;
    }
    else{
        std::cout << "Круги не пересекаются." << std::endl;
    }

    // Пересечение квадратов
    Square* sq2 = new Square;
    setSquare(sq2, c, 3);

    if(squaresInter(*sq1, *sq2)){
        std::cout << "Квадраты пересекаются." << std::endl;
    }
    else{
        std::cout << "Квадраты не пересекаются." << std::endl;
    }

    // Пересечение круга и квадрата
    if(difInter(*circ1, *sq1)){
        std::cout << "Фигуры пересекаются." << std::endl;
    }
    else{
        std::cout << "Фигуры не пересекаются." << std::endl;
    }

    // Круг в круге
    if(circle_in_circle(*circ1, *circ2)){
        std::cout << "Круг принадлежит кругу." << std::endl;
    }
    else{
        std::cout << "Круг не принадлежит кругу" << std::endl;
    }

    // Квадрат в квадрате
    if(square_in_square(*sq1, *sq2)){
        std::cout << "Квадрат принадлежит квадрату." << std::endl;
    }
    else{
        std::cout << "Квадрат не принадлежит квадрату" << std::endl;
    }

    // Квадрат в круге
    if(square_in_circle(*sq1, *circ1)){
        std::cout << "Квадрат принадлежит кругу." << std::endl;
    }
    else{
        std::cout << "Квадрат не принадлежит кругу" << std::endl;
    }

    // Круг в квадрате
    if(circle_in_square(*circ2, *sq2)){
        std::cout << "Круг принадлежит квадрату." << std::endl;
    }
    else{
        std::cout << "Круг не принадлежит квадрату." << std::endl;
    }
}