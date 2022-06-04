#ifndef Q3_H
#define Q3_H

#include <queue>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration{};
        size_t connections{};
        size_t connection_minutess{};
        size_t price{};
    };

    inline auto cmp_func = [](const Flight &f1, const Flight &f2) {
        return f1.duration + f1.connection_minutess + 3 * f1.price > f2.duration + f2.connection_minutess + 3 * f2.price;
    };
    inline std::string left_trim(const std::string &str) {
        return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
    }
    inline std::string right_trim(const std::string &str) {
        return std::regex_replace(str, std::regex("\\s+$"), std::string(""));
    }
    inline std::string trim(const std::string &str) {
        return left_trim(right_trim(str));
    }


    inline std::priority_queue<Flight, std::vector<Flight>, decltype(cmp_func)> gather_flights(const std::string &filename) {

        std::fstream stream("../resources/" + filename);
        std::string line;
        
        std::vector<std::string> elements;
        std::priority_queue<Flight, std::vector<Flight>, decltype(cmp_func)> flights(cmp_func);
        while (stream >> line) {
            if (elements.size() == 6){
                elements.clear();
            }
            std::string element{};
            size_t data{};
            while (data < line.size()) {
                if (line[data] == '-') {
                    if (!trim(element).empty()){
                        elements.push_back(trim(element));
                    }
                    element = "";
                }
                 else {
                    element += line[data];
                }
                data++;
            }
            if (!trim(element).empty()){
                elements.push_back(trim(element));
            }
            if (elements.size() < 6){
                continue;
            }

            size_t sect{};
            while (sect < elements.size()) {
                size_t minutes{};
                std::string str{};
                size_t letter{elements[sect].find(':') + 1};
                while (letter < elements[sect].size()) {
                    if (elements[sect][letter] == 'h') {
                        minutes += 60 * std::stoi(str);
                        str = {};
                    } 
                    else if (elements[sect][letter] == 'm') {
                        minutes += std::stoi(str);
                        str = {};
                    }
                     else if (elements[sect][letter] == ',') {
                        str = {};
                    }
                     else{
                        str += elements[sect][letter];
                     }
                    letter++;
                }
                if (str.empty()){
                    elements[sect] = std::to_string(minutes);
                }
                else{
                    elements[sect] = str;
                }
                sect++;
            }
        
            Flight flight = {
                    elements[1],
                    static_cast<size_t>(std::stoi(elements[2])),
                    static_cast<size_t>(std::stoi(elements[3])),
                    static_cast<size_t>(std::stoi(elements[4])),
                    static_cast<size_t>(std::stoi(elements[5])),
            };
            flights.push(flight);
        }

        return flights;
    }

}


#endif //Q3_H