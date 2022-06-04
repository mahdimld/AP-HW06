#ifndef Q3_H
#define Q3_H

#include <queue>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration{};
        size_t connections{};
        size_t connection_times{};
        size_t price{};
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

    inline auto comp = [](const Flight &a, const Flight &b) {
        return a.duration + a.connection_times + 3 * a.price > b.duration + b.connection_times + 3 * b.price;
    };

    inline std::priority_queue<Flight, std::vector<Flight>, decltype(comp)> gather_flights(const std::string &filename) {

        std::fstream stream("../resources/" + filename);
        std::string line;

        std::priority_queue<Flight, std::vector<Flight>, decltype(comp)> flights(comp);
        std::vector<std::string> tokens;
        while (stream >> line) {
            if (tokens.size() == 6)
                tokens.clear();
            std::string token{};
            size_t ch{};
            while (ch < line.size()) {
                if (line[ch] == '-') {
                    if (!trim(token).empty())
                        tokens.push_back(trim(token));
                    token = "";
                } else {
                    token += line[ch];
                }
                ch++;
            }
            if (!trim(token).empty())
                tokens.push_back(trim(token));
            if (tokens.size() < 6)
                continue;

            size_t part{};
            while (part < tokens.size()) {
                std::string str{};
                size_t time{};
                size_t ch_in_part{tokens[part].find(':') + 1};
                while (ch_in_part < tokens[part].size()) {
                    if (tokens[part][ch_in_part] == 'h') {
                        time += 60 * std::stoi(str);
                        str = {};
                    } else if (tokens[part][ch_in_part] == 'm') {
                        time += std::stoi(str);
                        str = {};
                    } else if (tokens[part][ch_in_part] == ',') {
                        str = {};
                    } else
                        str += tokens[part][ch_in_part];
                    ch_in_part++;
                }
                if (str.empty())
                    tokens[part] = std::to_string(time);
                else
                    tokens[part] = str;
                part++;
            }

            auto flight = Flight{
                    .flight_number = tokens[1],
                    .duration = static_cast<size_t>(std::stoi(tokens[2])),
                    .connections = static_cast<size_t>(std::stoi(tokens[3])),
                    .connection_times = static_cast<size_t>(std::stoi(tokens[4])),
                    .price = static_cast<size_t>(std::stoi(tokens[5])),
            };
            flights.push(flight);
        }
        return flights;
    }
}

#endif //Q3_H