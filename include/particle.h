#ifndef PARTICLE_H
#define PARTICLE_H

#include<limits>
#include<cmath>
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

struct vector2D {
    double x, y;

    double operator*(const vector2D &v) const {
        return x*v.x + y*v.y;
    }

    vector2D operator-(const vector2D &v) const {
        return vector2D(x - v.x, y - v.y);
    }

    vector2D(double a, double b) {x = a; y = b;}
    vector2D() {x = 0, y = 0;}
};

//A rigid body particle
class Particle {
private:
    double radius;
    double mass;
    int collisionCount;
    sf::CircleShape circle;
public:
    vector2D velocity;
    vector2D pos;
    vector2D prevPos;
    Particle(double x, double y, double radius,
                        double vx ,double vy,  double mass);
    double collidesVWall(); 
    double collidesHWall();
    double collidesWith(Particle*);
    void bounceVWall();
    void bounceHWall();
    void bounce(Particle*);
    int getCollisionCount() const; //TODO : 
    void move(double);
    sf::CircleShape* getShape();
    void updatePos();

};

#endif
