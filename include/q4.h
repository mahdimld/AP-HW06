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
        double accuracy_sum{};
        std::accumulate(sensors.begin(), sensors.end(), Sensor{{0, 0}, 0},
                        [&accuracy_sum](const Sensor &a, const Sensor &b) -> Sensor {
                            accuracy_sum += b.accuracy;
                            return {};
                        });

        Sensor kalman;
        double x_estimate{};
        double y_estimate{};
        kalman = std::accumulate(sensors.begin(), sensors.end(), Sensor{{0, 0}, 0},
                                 [accuracy_sum, &x_estimate, &y_estimate](const Sensor &a, const Sensor &b) -> Sensor {
                                     x_estimate += b.pos.x * (b.accuracy / accuracy_sum);
                                     y_estimate += b.pos.y * (b.accuracy / accuracy_sum);
                                     return {{x_estimate, y_estimate}};
                                 });

        return kalman.pos;
    }
}


#endif //Q4_H