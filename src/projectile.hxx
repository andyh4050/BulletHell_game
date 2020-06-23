#pragma once

#include <ge211.hxx>
#include <iostream>


class Projectile
{
public:
    // Constructor takes a position (projectile's position),
    // and an int representing the type
    Projectile(ge211::Position, int);

    // Changes the projectile's position based on its velocity
    void next();

    // Changes the projectile's velocity based on its acceleration
    void accelerate();

    // Checks whether the projectile hits the edge of the screen
    bool hits_edge() const;

    // Sets "active" to false
    void destroy_proj();

    // Member variables
    ge211::Rectangle hurtbox;
    ge211::Dimensions hurtbox_velocity;
    int type;
    ge211::Dimensions turn;
    bool active;
};
