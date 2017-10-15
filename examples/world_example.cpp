#include <iostream>
#include <ape/ape.h>

int main() {

    for(int i = 0; i < 10; i++) {
        auto entity = ape::world::createEntity();

        if(i % 2 == 0) {
            ape::world::addTag(entity, "Odd entity!");
        } else {
            ape::world::addTag(entity, "Even entity!");
        }
    }

    // Delete all odd entities
    auto oddEntities = ape::world::getTaggedEntities("Odd entity!");
    for(auto entity : oddEntities) {
        ape::world::deleteEntity(entity);
    }

    ape::world::refresh();

    // We should only get the even entities
    auto entity = ape::world::getFirstEntity();
    while(entity != ape::ENTITY_INVALID) {
        std::cout << entity << std::endl;
        entity = ape::world::getNext(entity);
    }

    std::cout << "Creating more entities\n";
    for(int i = 0; i < 5; i++) {
        auto entity = ape::world::createEntity();
    }

    // We should only get all entities from 1 to 10
    entity = ape::world::getFirstEntity();
    while(entity != ape::ENTITY_INVALID) {
        std::cout << entity << std::endl;
        entity = ape::world::getNext(entity);
    }
}
