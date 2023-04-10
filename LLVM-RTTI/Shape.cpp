

#include "Shape.h"
#include "SimpleCasting.h"

#include <iostream>

int main() {
    Shape *pShape = new Square(2);
    if (isa<Square>(pShape)) {
        std::cout << "S is Square with area = " << pShape->computeArea()
                  << std::endl;
    }
    if (Square *pSquare = cast<Square>(pShape)) {
        std::cout << "cast succeed, S is Square with area = "
                  << pSquare->computeArea() << std::endl;
    }
    if (Circle *Cir = dyn_cast<Circle>(pShape)) {
        std::cout << "This won't happen" << std::endl;
    }
    delete cast<Square>(pShape);

    pShape = new Circle(2);
    if (isa<Square>(pShape)) {
        std::cout << "This won't happen" << std::endl;
    }
    if (Circle *Cir = dyn_cast<Circle>(pShape)) {
        std::cout << "Cir is Circle with area = " << Cir->computeArea()
                  << std::endl;
    }
    if (Square *pSquare = cast<Square>(pShape)) {
        std::cout << "Assertion will fail" << std::endl;
    }
}