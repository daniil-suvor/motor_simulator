#include <iostream>
#include <vector>
#include "simulation.h"

int main() {
    double moment_inertia = 20;
    double t_max = 110;
    std::vector <double> torque = {20, 75, 100, 105, 75, 0};
    std::vector <double> crankshaft_speed = {0, 75, 150, 200, 250, 300};
    double h_m = 0.01;
    double h_v = 0.0001;
    double cooling_factor = 0.1;
    double ambient_temperature;
    std::cout << "input ambient temperature ", std::cin >> ambient_temperature; 
    Simulation ex_motor(moment_inertia, t_max, h_m, h_v,\
            cooling_factor, torque, crankshaft_speed, ambient_temperature);
    ex_motor.start();
    std::cout << "time to overheat " << ex_motor.get_time() << " seconds\n";
    return 0;
}
