#include "view.hxx"

// Convenient type aliases:
using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

View::View(Model const& model)
        : model_(model)
{}

ge211::Dimensions View::initial_window_dimensions() const
{
    return {1500, 1000};
}

std::string View::initial_window_title() const
{
    return "Touhou Project";
}

void View::draw(Sprite_set& set)
{
    if (model_.game_over())
    {
        gameover = ge211::Text_sprite(std::to_string(model_.p_.final_score), sans32);
        set.add_sprite(gameover_banner, {600, 500}, 15);
        set.add_sprite(gameover, {800, 500}, 15);
    }
    set.add_sprite(bg, {0, 0}, -1, ge211::Transform::scale(0.75));

    score = ge211::Text_sprite(std::to_string(model_.p_.score), sans32);
    set.add_sprite(score_banner, {1200, 100}, 15);
    set.add_sprite(score, {1300, 100}, 15);

    bomb = ge211::Text_sprite(std::to_string(model_.p_.bomb_uses), sans32);
    set.add_sprite(bomb_banner, {100, 100}, 15);
    set.add_sprite(bomb, {200, 100}, 15);

    health = ge211::Text_sprite(std::to_string(model_.p_.health), sans32);
    set.add_sprite(health_banner, {1200, 800}, 15);
    set.add_sprite(health, {1300, 800}, 15);

    set.add_sprite(player, {model_.p_.hitbox.center().x + 10, model_.p_.hitbox.center().y}, 10, ge211::Transform::scale(0.05));
    for (Projectile p : model_.proj_)
    {
        if (p.type == 0)
        {
            set.add_sprite(projectile0, p.hurtbox.center(), 2, ge211::Transform::scale(0.5));
        }
        else if (p.type == 1)
        {
            set.add_sprite(projectile1, p.hurtbox.center(), 1, ge211::Transform::scale(0.5));
        }
        else if (p.type == 2 || p.type == 3)
        {
            set.add_sprite(projectile2, p.hurtbox.center(), 1, ge211::Transform::scale(0.1));
        }
        else if (p.type == 4)
        {
            set.add_sprite(projectile4, p.hurtbox.top_left(), 3, ge211::Transform::scale(0.1));
        }
        else if (p.type == 5 || p.type == 6)
        {
            set.add_sprite(projectile56, p.hurtbox.top_left(), 3, ge211::Transform::scale(0.1));
        }
    }
    for (Enemy e : model_.enemy_)
    {
        if (e.type == 0)
        {
            set.add_sprite(enemy0, {e.hitbox.center().x - 60, e.hitbox.center().y}, 3, ge211::Transform::scale(2));
        }
        if (e.type == 1)
        {
            set.add_sprite(enemy1, {e.hitbox.top_left().x, e.hitbox.top_left().y}, 1, ge211::Transform::scale(0.5));
        }
        if (e.type == 2 || e.type == 3)
        {
            set.add_sprite(enemy2, {e.hitbox.center().x - 90, e.hitbox.center().y}, 2, ge211::Transform::scale(0.2));
        }
    }
}


