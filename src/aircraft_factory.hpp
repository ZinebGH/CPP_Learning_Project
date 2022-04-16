#pragma once

#include "GL/texture.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "airport_type.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

public:
    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport) const
    {
        assert(airport); // make sure the airport is initialized before creating aircraft
        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        // Pour gérer les aircrafts on passe par des unique_ptr.
        return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
    }

    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport) const
    {
        return create_aircraft(*(aircraft_types[rand() % 3]), airport);
    }

    std::string airline(int index)
    {
        assert(index > 0 && index < 8);
        return airlines[index];
    }

    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    void init_aircraft_types()
    {
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, 2, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, 1, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .08f, .03f, 3, MediaPath { "concorde_af.png" } };
    }
};