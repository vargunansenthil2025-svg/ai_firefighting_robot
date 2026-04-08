#include <iostream>
#include <thread>
#include <chrono>
#include "vision_sim.h"
#include "pathfinding.h"
#include "iot_logger.h"

using namespace std;

int main() {
    int roomSize, robotX, robotY, fireX, fireY;

    cout << "=== AI Fire Robot Simulator ===\n";
    cout << "Enter Room Size (e.g., 10 for a 10x10 grid): ";
    cin >> roomSize;

    cout << "Enter Robot Start X & Y (e.g., 0 0): ";
    cin >> robotX >> robotY;

    cout << "Enter Fire Location X & Y (e.g., 8 8): ";
    cin >> fireX >> fireY;

    // Initialize the IoT Logger
    initIoTLogger();
    logEvent("System Started. Room size: " + to_string(roomSize));
    logEvent("Fire detected at: [" + to_string(fireX) + ", " + to_string(fireY) + "]");

    bool fireExtinguished = false;

    while (!fireExtinguished) {
        // 1. Render current state using OpenCV
        renderSimulation(roomSize, robotX, robotY, fireX, fireY);

        // 2. AI calculates next move
        fireExtinguished = moveRobotTowardsFire(robotX, robotY, fireX, fireY);

        // 3. Log the movement
        logEvent("Robot moved to: [" + to_string(robotX) + ", " + to_string(robotY) + "]");

        // Pause for visual effect
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    logEvent("CRITICAL: Fire Reached. Extinguishing sequence activated.");
    cout << "\n[SUCCESS] Fire Reached and Extinguished!\n";
    
    // Final render to show robot at fire location
    renderSimulation(roomSize, robotX, robotY, fireX, fireY);
    return 0;
}
