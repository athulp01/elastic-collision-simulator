#include "particle.h"
#include "event.h"
#include "collisionsys.h"
#include<queue>
#include<vector>
#include<iostream>
#include<random>


int main() {
    std::vector<Particle> particles;
    double lower_bound = 0;
    double upper_bound = 9;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    int n = 20;
    while(n--) {
        particles.push_back(Particle(unif(re), unif(re), .2, unif(re), unif(re), 2));
    }
    particles.push_back(Particle(0,0,0.2,15,0,2));
    particles.push_back(Particle(0.4,0,0.2,30,0,2));
    CollisionSystem sys(particles);

    sys.simulate();
}
