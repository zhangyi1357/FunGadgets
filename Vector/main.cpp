#include <iostream>

#include "Vector.h"

template<typename T>
void PrintVector(const Vector<T>& vector) {
    for (size_t i = 0; i < vector.Size(); ++i)
        std::cout << vector[i] << std::endl;

    std::cout << "---------------------------" << std::endl;
}

class Vector3 {
public:
    Vector3() {}
    Vector3(float scalar)
        : x(scalar), y(scalar), z(scalar) {}
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {}

    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "Copy" << std::endl;
    }
    Vector3(const Vector3&& other)
        : x(other.x), y(other.y), z(other.z) {
        std::cout << "Move" << std::endl;
    }
    ~Vector3() {
        std::cout << "Destroy" << std::endl;
    }

    Vector3& operator=(const Vector3& other) {
        std::cout << "Copy" << std::endl;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Vector3& operator=(Vector3&& other) {
        std::cout << "Move" << std::endl;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream&, const Vector3&);
private:
    float x = 0.0f, y = 0.0f, z = 0.0f;
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << vec.x << ", " << vec.y << ", " << vec.z;
    return os;
}


int main() {
    Vector<Vector3> vec;
    vec.EmplaceBack();
    vec.EmplaceBack(1.0f);
    vec.EmplaceBack(1.0f, 2.0f, 3.0f);
    PrintVector(vec);

    return 0;
}