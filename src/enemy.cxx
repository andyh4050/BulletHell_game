#include "enemy.hxx"

Enemy::Enemy(ge211::Position location, int type)
        : type(type)
        , active(true)
        , enemy_projectile(Projectile({location.x,location.y}, 1))
{
    if (type == 0)
    {
        hitbox = {location.x,location.y,60,80};
        hitbox_velocity = {0,1};
        turn = {1,0};
        enemy_health = 1;
        enemy_projectile = Projectile({hitbox.x + 20,hitbox.y + 100}, 1);
    }
    else if (type == 1)
    {
        hitbox = {location.x,location.y,250,200};
        hitbox_velocity = {-1,0};
        turn = {0 ,0};
        enemy_health = 20;
        enemy_projectile = Projectile({hitbox.x + 130,hitbox.y + 100}, 4);
    }
    else if (type == 2)
    {
        hitbox = {location.x,location.y,80,120};
        hitbox_velocity = {1,0};
        turn = {0,0};
        enemy_health = 3;
        enemy_projectile = Projectile({hitbox.x + 20,hitbox.y + 100}, 2);
    }
    else if (type == 3)
    {
        hitbox = {location.x,location.y,80,120};
        hitbox_velocity = {-1,0};
        turn = {0,0};
        enemy_health = 3;
        enemy_projectile = Projectile({hitbox.x + 20,hitbox.y + 100}, 2);
    }
}

void Enemy::next()
{
    hitbox.x = hitbox.x + hitbox_velocity.width;
    hitbox.y = hitbox.y + hitbox_velocity.height;
    if (type == 0)
    {
        enemy_projectile = Projectile({hitbox.x + 20,hitbox.y + 100}, 1);
    }
    else if (type == 2 || type == 3)
    {
        enemy_projectile = Projectile({hitbox.x + 20,hitbox.y + 100}, 2);
    }
    else if (type == 1)
    {
        enemy_projectile = Projectile({hitbox.x + 130,hitbox.y + 100}, 4);
    }
}

void Enemy::accelerate()
{
    hitbox_velocity = hitbox_velocity + turn;
}

void Enemy::destroy_enemy()
{
    active = false;
}

bool Enemy::hits_edge() const
{
    return hitbox.top_left().x < 0 || hitbox.top_right().x > 1500 ||
           hitbox.bottom_left().y < 0 ||
           hitbox.top_left().y > 850;
}
