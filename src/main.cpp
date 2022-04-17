#include "point.hpp"
#include "tower_sim.hpp"

#include <iostream>

void test_generic_points()
{
    auto p1 = Point<2, int>(2, 3);
    auto p2 = Point<2, int>(1, 23);
    auto p3 = p1 + p2;
    auto p4 = Point<3, int>(2, 3, 4);
    auto p5 = Point<3, int>(1, 23, 2);
    auto p6 = p4 + p5;

    std::cout << p6.x() << " " << p6.y() << " " << p6.z() << std::endl;

    std::cout << p3.x() << " " << p3.y() << std::endl;

    p3 -= p2;

    std::cout << p3.x() << " " << p3.y() << std::endl;

    p1 *= 3;

    std::cout << p1.x() << " " << p1.y() << std::endl;
}

int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };
    test_generic_points();
    simulation.launch();
    return 0;
}