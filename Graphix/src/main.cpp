#include <iostream>
#include "Vector.h"
#include "Operations.h"

using namespace gpx;

int main(void)
{
    Vector a(2, 2.1, 4.4); Vector b(1, 2, 5.5);
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << "a + b: " << a + b << std::endl;
    std::cout << "a - b: " << a - b << std::endl;
    std::cout << "-a: " << -a << std::endl;
    std::cout << "2 * a: " << 2 * a << std::endl;
    std::cout << "a * 2: " << a * 2 << std::endl;

    std::cout << std::endl;

    std::cout << "Dot(a,b): " << Dot(a, b) << std::endl;
    std::cout << "Cross(a,b): " << Cross(a, b) << std::endl;

    std::cout << std::endl;

    std::cout << "Mag a: " << Magnitude(a) << std::endl;
    std::cout << "Normalized: " << Normalize(a) << std::endl;

    std::cout << std::endl;

    system("pause");
    return 0;
}