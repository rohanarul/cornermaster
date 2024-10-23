#include <iostream>
#include <cmath>

// Function to convert speed from km/h to m/s
double kmhToMs(double speedKmh) {
    return speedKmh / 3.6;
}

// Function to convert speed from m/s to km/h
double msToKmh(double speedMs) {
    return speedMs * 3.6;
}

// Function to calculate radius of curvature at a given point on the curve
double calculateRadiusOfCurvature(double a, double b, double c, double x) {
    double dydx = 2 * a * x + b;      // First derivative
    double d2ydx2 = 2 * a;            // Second derivative (constant for a quadratic)
    double radius = std::pow(1 + dydx * dydx, 1.5) / std::abs(d2ydx2);
    return radius;
}

// Function to calculate the arc length of a curve (numerical integration)
double calculateArcLength(double a, double b, double c, double x1, double x2, double elevationChange) {
    int n = 1000; // Number of intervals for numerical integration
    double dx = (x2 - x1) / n;
    double arcLength = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = x1 + i * dx;
        double dydx = 2 * a * x + b;  // First derivative
        double dzdx = elevationChange / (x2 - x1);  // Constant elevation slope
        double ds = std::sqrt(1 + dydx * dydx + dzdx * dzdx) * dx;
        arcLength += ds;
    }

    return arcLength;
}

// Function to calculate the optimal speed during the corner (without aerodynamic drag)
double optimalSpeed(double radius, double tireGrip, double carWeight, double carHeight = 0.5) {
    const double g = 9.81; // Acceleration due to gravity (m/s^2)

    // Calculate the maximum speed based on tire grip and radius of curvature
    double maxSpeed = std::sqrt((tireGrip * g * radius) / (1 - (carHeight / radius)));

    return maxSpeed; // Speed in m/s
}

// Function to calculate the optimal exit speed based on acceleration and distance
double optimalExitSpeed(double entrySpeed, double acceleration, double exitLength) {
    return std::sqrt((entrySpeed * entrySpeed) + 2 * acceleration * exitLength);
}

// Function to validate input ensuring it's non-negative (for values like x1)
double validateNonNegativeInput(const std::string &prompt) {
    double value;
    do {
        std::cout << prompt;
        std::cin >> value;
        if (value < 0) {
            std::cout << "Error: Please enter a non-negative value." << std::endl;
        }
    } while (value < 0);
    return value;
}

// Function to validate input and ensure it's a positive value
double validatePositiveInput(const std::string &prompt) {
    double value;
    do {
        std::cout << prompt;
        std::cin >> value;
        if (value <= 0) {
            std::cout << "Error: Please enter a positive value." << std::endl;
        }
    } while (value <= 0);
    return value;
}

int main() {
    // Input parameters from the user
    double a, b, c, x1, x2, exitLength, elevationChange, entrySpeedKmh;
    double tireGripCoefficient, carWeight, carAcceleration;

    std::cout<<"*****************************************************************";
    std::cout<<"*********************WELCOME TO CORNERMASTER*********************";
    std::cout<<"*****************************************************************";

    // Prompting the user for input
    std::cout << "Enter the polynomial coefficients for the curve (a, b, c for y = ax^2 + bx + c): ";
    std::cin >> a >> b >> c;

    // Allow x1 to be non-negative (including 0)
    x1 = validateNonNegativeInput("Enter the lower bound of the curve (x1): ");
    x2 = validatePositiveInput("Enter the upper bound of the curve (x2): ");
    
    exitLength = validatePositiveInput("Enter the length of the exit portion of the curve (meters): ");
    elevationChange = validateNonNegativeInput("Enter the constant elevation change in meters: ");

    entrySpeedKmh = validatePositiveInput("Enter the car's entry speed (km/h): ");
    double entrySpeedMs = kmhToMs(entrySpeedKmh); // Convert to m/s

    // Tire grip options for F1 tires (informing the user)
    std::cout << "Choose tire grip coefficient (for reference, F1 tires range):" << std::endl;
    std::cout << "Pirelli C1 (0.9), C2 (1.0), C3 (1.1), C4 (1.2), C5 (1.3), Intermediate (0.8), Wet (0.7)" << std::endl;
    tireGripCoefficient = validatePositiveInput("Enter the tire grip coefficient: ");

    carWeight = validatePositiveInput("Enter the car's weight (kg): ");
    carAcceleration = validatePositiveInput("Enter the car's acceleration during the exit (m/s^2): ");

    // Calculate the arc length of the curve
    double arcLength = calculateArcLength(a, b, c, x1, x2, elevationChange);

    // Calculate the radius of curvature at the midpoint
    double radiusOfCurvature = calculateRadiusOfCurvature(a, b, c, (x1 + x2) / 2);

    // Calculate the optimal speed during the corner (without aerodynamic drag)
    double optimalCornerSpeed = optimalSpeed(radiusOfCurvature, tireGripCoefficient, carWeight);

    // Calculate the optimal exit speed based on acceleration
    double optimalExitSpeedMs = optimalExitSpeed(entrySpeedMs, carAcceleration, exitLength);
    double optimalExitSpeedKmh = msToKmh(optimalExitSpeedMs);  // Convert to km/h

    // Output the results
    std::cout << "Arc Length (with constant elevation): " << arcLength << " meters" << std::endl;
    std::cout << "Radius of Curvature: " << radiusOfCurvature << " meters" << std::endl;
    std::cout << "Optimal Speed during the corner: " << msToKmh(optimalCornerSpeed) << " km/h" << std::endl;
    std::cout << "Optimal Exit Speed: " << optimalExitSpeedKmh << " km/h" << std::endl;

    return 0;
}
