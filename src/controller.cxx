#include "controller.hxx"

using namespace std::this_thread;
using namespace std::chrono;

Controller::Controller(Player p_)
        : model_(p_)
        , view_(model_)
        , up(false)
        , down(false)
        , left(false)
        , right(false)
{ }

void Controller::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::left())
        left = true;
    if (key == ge211::Key::right())
        right = true;
    if (key == ge211::Key::up())
        up = true;
    if (key == ge211::Key::down())
        down = true;
    if (key.code() == 'j')
        model_.player_fire();
    if (key.code() == 'k')
        model_.bomb();
}

void Controller::move()
{
    if (left)
        model_.set_velocity({-5, 0});
    if (right)
        model_.set_velocity({5, 0});
    if (up)
        model_.set_velocity({0, -5});
    if (down)
        model_.set_velocity({0, 5});
    if (up && left)
        model_.set_velocity({-5, -5});
    if (up && right)
        model_.set_velocity({5, -5});
    if (down && left)
        model_.set_velocity({-5, 5});
    if (down && right)
        model_.set_velocity({5, 5});
}

void Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::left() || key == ge211::Key::right() ||
        key == ge211::Key::up() || key == ge211::Key::down())
        left = false;
    right = false;
    up = false;
    down = false;
    model_.set_velocity({0, 0});
}

void Controller::on_frame(double dt)
{
    move();
    model_.update();
    if (model_.frame%int(model_.interval0) == 0)
    {
        model_.place_enemy(Enemy({50, 50}, 0));
    }
    if (model_.frame%int(model_.interval1) == 0)
    {
        model_.place_enemy(Enemy({1200, 100}, 1));
    }
    if (model_.frame%int(model_.interval2) == 0)
    {
        model_.place_enemy(Enemy({300, 100}, 2));
    }
    if ((model_.frame+150)%int(model_.interval2) == 0)
    {
        model_.place_enemy(Enemy({1200, 100}, 3));
    }
    if (model_.game_over())
    {
        model_.p_.final_score = model_.p_.score;
    }
}

void Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

