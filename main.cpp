#include <iostream>
#include "Vector.h"
#include <vector>

class Vertex
{
public:

    float x = 0, y = 0, z = 0;
    int* Data;

    Vertex()
    {
        Data = new int(0);
        printf("default!\n");
    }

    Vertex(float _x, float _y, float _z, int _data)
            : x(_x), y(_y), z(_z)
    {
        Data = new int(_data);
        printf("Created!\n");
    }

    Vertex(const Vertex& other)
            : x(other.x), y(other.y), z(other.z)
    {
        Data = new int(*other.Data);
        printf("copy constructor\n");
    }

    Vertex(Vertex&& other)
            : x(other.x), y(other.y), z(other.z)
    {
        Data = other.Data;
        printf("move constructor\n");
    }

    Vertex& operator=(const Vertex& other)
    {
        *Data = *other.Data;
        x = other.x;
        y = other.y;
        z = other.z;
        std::cout << "Copied!\n";
        return *this;
    }

    Vertex& operator=(Vertex&& other)
    {
        Data = other.Data;
        x = other.x;
        y = other.y;
        z = other.z;
        std::cout << "Moved!\n";
        return *this;
    }

    bool operator==(const Vertex& other) const
    {
        return (x == other.x && y == other.y && z == other.z && *Data == *other.Data);
    }

    bool operator!=(const Vertex& other) const
    {
        return (x != other.x || y != other.y || z != other.z || *Data != *other.Data);
    }

    ~Vertex()
    {
        delete Data;
    }
};

std::ostream& operator<<(std::ostream& out, const Vertex& vertex)
{
    out << vertex.x << " " << vertex.y << " " << vertex.z << " " << *vertex.Data << "\n";

    return out;
}

int main()
{

    Vector<Vertex> vec;
    vec.reserve(3);

    vec.emplace_back(1, 2, 3, 4);
    vec.emplace_back(1, 2, 3, 4);
    vec.emplace_back(1, 2, 3, 4);
    vec.emplace_back(1, 2, 3, 4);
    vec.emplace_back(1, 2, 3, 4);
    vec.print();
    vec.popBack();
    vec.popBack();
    vec.popBack();
    vec.popBack();
    vec.popBack();
    vec.emplace_back(1, 2, 3, 5);
    vec.print();


    return 0;
}
