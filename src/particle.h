class Particle
{
private:
    double x, y, radius;
    double velocity;
    double mass;
public:
    Particle(double x, double y, double radius,
                        double velocity, double mass);
    ~Particle();
    double collidesVWall();
    double collidesHWall();
    double collidesWith(Particle);
    void bounceVWall();
    void bounceHWall();
    void bounce(Particle);

};

Particle::Particle(double x, double y, double radius,
                            double velocity, double mass) {
}

Particle::~Particle()
{
}
