#include "Weather_Information.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::vector<Day*>& Weather_Information::GetWeather(const std::string& city_name, int days_count) {
    auto response_city_information = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                             cpr::Header{{"X-Api-Key", "5TtRhFUF5J7BVF1gAFc9dP2dIWUAoduDQjF5awAw"}},
                             cpr::Parameters{{"name", city_name}});

    if(response_city_information.status_code == 0){
        throw std::runtime_error(response_city_information.error.message);
    }

    json city = json::parse(response_city_information.text.substr(1, response_city_information.text.size() - 2));

    std::string latitude = to_string(city.at("latitude"));
    std::string longitude = to_string(city.at("longitude"));


    auto response_weather_information = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                                 cpr::Header{{"X-Api-Key", "5TtRhFUF5J7BVF1gAFc9dP2dIWUAoduDQjF5awAw"}},
                                                 cpr::Parameters{{"latitude", latitude}, {"longitude", longitude},
                                                                 {"forecast_days", std::to_string(days_count)},
                                                                 {"hourly", "weathercode"},
                                                                 {"hourly", "temperature_2m"},
                                                                 {"hourly", "relativehumidity_2m"},
                                                                 {"hourly", "windspeed_10m"},
                                                                 {"hourly", "winddirection_10m"},
                                                                 {"daily", "temperature_2m_max"},
                                                                 {"timezone", "GMT"},
                                                                 {"hourly", "visibility"}});

    if(response_weather_information.status_code == 0){
        throw std::runtime_error(response_weather_information.error.message);
    }

    json weather_information = json::parse(response_weather_information.text);

    for(auto i : information){
        delete i;
    }

    for(int i = 0; i < days_count; i++) {
        Day* new_day = new Day();

        new_day->city = city_name;
        new_day->day = weather_information.at("daily").at("time")[i];

        new_day->weather_code[0] = weather_information.at("hourly").at("weathercode")[9 + i * 24];
        new_day->weather_code[1] = weather_information.at("hourly").at("weathercode")[13 + i * 24];
        new_day->weather_code[2] = weather_information.at("hourly").at("weathercode")[19 + i * 24];
        new_day->weather_code[3] = weather_information.at("hourly").at("weathercode")[23 + i * 24];
        new_day->visibility[0] = weather_information.at("hourly").at("visibility")[9 + i * 24];
        new_day->visibility[1] = weather_information.at("hourly").at("visibility")[13 + i * 24];
        new_day->visibility[2] = weather_information.at("hourly").at("visibility")[19 + i * 24];
        new_day->visibility[3] = weather_information.at("hourly").at("visibility")[23 + i * 24];

        int humidinity_;
        int wind_speed_;
        int wind_direction_;

        int j = 0;

        for(int k = 0 ; k < 4; ++k) {
            for(j; j < 6 * (k + 1); j++) {
                if(weather_information.at("hourly").at("temperature_2m")[j] < new_day->min_temperature[k]) {
                    new_day->min_temperature[k] = weather_information.at("hourly").at("temperature_2m")[j  + i * 24];
                }
                if(weather_information.at("hourly").at("temperature_2m")[j] > new_day->max_temperature[k]){
                    new_day->max_temperature[k] = weather_information.at("hourly").at("temperature_2m")[j + i * 24];
                }
                humidinity_ = weather_information.at("hourly").at("relativehumidity_2m")[j + i * 24];
                wind_speed_ = weather_information.at("hourly").at("windspeed_10m")[j + i * 24];
                wind_direction_ = weather_information.at("hourly").at("winddirection_10m")[j + i * 24];
                new_day->humidinity[k] += humidinity_;
                new_day->wind_direction[k] += wind_direction_;
                new_day->wind_speed[k] += wind_speed_;
            }
            new_day->humidinity[k] /= 6;
            new_day->wind_speed[k] /= 6;
            new_day->wind_direction[k] /= 6;
        }

        information.push_back(new_day);
    }

    return information;
}


