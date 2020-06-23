#include "model.hxx"
#include <catch.hxx>

TEST_CASE("Enemies exist and are initialized properly, with their projectiles")
{
    Player p({750, 800}, {0,0});
    Model model(p);

    Enemy e({750, 200}, 2);
    model.place_enemy(e);
    CHECK(model.enemy_[0].hitbox == e.hitbox);
    CHECK(model.enemy_[0].hitbox_velocity == e.hitbox_velocity);
    CHECK(model.enemy_[0].type == e.type);
    CHECK(model.enemy_[0].active == e.active);
    CHECK(model.enemy_[0].turn == e.turn);
    CHECK(model.enemy_[0].enemy_health == e.enemy_health);
    CHECK(model.enemy_[0].enemy_projectile.hurtbox == e.enemy_projectile.hurtbox);
    CHECK(model.enemy_[0].enemy_projectile.hurtbox_velocity == e.enemy_projectile.hurtbox_velocity);
    CHECK(model.enemy_[0].enemy_projectile.type == e.enemy_projectile.type);
    CHECK(model.enemy_[0].enemy_projectile.active == e.enemy_projectile.active);
    CHECK(model.enemy_[0].enemy_projectile.turn == e.enemy_projectile.turn);
}

TEST_CASE("Enemy gets hit with player's projectile")
{
    Player p({750, 800}, {0,0});
    Model model(p);

    Enemy e({750, 200}, 2);
    model.place_enemy(e);
    CHECK(model.enemy_[0].hitbox == e.hitbox);

    Projectile h({750, 250}, 0);
    model.enemy_fire(h);
    CHECK(model.proj_[0].hurtbox == h.hurtbox);

    model.update();
    CHECK(model.enemy_hit(model.enemy_[0], model.proj_[0]));
    CHECK(model.enemy_[0].enemy_health == 2);
    CHECK(model.proj_[0].active);
}

TEST_CASE("Player gets hit with enemy's projectile")
{
    Player p({750,800},{0,0});
    Model model(p);

    Projectile z({750,800},2);
    model.enemy_fire(z);
    model.update();

    CHECK(model.p_.player_hit(z));
    CHECK(model.p_.health == 2);
    CHECK(model.proj_.empty());
    CHECK(model.p_.invuln > 0);
}

TEST_CASE("Player runs into enemy ship")
{
    Player p({750,800},{0,0});
    Model model(p);

    Enemy e({750, 800}, 2);
    model.place_enemy(e);
    model.update();

    CHECK(model.p_.health == 2);
    CHECK(model.enemy_.empty());
    CHECK(model.p_.invuln > 0);
    CHECK(model.p_.score == 1);
}

TEST_CASE("Bomb clears enemies and projectiles off screen")
{
    Player p({750, 800}, {0, 0});
    Model model(p);

    Enemy e({750, 200}, 2);
    model.place_enemy(e);

    Enemy f({700, 300}, 3);
    model.place_enemy(f);

    Projectile y({650, 500}, 2);
    model.enemy_fire(y);

    Projectile z({550, 700}, 3);
    model.enemy_fire(z);
    CHECK_FALSE(model.enemy_.empty());

    model.bomb();

    CHECK(model.enemy_.empty());
    CHECK(model.proj_.empty());
    CHECK(model.p_.score == 2);
    CHECK(model.p_.bomb_uses == 2);
}
