#include "player.hxx"

Player::Player(ge211::Position location, ge211::Dimensions velocity)
        : hitbox({location.x, location.y, 20, 20})
        , hitbox_velocity(velocity)
        , score(0)
        , final_score(0)
        , health(3)
        , alive(true)
        , bomb_uses(3)
        , invuln(0)
{}

Player Player::next()
{
    ge211::Position next_pos = {this->hitbox.top_left().x + hitbox_velocity.width,
                                this->hitbox.top_left().y + hitbox_velocity.height};
    Player next_player(next_pos, this->hitbox_velocity);
    next_player.alive = this->alive;
    next_player.score = this->score;
    next_player.health = this->health;
    next_player.hitbox_velocity = this->hitbox_velocity;
    next_player.bomb_uses = this->bomb_uses;
    next_player.invuln = this->invuln;
    return next_player;
}

bool Player::hits_edge()
{
    return next().hitbox.top_left().x < 0 || next().hitbox.top_right().x > 1500 ||
           next().hitbox.bottom_left().y < 150 ||
           next().hitbox.top_left().y > 850;
}

bool Player::player_hit(Projectile proj) const
{
    int hor_distance = abs(hitbox.center().x - proj.hurtbox.center().x);
    int vert_distance = abs(hitbox.center().y - proj.hurtbox.center().y);

    return (hor_distance <= ((hitbox.width / 2) + (proj.hurtbox.width / 2))) &&
           (vert_distance <= ((hitbox.height / 2) + (proj.hurtbox.height / 2)));
}

