#ifndef COLLISIONSYS_H
#define COLLISIONSYS_H

#include<queue>
#include<vector>
#include"event.h"

class CollisionSystem {
private:
    double time = 0.0;
    std::priority_queue<Event> pq;
    std::vector<Particle> particles;
    sf::RenderWindow window;

public:
    CollisionSystem(std::vector<Particle>);
    void predict(Particle*);
    void simulate();
    void redraw(double);
};

#endif
