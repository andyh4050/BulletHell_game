#pragma once

#include <iostream>
#include <ge211.hxx>
#include "projectile.hxx"

class Player
{
public:
    // Constructor takes a position and a set of dimensions
    // (represents player velocity)
    Player(ge211::Position, ge211::Dimensions);

    // Creates a new player at the next location
    // (with velocity added to it's position once)
    Player next();

    // Returns true if the player hits the edge of the screen
    bool hits_edge();

    // Returns true if the player is hit by the given projectile
    bool player_hit(Projectile) const;

    // Member variables
    ge211::Rectangle hitbox;
    ge211::Dimensions hitbox_velocity;
    int score;
    int final_score;
    int invuln;
    int health;
    int bomb_uses;
    bool alive;
};


