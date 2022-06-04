#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <regex>
#include <iostream>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age{};
        size_t smokes{};
        size_t area_q{};
        size_t alkhol{};
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


    inline std::vector<Patient> read_file(const std::string &filename) {

        std::fstream stream("../resources/" + filename);
        std::string line;
        stream >> line >> line;
        std::vector<std::string> elements;
        std::vector<Patient> patients;
        
        while (stream >> line) {
            if (elements.size() == 6)
                elements.clear();
            std::string element{};
            for (auto data: line) {
                if (data == ',') {
                    if (!trim(element).empty()){
                        elements.push_back(trim(element));
                    }
                    element = "";
                } 
                else {
                    element += data;
                }
            }
            if (!trim(element).empty()){
                elements.push_back(trim(element));
            }
            if (elements.size() < 6){
                continue;
            }
            Patient pat = {
                    elements[0] + " " + elements[1],
                    static_cast<size_t>(std::stoi(elements[2])),
                    static_cast<size_t>(std::stoi(elements[3])),
                    static_cast<size_t>(std::stoi(elements[4])),
                    static_cast<size_t>(std::stoi(elements[5])),
            };
            patients.push_back(pat);
        }

        return patients;
    }

    inline void sort(std::vector<Patient> &pat) {
        std::ranges::sort(pat, std::greater<>{},
                          [](const Patient &person) {
                              return (3 * person.age + 5 * person.smokes + 2 * person.area_q + 4 * person.alkhol);
                          });
    }
}
#endif //Q2_H