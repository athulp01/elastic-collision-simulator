#include "particle.h"
#include<cmath>

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
}

//returns time to hit horizontal wall
double Particle::collidesHWall(){
    if(velocity.y == 0) return -1;
    if(velocity.y > 0) { return ((1 - radius - pos.y)/velocity.y);}
    if(velocity.y < 0) { return ((radius - pos.y)/velocity.y);}
    double ans =  ((radius - pos.y)/velocity.y);
    return ans;
}

//returns time to hit vertical wall
double Particle::collidesVWall(){
    if(velocity.x == 0) return -1;
    if(velocity.x > 0) { return ((1 - radius - pos.x)/velocity.x);}
    if(velocity.x < 0) { return ((radius - pos.x)/velocity.x);}
    double ans =  ((radius - velocity.x)/velocity.x);
    return ans;
}

//returns time to hit another particle
double Particle::collidesWith(Particle *that) {
    if(this == that) return -1;
    if(that == nullptr) return -1;
    vector2D dV = this->velocity - that->velocity;
    vector2D dR = this->pos - that->pos;
    if(((dR*dR)-pow(this->radius+that->radius,2)) == 0) return -1;
    double d = pow(dV*dR, 2) - ((dV*dV)*((dR*dR)-pow(this->radius+that->radius,2)));
    if(dV * dR >= 0 || d < 0) return -1;
    std::cout<<"delta T num = "<<-(dV*dR + sqrt(d))<<"\n";
    std::cout<<"delta T den = "<<(dV*dV)<<"\n";
    double ans  = -(dV*dR + sqrt(d))/(dV*dV);
    return ans;

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
    vector2D dV = this->velocity - that->velocity;
    vector2D dR = this->pos - that->pos;

    double J = (2*this->mass*that->mass*(dV*dR));
    J /= ((this->mass+ that->mass) * (this->radius + that->radius));

    double Jx = (J * (this->pos.x - that->pos.x)) / (this->radius + that->radius);
    double Jy = (J * (this->pos.y - that->pos.y)) / (this->radius + that->radius);

    this->velocity.x += Jx/this->mass; this->velocity.y += Jy/this->mass;
    that->velocity.x += -Jx/this->mass; that->velocity.y += -Jy/this->mass;

    std::cout<<"Particle at ("<<pos.x<<","<<pos.y<<") collided with ("<<that->pos.x<<","<<that->pos.y<<") \n";
    this->collisionCount++;
}

int Particle::getCollisionCount() const{return this->collisionCount;}

void Particle::move(double time) {
    pos.x += velocity.x*time;
    pos.y += velocity.y*time;
}

sf::CircleShape Particle::getCircle() { return circle; }

