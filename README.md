## Cornermaster
CornerMaster is a C++ program designed to calculate optimal cornering speeds for a car on a track modeled by a polynomial curve. It computes essential parameters such as arc length, radius of curvature, and difficulty coefficient, then uses physical models to determine optimal speeds during and after a turn, factoring in the car's weight, tire grip, acceleration, and elevation changes.

## Introduction

CornerMaster started as my Math Internal Assessment (IA), where I explored the concepts of Arc Length and Radius of Curvature to create a Difficulty Coefficient for Formula 1 turns. My initial goal was to mathematically quantify the challenge posed by each corner. After self-learning C++, I decided to take this project further by transforming my Math IA into an interactive program that calculates and presents the difficulty coefficient for a given curve.

As a sophomore physics major, I expanded the scope by incorporating principles of kinematics to compute not only the difficulty coefficient but also the optimal speed through the corner and the optimal exit speed.

<u>Principles Used:<u>
Optimal Speed During the Corner: The optimal cornering speed is derived using the principle of centripetal force, which balances the frictional force acting between the car’s tires and the road surface. The formula used is:

!(CodeCogsEqn)

Where:
- v_opt = optimal speed during the corner (m/s)
- mu = tire grip coefficient (dimensionless)
- g = acceleration due to gravity (9.81 m/s²)
- R = radius of curvature (m)

