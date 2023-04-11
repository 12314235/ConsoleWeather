#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../wether/Weather_Information.h"

#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"

using namespace ftxui;

class visualisation {
private:
     Element cell_construct(int weather_code, int visibility, int min_temperature, int max_temperature, int humidinity, int wind_speed, int wind_direction);
public:
    void ConsoleRefresh(const std::string& city_name, int days_count);
};
