#pragma once

#include "player.hxx"
#include "projectile.hxx"
#include "enemy.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>

class Model
{
public:
    // Constructor takes in a player p
    explicit Model(Player p);

    // Sets the velocity of the player to the given Dimensions
    void set_velocity(ge211::Dimensions);

    // Returns the position of the player
    ge211::Position get_position() const;

    // Creates a player projectile (type 0) and places it
    // into the proj_ vector
    void player_fire();

    // Clears the screen and awards score accordingly
    void bomb();

    // Places the given enemy into the enemy_ vector
    void place_enemy(Enemy);

    // Places the given projectile into the proj_vector
    void enemy_fire(Projectile);

    // Checks whether the given enemy has been hit by the given projectile,
    // returns true if hit is confirmed
    static bool enemy_hit(Enemy, Projectile);

    // Returns the player's score
    int get_player_score() const;

    // Updates the state of the game, checking for collisions,
    // projectile hits, and game over
    void update();

    // Checks whether the given enemy has collided with the player,
    // returns true if collision is confirmed
    bool collision(Enemy);

    // Returns true if the player's health drops to 0
    bool game_over() const;

    // Member variables
    int frame;
    int end_frame;
    double interval0;
    double interval1;
    double interval2;
    std::vector<Projectile> proj_;
    std::vector<Enemy> enemy_;
    Player p_;

    friend struct Test_access;
};
