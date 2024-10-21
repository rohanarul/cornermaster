## Cornermaster
CornerMaster is a C++ program designed to calculate optimal cornering speeds for a car on a track modeled by a polynomial curve. It computes essential parameters such as arc length, radius of curvature, and difficulty coefficient, then uses physical models to determine optimal speeds during and after a turn, factoring in the car's weight, tire grip, acceleration, and elevation changes.

## Introduction

CornerMaster started as my Math Internal Assessment (IA), where I explored the concepts of Arc Length and Radius of Curvature to create a Difficulty Coefficient for Formula 1 turns. My initial goal was to mathematically quantify the challenge posed by each corner. After self-learning C++, I decided to take this project further by transforming my Math IA into an interactive program that calculates and presents the difficulty coefficient for a given curve.

As a sophomore physics major, I expanded the scope by incorporating principles of kinematics to compute not only the difficulty coefficient but also the optimal speed through the corner and the optimal exit speed.

## Principles Used:
The optimal cornering speed is derived using the principle of centripetal force, which balances the frictional force acting between the car’s tires and the road surface. The optimal exit speed is determined using the kinematic equation that relates the car’s entry speed, its acceleration, and the distance over which the acceleration is applied. 

## How the Program Works:
User Inputs: The user is prompted to input:

- The polynomial that models the curve of the track (for both the corner and elevation profiles), the car's parameters, including entry speed, tire grip coefficient, weight, and acceleration, the boundaries of the curve (x-values) and the length of the exit portion.

- Arc Length Calculation: The program computes the arc length of the curve using Simpson's Rule, which numerically integrates the curve to estimate its length, considering both the horizontal curve and the vertical elevation profile. This gives a more accurate measure of the total distance the car will travel through the corner.

- Radius of Curvature: The program calculates the radius of curvature at the midpoint of the curve using the first and second derivatives of the polynomial function. This represents the tightness of the corner, which is essential for determining how challenging the turn is for a car to navigate.

- Difficulty Coefficient: The difficulty coefficient is then calculated as the ratio of the arc length to the radius of curvature. This coefficient provides a single numerical measure of how difficult a given corner is to drive through.

- Optimal Speed During the Corner: Using the radius of curvature, tire grip, car weight, and the principle of centripetal force, the program calculates the optimal speed at which the car can safely navigate the corner without losing grip.

- Optimal Exit Speed: After calculating the speed during the corner, the program computes the optimal exit speed by factoring in the car’s acceleration and the length of the exit portion of the curve. This uses a basic kinematic formula to estimate how much the car can accelerate as it exits the turn.

- Speed Conversion: Finally, the program converts both the optimal cornering speed and the exit speed from meters per second (m/s) to kilometers per hour (km/h) for easier interpretation by the user.

