#define CATCH_CONFIG_MAIN
#include <deps/catch.hpp>
#include <ape/core/world.h>

using namespace ape;

struct Data : Component<Data> {
    Data(entity_t entity) : Component<Data>(entity) { }

    int value {0};
};

TEST_CASE("Entity deletion") {
    // A bit of set up

    int creations = 3;
    for(int i = 0; i < creations; i++) {
        auto entity = world::createEntity();
        world::addComponent<Data>(entity);
    }

    int entityNum = 0;
    auto entity = world::getFirstEntity();
    while(entity != ENTITY_INVALID) {
        if(entityNum == 1) {
            world::deleteEntity(entity);
        }

        entity = world::getNext(entity);
        entityNum++;
    }

    // Check whether all entities were looped over
    REQUIRE(entityNum == 3);

    world::refresh();

    entityNum = 0;
    entity = world::getFirstEntity();
    while(entity != ENTITY_INVALID) {
        entity = world::getNext(entity);
        entityNum++;
    }

    // Check that the entity was correctly "skipped" over
    REQUIRE(entityNum == (creations - 1));

    // Check whether the component was removed from the list
    REQUIRE(world::getComponentPool<Data>().size() == (creations - 1));

    auto newEntity = world::createEntity();
    // Check that the world reallocated the existing entity
    REQUIRE(newEntity == 2);

    // Check that the entity has no components associated to it
    REQUIRE(world::entityHasComponent<Data>(newEntity) == false);

    auto originalFirst = entity = world::getFirstEntity();
    world::deleteEntity(entity);
    world::refresh();
    auto newFirst = world::getFirstEntity();

    // Check that first entity points to the right entity
    REQUIRE(newFirst > originalFirst);
}