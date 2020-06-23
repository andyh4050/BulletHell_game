#include "projectile.hxx"


Projectile::Projectile(ge211::Position location, int type)
        : type(type)
        , active(true)
{
    if (type == 0)
    {
        hurtbox = {location.x, location.y, 10, 10};
        hurtbox_velocity = {0, -20};
        turn = {0, 0};
    }
    else if (type == 1)
    {
        hurtbox = {location.x, location.y, 10, 10};
        hurtbox_velocity = {0, 5};
        turn = {0, 0};
    }
    else if (type == 2)
    {
        hurtbox = {location.x, location.y, 10, 10};
        hurtbox_velocity = {-5, 5};
        turn = {0, 0};
    }
    else if (type == 3)
    {
        hurtbox = {location.x, location.y, 10, 10};
        hurtbox_velocity = {5, 5};
        turn = {0, 0};
    }
    else if (type == 4)
    {
        hurtbox = {location.x, location.y, 20, 20};
        hurtbox_velocity = {0, 15};
        turn = {0, 0};
    }
    else if (type == 5)
    {
        hurtbox = {location.x, location.y, 15, 15};
        hurtbox_velocity = {5, 5};
        turn = {-1, 0};
    }
    else if (type == 6)
    {
        hurtbox = {location.x, location.y, 15, 15};
        hurtbox_velocity = {-5, 5};
        turn = {1, 0};
    }
}

void Projectile::next()
{
    hurtbox.x = hurtbox.x + hurtbox_velocity.width;
    hurtbox.y = hurtbox.y + hurtbox_velocity.height;
}

void Projectile::accelerate()
{
    hurtbox_velocity = hurtbox_velocity + turn;
}

bool Projectile::hits_edge() const
{
    return hurtbox.top_left().x < 0 || hurtbox.top_right().x > 1500 ||
           hurtbox.bottom_left().y < 0 ||
           hurtbox.top_left().y > 1000;
}

void Projectile::destroy_proj()
{
    active = false;
}
