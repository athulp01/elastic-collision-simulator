#include "particle.h"
#include "event.h"
#include<queue>
#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>

bool operator<(const Event &a, const Event &b) {
    return a.getTime() > b.getTime();
}


int main() {
   // sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::priority_queue<Event> pq;
    std::vector<Particle> particles;

    particles.push_back(Particle(0.22, 0.24, .2, 0, 0.2, 2));
    particles.push_back(Particle(0.22, 0.74, .2, 0, -0.2, 4));

    for(auto i = particles.begin(); i != particles.end(); i++) {
        if(i->collidesHWall() != -1) pq.push(Event(nullptr, &*i, i->collidesHWall()));
        if(i->collidesVWall() != -1) pq.push(Event(&*i, nullptr, i->collidesVWall()));
        for(auto j = i + 1; j != particles.end(); j++) {
            if(i->collidesWith(&*j) != -1) pq.push(Event(&*i, &*j, i->collidesWith(&*j)));
        }
    }

    Particle *p1, *p2;
    int collisions = 50;

    //sf::CircleShape circle2(20);
    //circle1.setFillColor(sf::Color(100, 250, 50));
    //circle2.setFillColor(sf::Color(100, 250, 50));

    while(/*window.isOpen() &&*/ collisions--) {

        sf::Event event;
        /*while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
  //sf::CircleShape circle2(20);
    //circle1.setFillColor(sf::Color(100, 250, 50));*/
        Event current = pq.top(); pq.pop();
        if(!current.isValid()) {std::cout<<"skipped\n";continue;}
        p1 = current.getParticle1();
        p2 = current.getParticle2();

        if(p1 == nullptr && p2 == nullptr) continue;
        
        std::cerr<<"Time is "<<current.getTime()<<"\n";

        if(p1 == nullptr && p2 == nullptr) continue;
        if(p1 == nullptr) {p2->bounceHWall();}
        else if(p2 == nullptr) p1->bounceVWall();
        else p1->bounce(p2);

        for(auto i = particles.begin(); i != particles.end(); i++) {
            i->move(current.getTime());
        }

        //if(p1 != nullptr) circle1.setPosition(p1->pos.x*800,p1->pos.y*600);
        //if(p2 != nullptr) circle2.setPosition(p2->pos.x*800,p2->pos.y*600);
       // window.draw(circle1);
       // window.draw(circle2);
        //window.display();


        if(p1 != nullptr) {
            if(p1->collidesHWall() != -1) pq.push(Event(NULL, p1, p1->collidesHWall() ));
            if(p1->collidesVWall() != -1) pq.push(Event(p1, NULL, p1->collidesVWall() ));
        }
        if(p2 != nullptr) {
            if(p2->collidesHWall() != -1)pq.push(Event(NULL, p2, p2->collidesHWall() ));
            if(p2->collidesVWall() != -1)pq.push(Event(p2, NULL, p2->collidesVWall() ));
        }

        for(auto i = particles.begin(); i != particles.end(); i++) {
            if(p1 != nullptr && p1->collidesWith(&*i) != -1) pq.push(Event(p1, &*i, p1->collidesWith(&*i) ));
            if(p2 != nullptr && p2->collidesWith(&*i) != -1) pq.push(Event(p2, &*i, p2->collidesWith(&*i) ));
        }

    }


}