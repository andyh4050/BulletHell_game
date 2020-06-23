#pragma once

#include "model.hxx"
#include "view.hxx"
#include <ge211.hxx>
#include <iostream>
#include <string>

class Controller : public ge211::Abstract_game
{
public:
    // Constructor takes in a player p
    explicit Controller(Player p);

    // Delegate to view
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

    // Sets the velocity of the player based on key inputs
    // (booleans left, right, up, down)
    void move();

    void on_key_down(ge211::Key) override;
    void on_key_up(ge211::Key) override;
    void on_frame(double) override;

private:
    Model model_;
    View view_;
    bool left;
    bool right;
    bool up;
    bool down;
};
