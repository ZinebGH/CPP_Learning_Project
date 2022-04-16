#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

    void print_aircrafts();

    int crash_count = 0;

public:
    AircraftManager() = default;

    void add(std::unique_ptr<Aircraft> aircraft);

    bool move() override;

    void aircraft_by_index(const std::string& airline);

    int get_required_fuel();

    void number_of_crash() { std::cout << "Number crashed : " << crash_count << std::endl; }

    friend class Airport;
};
