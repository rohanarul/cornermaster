#include <iostream>
#include <cmath>
#include <limits>

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
    if (a == 0) {
        std::cerr << "Warning: The curve is linear (a = 0). Radius of curvature is infinite." << std::endl;
        return std::numeric_limits<double>::infinity();
    }
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

    // Add a safeguard against unrealistic values (negative or zero radius)
    if (radius <= carHeight) {
        std::cerr << "Error: Radius of curvature must be greater than car height." << std::endl;
        return 0; // Impossible to corner with such a small radius
    }

    // Calculate the maximum speed based on tire grip and radius of curvature
    double maxSpeed = std::sqrt((tireGrip * g * radius) / (1 - (carHeight / radius)));

    return maxSpeed; // Speed in m/s
}

// Function to calculate the optimal exit speed based on acceleration and distance
double optimalExitSpeed(double entrySpeed, double acceleration, double exitLength, double tireGrip) {
    const double g = 9.81; // Acceleration due to gravity (m/s^2)
    // The maximum exit speed is also limited by the tire grip and available traction
    double maxExitSpeed = std::sqrt(tireGrip * g * exitLength);

    // The actual exit speed should not exceed the maximum based on grip
    return std::min(std::sqrt((entrySpeed * entrySpeed) + 2 * acceleration * exitLength), maxExitSpeed);
}

// Function to validate input ensuring it's non-negative (for values like x1)
double validateNonNegativeInput(const std::string &prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0) {
            break;
        } else {
            std::cout << "Error: Please enter a non-negative numeric value." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return value;
}

// Function to validate input and ensure it's a positive value
double validatePositiveInput(const std::string &prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            break;
        } else {
            std::cout << "Error: Please enter a positive numeric value." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return value;
}

int main() {
    // Input parameters from the user
    double a, b, c, x1, x2, exitLength, elevationChange, entrySpeedKmh;
    double tireGripCoefficient, carWeight, carAcceleration;

    std::cout << "****************************************************************" << std::endl;
    std::cout << "********************* WELCOME TO CORNERMASTER ******************" << std::endl;
    std::cout << "****************************************************************" << std::endl;
    std::cout << "This program calculates the optimal speed and exit speed for a car\n";
    std::cout << "navigating a corner defined by a quadratic curve (y = ax^2 + bx + c).\n";
    std::cout << "You will be prompted to enter the curve parameters, car details, and\n";
    std::cout << "other relevant inputs. All speeds are calculated in km/h.\n";
    std::cout << "****************************************************************" << std::endl;

    // Prompting the user for input
    std::cout << "\nEnter the polynomial coefficients for the curve (a, b, c for y = ax^2 + bx + c):\n";
    while (true) {
        std::cout << "a: ";
        if (std::cin >> a) break;
        std::cout << "Error: Please enter a valid numeric value for 'a'.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (true) {
        std::cout << "b: ";
        if (std::cin >> b) break;
        std::cout << "Error: Please enter a valid numeric value for 'b'.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (true) {
        std::cout << "c: ";
        if (std::cin >> c) break;
        std::cout << "Error: Please enter a valid numeric value for 'c'.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    x1 = validateNonNegativeInput("\nEnter the lower bound of the curve (x1, in meters): ");
    x2 = validatePositiveInput("Enter the upper bound of the curve (x2, in meters): ");
    exitLength = validatePositiveInput("Enter the length of the exit portion of the curve (in meters): ");
    elevationChange = validateNonNegativeInput("Enter the constant elevation change (in meters): ");
    entrySpeedKmh = validatePositiveInput("Enter the car's entry speed (in km/h): ");

    // Tire grip options for F1 tires (informing the user)
    std::cout << "\nChoose tire grip coefficient (for reference, F1 tires range):\n";
    std::cout << "Pirelli C1 (0.9), C2 (1.0), C3 (1.1), C4 (1.2), C5 (1.3), Intermediate (0.8), Wet (0.7)\n";
    tireGripCoefficient = validatePositiveInput("Enter the tire grip coefficient: ");

    carWeight = validatePositiveInput("Enter the car's weight (in kg): ");
    carAcceleration = validatePositiveInput("Enter the car's acceleration during the exit (in m/s^2): ");

    // Perform calculations
    double entrySpeedMs = kmhToMs(entrySpeedKmh); // Convert to m/s
    double arcLength = calculateArcLength(a, b, c, x1, x2, elevationChange);
    double radiusOfCurvature = calculateRadiusOfCurvature(a, b, c, (x1 + x2) / 2);
    double optimalCornerSpeed = optimalSpeed(radiusOfCurvature, tireGripCoefficient, carWeight);
    double optimalExitSpeedMs = optimalExitSpeed(entrySpeedMs, carAcceleration, exitLength, tireGripCoefficient);
    double optimalExitSpeedKmh = msToKmh(optimalExitSpeedMs);  // Convert to km/h

    // Output the results
    std::cout << "\n****************************************************************" << std::endl;
    std::cout << "*************************** RESULTS ***************************" << std::endl;
    std::cout << "****************************************************************" << std::endl;
    std::cout << "Arc Length (with constant elevation): " << arcLength << " meters" << std::endl;
    std::cout << "Radius of Curvature: " << radiusOfCurvature << " meters" << std::endl;
    std::cout << "Optimal Speed during the corner: " << msToKmh(optimalCornerSpeed) << " km/h" << std::endl;
    std::cout << "Optimal Exit Speed: " << optimalExitSpeedKmh << " km/h" << std::endl;
    std::cout << "****************************************************************" << std::endl;

    return 0;
}