#include "Particle.h"

string Particle::toString()
{
    static stringstream ss;
    ss.str("");
    ss << "Particle {" << endl; 
    ss << "\t acceleration: " << to_string(acceleration) << endl;
    ss << "\t speed: " << to_string(speed) << endl;
    ss << "\t pos: " << to_string(pos) << endl;
    ss << "}" << endl;; 
    return ss.str(); 
}