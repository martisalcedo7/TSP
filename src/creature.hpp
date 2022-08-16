#ifndef CREATURE_HPP
#define CREATURE_HPP


struct position
{
    float x;
    float y;
};

class Creature{
    float angle;
    float velocity;

    position current_position;

    void next_position(float angle, float velocity);
    
};

#endif // CREATURE

