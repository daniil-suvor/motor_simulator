#include <iostream>
#include <vector>
#include <math.h>
#include "simulation.h"

//initialization of simulation parameters
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
//strt simulation, 
void Simulation::start() {
    while (current_motor_temperature < t_max) {
        time++;   // simulation time step 1 second
        change_speed_parametrs();
        change_current_motor_temperature();
    }
}
double Simulation::get_time() {
    return time;
}
// change in crankshaft speed, moment of force and acceleration at the next time step
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
// change in motor temperature at the next time step
void Simulation::change_current_motor_temperature() {
    double speed_heat = current_torque*h_m + pow(current_crankshaft_speed, 2)*h_v;
    // expression obtained integration dT/dt = V_h + V_c
    // V_h = h_m*M + V**2*h_v
    // V_c = C*(Ta - T)
    double new_temperature = (speed_heat + cooling_factor*ambient_temperature - speed_heat*exp(-cooling_factor*time))/cooling_factor;
    if (new_temperature == current_motor_temperature) { //loop check
        std::cout << "temperature does not change\n";
        exit(0);
    }
    current_motor_temperature = new_temperature;
}