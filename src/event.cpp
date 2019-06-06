#include "event.h"

Event::Event(Particle *a, Particle *b, double time) {
    this->p1 = a;
    this->p2 = b;
    this->time = time;
    if(a != nullptr) this->p1Col = a->getCollisionCount();
    if(b != nullptr) this->p2Col = b->getCollisionCount();
}

double Event::getTime() const {return this->time;}

Particle* Event::getParticle1() {return p1;}

Particle* Event::getParticle2() {return p2;}

bool Event::isValid() {
    if(p1 == nullptr && p2 == nullptr) return true;
    if(p1 == nullptr) return p2Col == p2->getCollisionCount();
    if(p2 == nullptr) return p1Col == p1->getCollisionCount();
    return (p1Col == p1->getCollisionCount() && p2Col == p2->getCollisionCount());
}


