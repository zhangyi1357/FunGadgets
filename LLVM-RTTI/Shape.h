#ifndef SHAPE_H
#define SHAPE_H

class Shape {
  public:
    /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
    enum ShapeKind {
        SK_Square,
        SK_SpecialSquare,
        SK_OtherSpecialSquare,
        SK_SomeWhatSpecialSquare,
        SK_LastSuqare,
        SK_Circle,
    };

  private:
    const ShapeKind Kind;

  public:
    ShapeKind getKind() const { return Kind; }

  public:
    Shape(ShapeKind K) : Kind(K) {}
    virtual double computeArea() = 0;
};

class Square : public Shape {
    double SideLength;

  public:
    Square(double S) : Shape(SK_Square), SideLength(S) {}
    double computeArea() override { return SideLength * SideLength; }

    static bool classof(const Shape *S) {
        return S->getKind() >= SK_Square && S->getKind() <= SK_LastSuqare;
    }
};

class Circle : public Shape {
    double Radius;

  public:
    Circle(double R) : Shape(SK_Circle), Radius(R) {}
    double computeArea() override { return 3.14 * Radius * Radius; }

    static bool classof(const Shape *S) { return S->getKind() == SK_Circle; }
};

class SpecialSquare : public Square {};
class OtherSpecialSquare : public Square {};
class SomeWhatSpecialSquare : public Square {};

#endif // SHAPE_H
