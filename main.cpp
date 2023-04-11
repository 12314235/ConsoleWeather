#include <nlohmann/json.hpp>
#include "visualisation/visualisation.h"
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

using json = nlohmann::json;
using namespace ftxui;

int main() {
    std::ifstream config_json;
    config_json.open("D:\\labwork10\\config.json");
    json config = json::parse(config_json);

    visualisation console;

    int days_count = config.at("days_count");
    int city_index;

    char command = '\0';

    while(command != 'q') {
        switch(command){
            case 'm':
                if(days_count < 16) {
                    days_count++;
                }
                break;
            case 'l':
                if(days_count > 0) {
                    days_count--;
                }
                break;
            case 'n':
                if(city_index > 0) {
                    city_index--;
                }
                break;
            case 'p':
                if(city_index + 1 < config.at("cities_count")) {
                    city_index++;
                }
                break;
            default:
                break;
        }
        console.ConsoleRefresh(config.at("cities")[city_index], days_count);
        command = getchar();
    }

    return 0;
}
