#ifndef Q1_H
#define Q1_H

#include <iostream>
#include <cmath>
#include <functional>

namespace q1 {
    template<typename T = double, typename F = std::function<T(T)>>
    inline T gradient_descent(T init_val, T step_size, F objectFnc = F()) {
        int maxIterations{500};
        T gradientThresh{step_size / 100};
        int iterCount{0};
        T gradientMagnitude = 1.0;
        T currentPoint{init_val};
        T nextPoint{currentPoint + step_size};
        int direction{objectFnc(nextPoint) - objectFnc(currentPoint) < 0 ? 1 : -1};
        while ((iterCount < maxIterations) && (gradientMagnitude > gradientThresh)) {
            nextPoint = currentPoint + direction * step_size;
            T funcVal1{objectFnc(currentPoint)};
            T funcVal2 = objectFnc(nextPoint);
            T gradient{(funcVal2 - funcVal1) / step_size};
            gradientMagnitude = pow(gradient, 2);
            currentPoint = nextPoint;
            iterCount++;
        }
        return nextPoint;
    }


}


#endif //Q1_H