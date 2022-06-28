class Motor {
    public:
        Motor(double set_moment_inertia,\
              double set_t_max, double set_h_m,\
              double set_h_v, double set_cooling_factor,\
              std::vector <double>& set_torque,\
              std::vector <double>& set_crankshaft_speed);
        void check_parametrs();
    protected:
        double moment_inertia, t_max, h_m, h_v, cooling_factor;
        std::vector <double> torque;
        std::vector <double> crankshaft_speed;
};