#include<limits>
#include<cmath>

typedef struct vector {
    double x, y;

    double operator*(const vector &v) const {
        return x*v.x + y*v.y;
    }

    vector operator-(const vector &v) const {
        return vector(x - v.x, y - v.y);
    }

    vector(double a, double b) {x = a; y = b;}
    vector() {x = 0, y = 0;}
};


class Particle
{
private:
    vector velocity, pos;
    double radius;
    double mass;
public:
    Particle(double x, double y, double radius,
                        double vx ,double vy,  double mass);
    ~Particle();
    double collidesVWall();
    double collidesHWall();
    double collidesWith(Particle*);
    void bounceVWall();
    void bounceHWall();
    void bounce(Particle*);

};

Particle::Particle(double x, double y, double radius,
                            double vx, double vy, double mass) {
    this->velocity.x = vx; this->velocity.y = vy;
    this->pos.x = x; this->pos.y = y;
    this->radius = radius;
    this->mass = mass;
}

double Particle::collidesHWall(){
    if(!velocity.y) return std::numeric_limits<double>::infinity();
    if(velocity.y > 0) { return ((1 - radius - pos.y)/velocity.y);}
    return ((radius - pos.y)/velocity.y);
}

double Particle::collidesVWall(){
    if(!velocity.x) return std::numeric_limits<double>::infinity();
    if(velocity.x > 0) { return ((1 - radius - velocity.x)/velocity.x);}
    return ((radius - velocity.x)/velocity.x);
}

double Particle::collidesWith(Particle *that) {
    vector dV = this->velocity - that->velocity;
    vector dR = this->pos - that->pos;
    
    double d = pow(dV*dR, 2) - (dV*dV)*((dR*dR)*pow(radius,2));
    if(dV * dR >= 0 || d < 0) return std::numeric_limits<double>::infinity();
    return -(dV*dR + sqrt(d))/(dV*dR);
}

void Particle::bounceHWall() { velocity.y = -velocity.y; }

void Particle::bounceVWall() { velocity.x = -velocity.x; }

void Particle::bounce(Particle* that) {
    
}