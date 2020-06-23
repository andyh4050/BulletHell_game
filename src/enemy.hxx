#pragma once

#include "projectile.hxx"
#include <ge211.hxx>

class Enemy
{
public:
    // Constructor takes a position and an int (represents enemy
    // type)
    Enemy(ge211::Position, int);

    // Returns the enemy after their velocity has been
    // added to their position
    void next();

    // Accelerates the enemy's velocity by a given x and y value
    void accelerate();

    // Destroys the enemy
    void destroy_enemy();

    // Checks if the enemy hits the edge of the window
    bool hits_edge() const;

    // Member variables

    // Enemy's hitbox and speed
    ge211::Rectangle hitbox;
    ge211::Dimensions hitbox_velocity;

    // Enemy's type
    int type;

    // Enemy's acceleration
    ge211::Dimensions turn;

    // The type of projectile fired by the enemy
    Projectile enemy_projectile;

    // The health and state of the enemy
    int enemy_health;
    bool active;
};


