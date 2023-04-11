#include "visualisation.h"
#include "constants.h"

using namespace ftxui;


Element visualisation::cell_construct(int weather_code, int visibility, int min_temperature, int max_temperature, int humidinity, int wind_speed, int winddirection) {

    std::vector<Element> weather_symb;
    std::vector<Element> weather_information;

    for(auto i : WEATHER_SYMBOL_WEGO.at(weather_code)){
        weather_symb.push_back(hbox({center(text(i))}));
    }

    weather_information.push_back(text(WMO_CODE.at(weather_code)));
    weather_information.push_back(text(std::to_string(min_temperature) + " - " + std::to_string(max_temperature) + " °C"));
    weather_information.push_back(text(std::to_string(humidinity) + " %"));
    weather_information.push_back(text(wind_direction[winddirection / 90] + " " + std::to_string(wind_speed) + " km/h"));
    weather_information.push_back(text(std::to_string(visibility / 1000) + " km"));

    auto cell = hbox({ vbox({weather_symb}), separator(), vbox({weather_information}) });
    return cell;
}

void visualisation::ConsoleRefresh(const std::string& city_name, int days_count) {
    system("cls");

    Weather_Information weatherInformation;

    std::vector<Day*> information = weatherInformation.GetWeather(city_name, days_count);

    std::vector<Elements> lines;
    lines.push_back({text(information[0]->city)});
    for(int i = 0; i < days_count; i++) {

        lines.push_back({
                                gridbox({
                                                {
                                                        window(center(text(information[i]->day)), hbox({
                                                        window(center(text("Morning")), cell_construct(information[i]->weather_code[0], information[i]->visibility[0], information[i]->min_temperature[0], information[i]->max_temperature[0], information[i]->humidinity[0], information[i]->wind_speed[0], information[i]->wind_direction[0])),
                                                        window(center(text("Day")), cell_construct(information[i]->weather_code[1], information[i]->visibility[1], information[i]->min_temperature[1], information[i]->max_temperature[1], information[i]->humidinity[1], information[i]->wind_speed[1], information[i]->wind_direction[1])),
                                                        window(center(text("Evening")), cell_construct(information[i]->weather_code[2], information[i]->visibility[2], information[i]->min_temperature[2], information[i]->max_temperature[2], information[i]->humidinity[2], information[i]->wind_speed[2], information[i]->wind_direction[2])),
                                                        window(center(text("Night")), cell_construct(information[i]->weather_code[3], information[i]->visibility[3], information[i]->min_temperature[3], information[i]->max_temperature[3], information[i]->humidinity[3], information[i]->wind_speed[3], information[i]->wind_direction[3])) }))
                                                }
                                        })
                        });
    }
    auto document =  gridbox(lines);
    auto screen = Screen::Create(Dimension::Fit(document));
    Render(screen, document);
    screen.Print();

}
