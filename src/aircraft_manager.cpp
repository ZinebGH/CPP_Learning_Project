#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

void AircraftManager::print_aircrafts()
{
    std::for_each(aircrafts.begin(), aircrafts.end(),
                  [](auto& a1)
                  {
                      std::cout << a1->get_flight_num() << " has terminal " << a1->has_terminal()
                                << "level fuel : " << a1->level_of_fuel() << std::endl;
                  });
}

bool AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](auto& a1, auto& a2)
              {
                  if ((!a1->has_terminal() && !a2->has_terminal()) ||
                      (a1->has_terminal() && a2->has_terminal()))
                  {
                      return a1->level_of_fuel() > a2->level_of_fuel();
                  }
                  else if ((a1->has_terminal() && !a2->has_terminal()))
                  {
                      return true;
                  }

                  else
                  {
                      return false;
                  }
              });

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [this](auto& aircraft)
                                   {
                                       try
                                       {
                                           return !aircraft->move();
                                       } catch (AircraftCrash& e)
                                       {
                                           crash_count++;
                                           std::cerr << e.what() << std::endl;
                                           return true;
                                       }
                                   }),
                    aircrafts.end());
    return true;
}

void AircraftManager::aircraft_by_index(const std::string& airline)
{
    const auto cnt = std::count_if(aircrafts.begin(), aircrafts.end(),
                                   [airline](const auto& aircraft)
                                   { return aircraft->get_flight_num().substr(0, 2).compare(airline) == 0; });
    std::cout << "number of " << airline << ": " << cnt << std::endl;
}

int AircraftManager::get_required_fuel()
{
    int i = 0;
    std::for_each(aircrafts.begin(), aircrafts.end(),
                  [&i](auto& a)
                  {
                      if (a->in_terminal() && a->is_low_on_fuel())
                      {
                          i += (MAX_FUEL - a->level_of_fuel());
                      }
                  });
    return i;
}
