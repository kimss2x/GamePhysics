#include <iostream>
#include <fstream>
#include "Simulator.h"
#include "websocket.h"
#include <limits>

double Vm = 100.0;
double Alpha = 45.0;
double Gamma = 0.0;
double Yb = 10.0;
double X = 1020.0;
double Z = 0.0;
double Length = 10.0;
double Width = 10.0;
double Height = 10.0;
double tInc = 0.1;

void GetUserInput() {
    char key;
    double inputValue;
    while (true) {
        std::cout << "Enter 'x' to set Pitch (Alpha) or 'y' to set Yaw (Gamma), or 's' to start simulation: ";
        std::cin >> key;

        if (key == 's') {
            break;
        }

        switch (key) {
            case 'x':
                std::cout << "Enter Pitch (Alpha) in degrees: ";
                std::cin >> inputValue;
                if (!std::cin.fail()) {
                    Alpha = inputValue;
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, Pitch (Alpha) remains " << Alpha << " degrees.\n";
                }
                break;
            case 'y':
                std::cout << "Enter Yaw (Gamma) in degrees: ";
                std::cin >> inputValue;
                if (!std::cin.fail()) {
                    Gamma = inputValue;
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, Yaw (Gamma) remains " << Gamma << " degrees.\n";
                }
                break;
            default:
                std::cout << "Invalid option. Please enter 'x', 'y', or 's'.\n";
                break;
        }
    }
}

int main() {
    GetUserInput();

    Simulator simulator(Vm, Alpha, Gamma, Yb, X, Z, Length, Width, Height, tInc);
    simulator.initialize();

    WebSocketServer wsServer;
    wsServer.start();

    while (simulator.runSimulationStep() == 0) {
        std::string status = simulator.getSimulationStatus();
        wsServer.sendSimulationData(status);
    }

    wsServer.stop();
    return 0;
}
