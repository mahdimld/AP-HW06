#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <regex>
#include <iostream>
// #include <string>
//#include <vector>
//#include <algorithm>
//#include <functional>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age{};
        size_t smokes{};
        size_t area_q{};
        size_t alkhol{};
    };

    inline std::string ltrim(const std::string &s) {
        return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
    }

    inline std::string rtrim(const std::string &s) {
        return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
    }

    inline std::string trim(const std::string &s) {
        return ltrim(rtrim(s));
    }

    inline std::vector<Patient> read_file(const std::string &filename) {

        std::fstream stream("../resources/" + filename);
        std::string line;
        stream >> line;
        stream >> line;

        std::vector<Patient> patients;
        std::vector<std::string> tokens;
        while (stream >> line) {
            if (tokens.size() == 6)
                tokens.clear();
            std::string token{};
            for (auto ch: line) {
                if (ch == ',') {
                    if (!trim(token).empty())
                        tokens.push_back(trim(token));
                    token = "";
                } else {
                    token += ch;
                }
            }
            if (!trim(token).empty())
                tokens.push_back(trim(token));
            if (tokens.size() < 6)
                continue;
            auto patient = Patient{
                    .name =  tokens[0] + " " + tokens[1],
                    .age = static_cast<size_t>(std::stoi(tokens[2])),
                    .smokes = static_cast<size_t>(std::stoi(tokens[3])),
                    .area_q = static_cast<size_t>(std::stoi(tokens[4])),
                    .alkhol = static_cast<size_t>(std::stoi(tokens[5])),
            };
            patients.push_back(patient);
        }

        return patients;
    }

    inline void sort(std::vector<Patient> &patient) {
        std::ranges::sort(patient, std::greater<>{},
                          [](const Patient &a) {
                              return (3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol);
                          });
    }
}
#endif //Q2_H