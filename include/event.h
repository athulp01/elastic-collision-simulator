#ifndef EVENT_H
#define EVENT_H

#include "particle.h"

class Event{
private:
    Particle *p1, *p2;
    int p1Col = 0, p2Col = 0;
    double time;
public:
    Event(Particle *a, Particle *b, double time);
    double getTime() const;
    Particle* getParticle1();
    Particle* getParticle2();
    bool isValid();

};

#endif
