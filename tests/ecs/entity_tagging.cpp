#define CATCH_CONFIG_MAIN
#include <deps/catch.hpp>
#include <ape/core/world.h>

using namespace ape;

enum Tags {
    PLAYER,
    ENEMY
};

TEST_CASE("Entity tagging") {

    auto player = world::createEntity();
    world::tagEntity(player, Tags::PLAYER);

    std::vector<entity_t> fiftyEnemies;
    const int ENEMIES = 1000;
    for (int i = 0; i < ENEMIES; i++) {
        auto enemy = world::createEntity();
        world::tagEntity(enemy, Tags::ENEMY);

        if (i % 50 == 0) {
            fiftyEnemies.push_back(enemy);
        }
    }

    REQUIRE(world::getEntitiesWithTag(Tags::PLAYER).size() == 1);
    REQUIRE(world::getEntitiesWithTag(Tags::PLAYER).count(player) == 1);

    REQUIRE(world::getEntitiesWithTag(Tags::ENEMY).size() == ENEMIES);
    
    const int EXPECTED = ENEMIES - fiftyEnemies.size();

    for (entity_t entity : fiftyEnemies) {
        world::deleteEntity(entity);
    }

    world::refresh();

    REQUIRE(world::getEntitiesWithTag(Tags::ENEMY).size() == EXPECTED);
    REQUIRE(world::getEntitiesWithTag(Tags::ENEMY).count(fiftyEnemies[0]) == 0);

}