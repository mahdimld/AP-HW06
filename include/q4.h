#ifndef Q4_H
#define Q4_H

#include <functional>
#include <numeric>

namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
    };

    struct Sensor {
        Vector2D pos;
        double accuracy{};
    };
        
        
    inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
        double accumulate_accuaracies{};
        double approximation_of_x{};
        double approximation_of_y{};
        Sensor sns{std::accumulate(sensors.begin(), sensors.end(), Sensor{{0, 0}, 0},
                        [&accumulate_accuaracies](const Sensor &first, const Sensor &second) -> Sensor {
                            accumulate_accuaracies += first.accuracy + second.accuracy;
                            return {accumulate_accuaracies};
                        })};

        
        
        Sensor kalman{std::accumulate(sensors.begin(), sensors.end(), Sensor{{0, 0}, 0},
                                 [accumulate_accuaracies, &approximation_of_x, &approximation_of_y](const Sensor &first, const Sensor &second) -> Sensor {
                                     approximation_of_x += second.pos.x * (second.accuracy / accumulate_accuaracies);
                                     approximation_of_y += second.pos.y * (second.accuracy / accumulate_accuaracies);
                                     return {{approximation_of_x, approximation_of_y}};
                                 })};

        return kalman.pos;
    }
}


#endif //Q4_H