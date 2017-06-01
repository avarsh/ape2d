#include <ape/graphics/graphics.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace ape {

    /*
     * TODO: we can only have one instance of this class currently since it
     * is managing the lifetime of GLFW. Maybe decouple the GLFW initalization
     * and destruction from this class and let it be managed by the core
     * engine? This could allow for some more interesting possibilities, e.g.
     * multiple "worlds" each with their own graphics module, such as a world
     * for the main menu, a world for the game, etc. We could also decouple
     * the world from the graphics module and require it to be passed in to
     * each function.
     */

    Graphics::Graphics(World& world) : world(world) {
        if(!glfwInit()) {
            std::cout << "GLFW failed to initalize!\n";
        }

        window.createdEvent.addCallback([this](Vec2i newDims) {
            texturedShader.load("./data/shaders/textured.vert", "./data/shaders/textured.frag");
            _setViewport(newDims);
            _createSpriteBuffer();
        });

        window.resizedEvent.addCallback([this](Vec2i newDims) {
            _setViewport(newDims);
        });
    }

    Graphics::~Graphics() {
        window.destroy();
        glfwTerminate();
    }

    void Graphics::clear(Color color) {
        glClearColor(color.red, color.green, color.blue, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        meshDrawList.clear();
        batchRenderers.clear();
    }

    void Graphics::draw(entity_t entity) {
        meshDrawList.push_back(world.getComponent<Mesh>(entity));
    }

    // TODO: This is broken -
    // We need to batch draw consequtive sprites with the same texture.
    // We also need to have a one-to-one relationship between the batch
    // renderer and the vbos it uses
    // This means we can't create batch renderers on the fly - one renderer
    // per texture could work.
    void Graphics::display() {
        if(meshDrawList.size() > 0) {

            GLuint currentTextureId = meshDrawList[0].getTextureId();
            int index = 0;
            batchRenderers.push_back(BatchRenderer(currentTextureId));

            for(auto& mesh : meshDrawList) {
                if(mesh.getTextureId() != currentTextureId) {
                    currentTextureId = mesh.getTextureId();
                    batchRenderers.push_back(BatchRenderer(currentTextureId));
                    index++;
                }

                batchRenderers[index].addMesh(mesh);
            }

            texturedShader.use();
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(texturedShader.getUniformLocation("u_texture"), 0);

            for(auto& renderer : batchRenderers) {
                textureMap[renderer.getTextureId()].bind();
                renderer.drawAll(world, attributeVBO, matrixVBO);

                glBindVertexArray(vertexArray);
                glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, renderer.getMeshListSize());
                glBindVertexArray(0);
            }
        }

        glfwSwapBuffers(window.getWindow());
    }

    Window& Graphics::getWindow() {
        return window;
    }

    Texture& Graphics::loadTexture(const std::string& source) {
        GLuint texId;

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        Vec2i size;

        unsigned char* image = SOIL_load_image(source.c_str(), &size.x, &size.y,
            0, SOIL_LOAD_RGBA);

        if(image == NULL) {
            throw std::runtime_error("Error when loading textures: file at path "
                + source + " was not found.");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);

        glEnable (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, 0);

        textureMap[texId] = Texture();
        textureMap[texId].id = texId;
        textureMap[texId].size = size;

        return textureMap[texId];
    }

    void Graphics::_setViewport(Vec2i newDimensions) {
        glViewport(0, 0, newDimensions.x, newDimensions.y);
        projectionMatrix = glm::ortho(0.f, (float)newDimensions.x,
            (float)newDimensions.y, 0.0f, -1.0f, 1.0f);

        // TODO: only set shader if it is not currently in use
        texturedShader.use();
        GLint projection = texturedShader.getUniformLocation("projection");
        glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        for(int i = 0; i < 4; i++) {
            std::cout << projectionMatrix[0][i] << " " << projectionMatrix[1][i]
                << " " << projectionMatrix[2][i] << " " << projectionMatrix[3][i]
                << std::endl;
        }

    }

    void Graphics::_createSpriteBuffer() {

        // ================
        // Generate buffers
        // ================

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        // =====================
        // Initalise the buffers
        // =====================

        // ======================
        // Buffers for the square
        // ======================

        squareVBO.init(GL_ARRAY_BUFFER, square, sizeof(square), false);
        squareEBO.init(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), false);

        squareVBO.bind();

        glVertexAttribPointer(VertexAttributeInfo::PositionLocation,
            VertexAttributeInfo::PositionSize, GL_FLOAT, GL_FALSE,
            VertexAttributeInfo::PositionSize * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(VertexAttributeInfo::PositionLocation);

        // ==========================
        // The buffer for each vertex
        // ==========================

        attributeVBO.init(GL_ARRAY_BUFFER, NULL, maxSize, true);
        attributeVBO.bind();

        int size = VertexAttributeInfo::ColorSize + VertexAttributeInfo::TextureSize;

        glVertexAttribPointer(VertexAttributeInfo::ColorLocation,
            VertexAttributeInfo::ColorSize, GL_FLOAT, GL_FALSE,
            size * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(VertexAttributeInfo::ColorLocation);

        glVertexAttribPointer(VertexAttributeInfo::TextureLocation,
            VertexAttributeInfo::TextureSize, GL_FLOAT, GL_FALSE,
            size * sizeof(GLfloat), (GLvoid*)(VertexAttributeInfo::ColorSize * sizeof(GLfloat)));

        glEnableVertexAttribArray(VertexAttributeInfo::TextureLocation);

        // ============================
        // The buffer for each instance
        // ============================

        matrixVBO.init(GL_ARRAY_BUFFER, NULL, maxSize, true);

        for(int column = 0; column < 4; column++) {
            glVertexAttribPointer(VertexAttributeInfo::TextureLocation + 1 + column, 3, GL_FLOAT, GL_FALSE,
                12 * sizeof(GLfloat), (GLvoid*)(column * 3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(VertexAttributeInfo::TextureLocation + 1 + column);
            glVertexAttribDivisor(VertexAttributeInfo::TextureLocation + 1 + column, 1);
        }

        // =========
        // Unbinding
        // =========

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
