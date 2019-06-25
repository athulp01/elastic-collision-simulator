#include "collisionsys.h"

#define WINDOW_DIM 800
#define FPS 60


bool operator<(const Event &a, const Event &b) {
    return a.getTime() > b.getTime();
}


CollisionSystem::CollisionSystem(std::vector<Particle> p) {
    particles = p;
    window.create(sf::VideoMode(WINDOW_DIM, WINDOW_DIM), "My window");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FPS); 
}

void CollisionSystem::predict(Particle* p) {
    if(p == NULL) return;
    for(auto i = particles.begin(); i != particles.end(); i++) {
        pq.push(Event(p, &*i, time + p->collidesWith(&*i)));
    }
    pq.push(Event(nullptr, p, time + p->collidesHWall()));
    pq.push(Event(p, nullptr, time + p->collidesVWall()));

}

void CollisionSystem::simulate() {
    for(auto i = particles.begin(); i != particles.end(); i++) {
        predict(&*i);
    }
    pq.push(Event(nullptr, nullptr, 0.0));
    int count = 0;
    while(!pq.empty()) {
        Event current = pq.top(); pq.pop();

        Particle *p1 = current.getParticle1();
        Particle *p2 = current.getParticle2();
        

        if(!current.isValid()) continue;
        
        for(auto i = particles.begin(); i != particles.end(); i++) {
            i->move(current.getTime() - time);
        }
        redraw(current.getTime() - time);
	count++;

        time = current.getTime();
        
        if(p1 == nullptr && p2 == nullptr); 
        else if(p1 == nullptr) p2->bounceHWall();
        else if(p2 == nullptr) p1->bounceVWall();
        else p1->bounce(p2);

        predict(p1);
        predict(p2);
    }
}

void CollisionSystem::redraw(double timeToCol) {
    double counter = 0, minTime = 0.001;
    while(counter <= timeToCol) {
        window.clear(sf::Color::Black);
        for(int i = 0; i<particles.size(); i++) {
            particles[i].prevPos.x += particles[i].velocity.x * minTime; 
            particles[i].prevPos.y += particles[i].velocity.y * minTime;
            particles[i].updatePos();
            window.draw(*particles[i].getShape());
        }
        window.display();
	counter += minTime;
    }
}

