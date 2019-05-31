#include "particle.h"
#include "event.h"
#include "collisionsys.h"
#include<queue>
#include<vector>
#include<iostream>


int main() {
    std::vector<Particle> particles;
    particles.push_back(Particle(0.22, 0.24, .2, 0, 0.2, 2));
    particles.push_back(Particle(0.22, 0.74, .2, 0, -0.2, 4));

    CollisionSystem sys(particles);

    sys.simulate();
}