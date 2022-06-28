#include <iostream>
#include <vector>
#include "motor.h"

//initialization of motor parameters
Motor::Motor(double set_moment_inertia,\
              double set_t_max, double set_h_m,\
              double set_h_v, double set_cooling_factor,\
              std::vector <double>& set_torque,\
              std::vector <double>& set_crankshaft_speed) {
    torque.assign(set_torque.begin(), set_torque.end());
    crankshaft_speed.assign(set_crankshaft_speed.begin(),\
                            set_crankshaft_speed.end());
    moment_inertia = set_moment_inertia;
    t_max = set_t_max;
    h_m = set_h_m;
    h_v = set_h_v;
    cooling_factor = set_cooling_factor;
    check_parametrs();
}
//parameter validation
void Motor::check_parametrs() {
    if (torque.size() != crankshaft_speed.size()) {
        std::cout << "Different number of points for the dependence of torque on the speed of rotation of the crankshaft\n";
        exit(0);
    }
    if (torque.size() < 2) {
        std::cout << "Error number paramerts\n";
        exit(0);
    }
    for (int i = 0; i < (int)torque.size(); i++) {
        if (torque[i] < 0) {
            std::cout << "Error torque\n";
            exit(0);
        }
        if ((crankshaft_speed[i] < 0)||\
            ((i > 0 ) && (crankshaft_speed[i] <= crankshaft_speed[i - 1]))) {
            std::cout << "Error crankshaft speed\n";
            exit(0);
        }
    }
    if (torque.back() != 0) {
        std::cout << "Error torque\n";
        exit(0);
    }
    if (moment_inertia <= 0) {
        std::cout << "Error moment of inertia\n";
        exit(0);
    }
    if (t_max < 0) {
        std::cout << "Error superheat temperature\n";
        exit(0);
    }
    if (h_v < 0) {
        std::cout << "Error coefficient of dependence of the heating rate on the speed of rotation of the crankshaft\n";
        exit(0);
    }
    if (h_m < 0) {
        std::cout << "Error coefficient of heating rate versus torque\n";
        exit(0);
    }
    if (cooling_factor < 0) {
        std::cout << "Error coefficient of dependence of the cooling rate on the temperature of the engine and the environment environments\n";
        exit(0);
    }
}
