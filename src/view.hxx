#pragma once

#include "model.hxx"
#include <ge211.hxx>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>

class View
{
public:
    explicit View(Model const&);

    void draw(ge211::Sprite_set&);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    ge211::Font sans32 = {"sans.ttf", 32};
    Model const& model_;
    ge211::Image_sprite player{"Ship4.png"};
    ge211::Image_sprite enemy0{"EnemyShip1.png"};
    ge211::Image_sprite enemy1{"Ship7.png"};
    ge211::Image_sprite enemy2{"Ship8.png"};
    ge211::Image_sprite projectile0{"BlueLaser.png"};
    ge211::Image_sprite projectile1{"Missile.png"};
    ge211::Image_sprite projectile2{"torpedo.gif"};
    ge211::Image_sprite projectile4{"FireBlast.png"};
    ge211::Image_sprite projectile56{"LightningBlast.png"};
    ge211::Text_sprite score_banner{"Score:", sans32};
    ge211::Text_sprite score;
    ge211::Text_sprite bomb_banner{"Bomb: ", sans32};
    ge211::Text_sprite bomb;
    ge211::Text_sprite health_banner{"Health: ", sans32};
    ge211::Text_sprite health;
    ge211::Image_sprite bg{"bkgd2.png"};
    ge211::Text_sprite gameover_banner{"Final Score: ", sans32};
    ge211::Text_sprite gameover;
};
