#ifndef Q1_H
#define Q1_H

#include <iostream>
#include <cmath>
#include <functional>



namespace q1 {

    template<typename T = double, typename F = std::function<T(T)>>
    inline T gradient_descent(T initial_value, T step_size, F gradient_func = F()) {
        T limit{step_size / 50};
        size_t Max_lim{1000};
        size_t Counter{0};
        T slope{1.0};
        T currentP{initial_value};
        T nextP{currentP + step_size};
        int dir{0};
        if(gradient_func(nextP) - gradient_func(currentP) < 0){
            dir = 1;
        }
        else{
            dir = -1;
        }
        while ((Counter < Max_lim) && (slope > limit)) {
            nextP = currentP + dir * step_size;
            T currentOut{gradient_func(currentP)};
            T nextOut = gradient_func(nextP);
            T gradient{(currentOut - nextOut) / step_size};
            slope = pow(gradient, 2);
            currentP = nextP;
            Counter++;
        }

        return currentP;
    }

}

#endif //Q1_H