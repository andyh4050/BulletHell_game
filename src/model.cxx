#include "model.hxx"

using namespace ge211;

Model::Model(Player player)
        : p_(player)
        , frame(0)
        , interval0(150)
        , interval1(800)
        , interval2(300)
        , end_frame(300)
{}

void Model::set_velocity(ge211::Dimensions move)
{
    p_.hitbox_velocity.width  = move.width;
    p_.hitbox_velocity.height = move.height;
}

ge211::Position Model::get_position() const
{
    return p_.hitbox.top_left();
}


int Model::get_player_score() const
{
    return p_.score;
}


void Model::player_fire()
{
    proj_.push_back(Projectile({p_.hitbox.center().x, p_.hitbox.center().y}, 0));
}

void Model::place_enemy(Enemy e)
{
    enemy_.push_back(e);
}

void Model::enemy_fire(Projectile enemy_p)
{
    proj_.push_back(enemy_p);
}

bool Model::collision(Enemy e)
{
    int hor_distance = abs(p_.hitbox.center().x - e.hitbox.center().x);
    int vert_distance = abs(p_.hitbox.center().y - e.hitbox.center().y);

    return (hor_distance <= ((p_.hitbox.width / 2) + (e.hitbox.width / 2))) &&
           (vert_distance <= ((p_.hitbox.height / 2) + (e.hitbox.height / 2)));
}

bool Model::enemy_hit(Enemy e, Projectile p)
{
    int hor_distance = abs(e.hitbox.center().x - p.hurtbox.center().x);
    int vert_distance = abs(e.hitbox.center().y - p.hurtbox.center().y);

    return (hor_distance <= (e.hitbox.width / 2 + p.hurtbox.width / 2)) &&
           (vert_distance <= (e.hitbox.height / 2 + p.hurtbox.height / 2));
}

void Model::update()
{
    size_t count = 0;
    size_t count1 = 0;
    size_t count2 = 0;

    if (p_.hits_edge())
    {
        set_velocity({0,0});
    }

    if (!game_over()) {
        p_ = p_.next();

        for (auto &i : proj_) {
            if (i.hits_edge()) {
                i.destroy_proj();
                proj_.erase(proj_.begin() + count);
            } else if ((i.type != 0) && p_.player_hit(i) && (p_.invuln <= 0)) {
                proj_.erase(proj_.begin() + count);
                p_.health = p_.health - 1;
                p_.invuln = 80;
            } else {
                i.next();
                if (frame % 15 == 0) {
                    i.accelerate();
                }
            }
            for (auto &j : enemy_) {
                if (enemy_hit(j, i) && (i.type == 0)) {
                    j.enemy_health = j.enemy_health - 1;
                    i.destroy_proj();
                    proj_.erase(proj_.begin() + count);
                    if (j.enemy_health == 0) {
                        j.destroy_enemy();
                        enemy_.erase(enemy_.begin() + count1);
                        p_.score = p_.score + 1;
                    }
                }
                count1++;
            }
            count++;
            count1 = 0;
        }

        for (auto &k : enemy_) {
            if (k.hits_edge()) {
                k.destroy_enemy();
                enemy_.erase(enemy_.begin() + count2);
            } else if (collision(k) && (p_.invuln <= 0)) {
                k.destroy_enemy();
                p_.score = p_.score + 1;
                p_.health = p_.health - 1;
                enemy_.erase(enemy_.begin() + count2);
                p_.invuln = 80;
            } else {
                k.next();
                if (frame % 60 == 0) {
                    k.accelerate();
                }
            }
            count2++;

            if ((k.type == 2 || k.type == 3) && frame % 90 == 0) {
                enemy_fire(k.enemy_projectile);
                enemy_fire(Projectile({k.hitbox.x + 20, k.hitbox.y + 100}, 3));
            } else if ((k.type == 0) && ((frame + 30) % 60 == 0)) {
                enemy_fire(k.enemy_projectile);
            } else if ((k.type == 1) && ((frame + 25) % 75) == 0) {
                enemy_fire(k.enemy_projectile);
                enemy_fire(Projectile({k.hitbox.x + 130, k.hitbox.y + 100}, 5));
                enemy_fire(Projectile({k.hitbox.x + 130, k.hitbox.y + 100}, 6));
            }
        }

        frame++;
        p_.invuln = p_.invuln - 1;
        interval0 = interval0 - 0.01;
        interval1 = interval1 - 0.01;
        interval2 = interval2 - 0.01;
    }
    if (interval0 <= 10)
    {
        interval0 = 100;
    }
    if (interval1 <= 10)
    {
        interval1 = 100;
    }
    if (interval2 <= 10)
    {
        interval2 = 100;
    }

    if (game_over())
    {
        end_frame = end_frame - 1;
        if (end_frame == 0)
        {
            exit(1);
        }
    }
}

void Model::bomb()
{
    if (p_.bomb_uses > 0)
    {
        int count = 0;
        int count1 = 0;
        for (auto &i : proj_) {
            proj_.erase(proj_.begin() + count);
            count++;
        }
        for (auto &i : enemy_) {
            enemy_.erase(enemy_.begin() + count1);
            count1++;
            p_.score = p_.score + 1;
        }
        p_.bomb_uses = p_.bomb_uses - 1;
    }
}

bool Model::game_over() const
{
    return p_.health <= 0;
}