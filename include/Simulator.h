#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "PhysicsObject.h"
#include "Logging.h"
#include <string>

class Simulator {
public:
    Simulator(double Vm, double Alpha, double Gamma, double Yb, double X, double Z, double Length, double Width, double Height, double tInc);
    
    void initialize();
    int runSimulationStep();
    std::string getSimulationStatus() const;

private:
    double Vm, Alpha, Gamma, Yb, X, Z, Length, Width, Height, simulationTime, tInc;
    int status;
    
    PhysicsObject projectile;
    PhysicsObject target;

    void updateProjectile();
    bool checkCollision() const;
    bool isSimulationTimedOut() const;
};

#endif // SIMULATOR_H
