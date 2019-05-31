#include "particle.h"
#include<cmath>

#define SCALE_FACTOR 100

double mod(const vector2D &a, const vector2D &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y-b.y, 2));
}

Particle::Particle(double x, double y, double radius,
                            double vx, double vy, double mass) {
    this->velocity.x = vx; this->velocity.y = vy;
    this->pos.x = x; this->pos.y = y;
    this->radius = radius;
    this->mass = mass;
    this->collisionCount = 0;
    this->circle.setFillColor(sf::Color(100, 250, 50));
    this->circle.setRadius(float(radius)*SCALE_FACTOR);
    this->circle.setPosition(float(pos.x)*SCALE_FACTOR , float(pos.y)*SCALE_FACTOR);
}

//returns time to hit horizontal wall
double Particle::collidesHWall(){
    if(velocity.y == 0) return INFINITY;
    if(velocity.y > 0) { return ((10 - radius - pos.y)/velocity.y);}
    if(velocity.y < 0) { return ((radius - pos.y)/velocity.y);}
    double ans =  ((radius - pos.y)/velocity.y);
    return ans;
}

//returns time to hit vertical wall
double Particle::collidesVWall(){
    if(velocity.x == 0) return INFINITY;
    if(velocity.x > 0) { return ((10 - radius - pos.x)/velocity.x);}
    if(velocity.x < 0) { return ((radius - pos.x)/velocity.x);}
    double ans =  ((radius - velocity.x)/velocity.x);
    return ans;
}

//returns time to hit another particle
double Particle::collidesWith(Particle *that) {
    if(this == that) return INFINITY;
    if(that == NULL) return INFINITY;
    double dx = that->pos.x - this->pos.x;
    double dy = that->pos.y - this->pos.y;
    double dvx = that->velocity.x - this->velocity.x;
    double dvy = that->velocity.y - this->velocity.y;
    double dvdr = dx*dvx + dy*dvy;
    if(dvdr > 0) return INFINITY;
    double dvdv = dvx*dvx + dvy*dvy;
    double drdr = dx*dx + dy*dy;
    double sigma  = this->radius + that->radius;
    double d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
    if(d < 0) return INFINITY;
    return -(dvdr + sqrt(d)) / dvdv;
}

void Particle::bounceHWall() { 
    this->velocity.y = -this->velocity.y; 
    std::cout<<"Particle at ("<<pos.x<<","<<pos.y<<") collided with HWall\n";
    this->collisionCount++;
}

void Particle::bounceVWall() { 
    velocity.x = -velocity.x;
    std::cout<<"Particle at ("<<pos.x<<","<<pos.y<<") collided with VWall\n";
    this->collisionCount++;
}

void Particle::bounce(Particle* that) {
    double dx = that->pos.x - this->pos.x;
    double dy = that->pos.y - this->pos.y;
    double dvx = that->velocity.x - this->velocity.x;
    double dvy = that->velocity.y - this->velocity.y;
    double dvdr = dx*dvx + dy*dvy;    
    double dist = this->radius + that->radius;
    double J = 2 * this->mass * that->mass * dvdr / ((this->mass + that->mass) * dist);
    double Jx = J * dx / dist;
    double Jy = J * dy / dist;
    this->velocity.x += Jx / this->mass;
    this->velocity.y += Jy / this->mass;
    that->velocity.x -= Jx / that->mass;
    that->velocity.y -= Jy / that->mass;
    std::cout<<"Particle at ("<<pos.x<<","<<pos.y<<") collided with ("<<that->pos.x<<","<<that->pos.y<<") \n";
    this->collisionCount++;
    that->collisionCount++;
}

int Particle::getCollisionCount() const{return this->collisionCount;}

void Particle::move(double time) {
    pos.x += velocity.x*time;
    pos.y += velocity.y*time;
    this->circle.setPosition(float(pos.x)*SCALE_FACTOR , float(pos.y)*SCALE_FACTOR);
}

sf::CircleShape* Particle::getShape() {
    return &this->circle;
}


