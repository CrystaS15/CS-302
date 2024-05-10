#include <cmath>
// #include <iostream>
// using namespace std;
class lander {
    public:
        lander(double = 0, double = 0, double = 0, double = 0, double = 0, int = 0);
        double get_velocity() const;
        double get_altitude() const;
        double get_fuel_amount() const;
        int get_id() const;
        double get_mass() const;
        char get_status() const;
        bool change_flow_rate(double);
        void simulate();
        bool operator<(const lander&) const;
    private:
        double flow_rate;
        double velocity;
        double altitude;
        double fuel_amount;
        bool stillLanding;
        int id;
        int timesSimulated;
        double LANDER_MASS;
        double MAX_FUEL_CONSUMPTION_RATE;
        double MAX_THRUST;
};

lander::lander(double mass, double max_thrust, double max_fuel, double alt, 
                double fuel, int id) {
    // mass        = lander::LANDER_MASS;
    // max_thrust  = lander::MAX_THRUST;
    // max_fuel    = lander::MAX_FUEL_CONSUMPTION_RATE;
    // alt         = lander::altitude;
    // fuel        = lander::fuel_amount;
    // id          = lander::id;

    LANDER_MASS = mass;
    MAX_THRUST = max_thrust;
    // cout << "Max thrust: " << MAX_THRUST << endl;
    MAX_FUEL_CONSUMPTION_RATE = max_fuel;
    // cout << "Max fuel: " << MAX_FUEL_CONSUMPTION_RATE << endl;
    altitude = alt;
    fuel_amount = fuel;
    lander::id = id;
    
    velocity        = 0;
    stillLanding    = true;
    flow_rate       = 0;
    timesSimulated  = 0;
}

double lander::get_velocity() const {
    return velocity;
}

double lander::get_altitude() const {
    return altitude;
}

double lander::get_mass() const {
    return LANDER_MASS;
}

double lander::get_fuel_amount() const {
    return fuel_amount;
}

int lander::get_id() const {
    return id;
}

char lander::get_status() const {
    // Airborne
    if (stillLanding == true)
        return 'a';
    // Lander crashed
    if (stillLanding == false && velocity <= -2)
        return 'c';
    // Lander has landed
    if (stillLanding == false && velocity > -2)
        return 'l';
}

bool lander::change_flow_rate(double r) {
    if (r >= 0 && r <= 1) {
        // if (r > 0 && r <= 1)
        flow_rate = r;
        return true;
    }
    
    if (r < 0 || r > 1)
        return false;
}

void lander::simulate() {
    const double TIME = 1;
    double instantaneous_velocity 
    = TIME * ((flow_rate * MAX_THRUST)/(LANDER_MASS + fuel_amount)) - 1.62;
    
    if (stillLanding == true) {
        velocity += instantaneous_velocity;
        altitude += (TIME * velocity);
        if (altitude <= 0) {
            altitude = 0;
            stillLanding = false;
        }
        fuel_amount -= (TIME * MAX_FUEL_CONSUMPTION_RATE * abs(velocity));
        if (fuel_amount < 0)
            fuel_amount = 0;
        timesSimulated++;
    }
}

bool lander::operator<(const lander& rhs) const {
    if (timesSimulated < rhs.timesSimulated) return true;
    else if (timesSimulated == rhs.timesSimulated) 
    {
        if (altitude < rhs.altitude) return true;
        else if (altitude == rhs.altitude) 
        {
            if (fuel_amount < rhs.fuel_amount) return true;
            else if (fuel_amount == rhs.fuel_amount) 
            {
                if (LANDER_MASS > rhs.LANDER_MASS) return true;
                else if (LANDER_MASS == rhs.LANDER_MASS) 
                {
                    if (id < rhs.id) return true;
                    else if (id > rhs.id) return false;
                    else return false;
                } 
                else return false;
            } 
            else return false;
        } 
        else return false;
    } 
    else return false;
}