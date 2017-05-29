#include <ape/graphics/mesh.h>
#include <ape/core/transform.h>
#include <ape/graphics/sprite.h>
#include <ape/graphics/graphics.h>

#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
    ape::World world;
    ape::Graphics graphics(world);

    ape::Window& window = graphics.getMainWindow();
    window.create(800, 600, "Sprites!");

    graphics.init();

    ape::Texture catTexture;

    if(!catTexture.load("./data/cat.png")) {
        std::cout << "Failed to load texture!\n";
    }

    int catTextureID = graphics.addTexture(catTexture);

    srand((unsigned)time(0));

    for(int i = 0; i < 100; i++) {
        auto cat = world.createEntity();
        auto& mesh = world.addComponent<ape::Mesh>(cat);
        auto& sprite = world.addComponent<ape::Sprite>(cat);
        sprite.batchID = catTextureID;
        auto& transform = world.addComponent<ape::Transform>(cat);

        ape::Vertex vertex;
        vertex.texture.x = 0.0f;
        vertex.texture.y = 1.0f;
        vertex.color = ape::Color((rand()%255)+1, (rand()%12)+24, (rand()%108)+20);
        mesh.vertices.push_back(vertex);

        vertex.texture.x = 0.0f;
        vertex.texture.y = 0.0f;
        vertex.color = ape::Color((rand()%119)+55, (rand()%55)+106, (rand()%16)+192);
        mesh.vertices.push_back(vertex);

        vertex.texture.x = 1.0f;
        vertex.texture.y = 0.0f;
        vertex.color = ape::Color((rand()%83)+19, (rand()%255)+1, (rand()%116)+75);
        mesh.vertices.push_back(vertex);

        vertex.texture.x = 1.0f;
        vertex.texture.y = 1.0f;
        vertex.color = ape::Color((rand()%200)+1, (rand()%255)+1, (rand()%196)+1);
        mesh.vertices.push_back(vertex);

        sprite.dimensions.x = (rand()%50)+25;
        sprite.dimensions.y = (rand()%50)+25;

        transform.position.x = (rand()%800)+1;
        transform.position.y = (rand()%600)+1;

        transform.rotation = (rand()%180)+1;
    }


    while(window.isOpen()) {
        glfwPollEvents();

        window.clear(ape::Colors::Sea);
        graphics.draw();
        window.display();
    }

    return 0;
}
