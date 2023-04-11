#include <string>
#include <cpr/cpr.h>
#include <vector>

struct Day{
    std::string city;
    std::string day;
    int* weather_code = new int[4];
    double* min_temperature = new double[4];
    double* max_temperature = new double[4];
    int* humidinity = new int[4];
    double* wind_speed = new double[4];
    int* wind_direction = new int[4];
    int* visibility = new int[4];

    Day() {
        for(int i = 0; i < 4; i++){
            visibility[i] = 0;
            min_temperature[i] = 100;
            max_temperature[i] = -100;
            humidinity[i] = 0;
            wind_speed[i] = 0;
            wind_direction[i] = 0;
        }
    }

    ~Day(){
        delete[] weather_code;
        delete[] min_temperature;
        delete[] max_temperature;
        delete[] humidinity;
        delete[] wind_speed;
        delete[] wind_direction;
        delete[] visibility;
    }

    Day(const Day& other) = default;
};


class Weather_Information {
public:
    std::vector<Day*> information;
    const std::vector<Day*>& GetWeather(const std::string& city_name, int days_count);
};