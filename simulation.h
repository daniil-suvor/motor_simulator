#include "motor.h"

class Simulation : public Motor {
    public:
        Simulation(double set_moment_inertia,\
              double set_t_max, double set_h_m,\
              double set_h_v, double set_cooling_factor,\
              std::vector <double>& set_torque,\
              std::vector <double>& set_crankshaft_speed,\
              double set_ambient_temperature);
        double get_time();
        void start();
        void change_speed_parametrs();
        void change_current_motor_temperature();    
    private:
        double time, ambient_temperature,\
        acceleration, current_torque,\
        current_crankshaft_speed,\
        current_motor_temperature;
        int index;
};