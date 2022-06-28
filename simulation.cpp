#include <iostream>
#include <vector>
#include <math.h>
#include "simulation.h"

Simulation::Simulation(double set_moment_inertia,\
              double set_t_max, double set_h_m,\
              double set_h_v, double set_cooling_factor,\
              std::vector <double>& set_torque,\
              std::vector <double>& set_crankshaft_speed,\
              double set_ambient_temperature)\
              : Motor(set_moment_inertia, set_t_max, set_h_m, set_h_v,\
                      set_cooling_factor, set_torque, set_crankshaft_speed) {
    time = 0;
    ambient_temperature = set_ambient_temperature;
    current_motor_temperature = ambient_temperature;
    current_torque = torque[0];
    current_crankshaft_speed = crankshaft_speed[0];
    acceleration = current_torque/moment_inertia;
    index = 1;
}
void Simulation::start() {
    while (current_motor_temperature < t_max) {
        time++;
        change_speed_parametrs();
        change_current_motor_temperature();
    }
}
double Simulation::get_time() {
    return time;
}    
void Simulation::change_speed_parametrs() {
    if (current_crankshaft_speed + acceleration*time > crankshaft_speed[index]) {
        time--;
        time += (crankshaft_speed[index] - current_crankshaft_speed)/acceleration;
        current_crankshaft_speed = crankshaft_speed[index];
        current_torque = torque[index];
        if (index + 1 < (int)torque.size()) {
            index++;
        }
    }else {
        current_crankshaft_speed += acceleration*time;
        current_torque = (torque[index] - torque[index-1])/(crankshaft_speed[index] - crankshaft_speed[index - 1])*\
                         (current_crankshaft_speed - crankshaft_speed[index - 1]) + torque[index - 1];
    }
    acceleration = current_torque/moment_inertia;
}
void Simulation::change_current_motor_temperature() {
    double speed_heat = current_torque*h_m + pow(current_crankshaft_speed, 2)*h_v;
    double new_temperature = (speed_heat + cooling_factor*ambient_temperature - speed_heat*exp(-cooling_factor*time))/cooling_factor;
    if (new_temperature == current_motor_temperature) {
        std::cout << "temperature does not change\n";
        exit(0);
    }
    current_motor_temperature = new_temperature;
}